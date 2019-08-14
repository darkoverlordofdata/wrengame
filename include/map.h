#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dark.h"

//http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29

Type (MapItem) {
    MapItem *next;
    char *key;
    void *value;
};

Type (Map)
{
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    MapItem **table;
};

/* create a new empty dictionary */
static inline Map* MapNew(void);

/* destroy a dictionary */
Method void Dispose(Map*);

/* insert a new key-value pair into an existing dictionary */
Method void Insert(Map*, const char *key, void *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
Method void *Search(Map*, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
Method void Delete(Map*, const char *key, bool);
Method void Delete(Map*, const char *key);

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

/* dictionary initialization code used in both MapNew and grow */
Method Map* internalMapAlloc(int size)
{
    Map* d;
    int i;

    d = malloc(sizeof(*d));

    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->table = malloc(sizeof(MapItem *) * d->size);

    assert(d->table != 0);

    for(i = 0; i < d->size; i++) d->table[i] = 0;

    return d;
}

static inline Map* MapNew(void)
{
    return internalMapAlloc(INITIAL_SIZE);
}

Method void Dispose(Map* d, bool content)
{
    int i;
    MapItem *e;
    MapItem *next;

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            if (content) free(e->value);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

Method void Dispose(Map* d)
{
    Dispose(d, false);
}
#define MULTIPLIER (97)

static inline unsigned long hash_function(const char *s)
{
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}

static inline void grow(Map* d)
{
    Map* d2;            /* new dictionary we'll create */
    Map swap;   /* temporary structure for brain transplant */
    int i;
    MapItem *e;

    d2 = internalMapAlloc(d->size * GROWTH_FACTOR);

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside Insert
             * to avoid this problem */
            Insert(d2, e->key, e->value);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call Dispose on d2 */
    swap = *d;
    *d = *d2;
    *d2 = swap;

    Dispose(d2, false);
}

/* insert a new key-value pair into an existing dictionary */
/* value is owned by the caller and not copied */
Method void Insert(Map* d, const char *key, void *value)
{
    MapItem *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = strdup(key);
    // e->value = strdup(value);
    e->value = value;

    h = hash_function(key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;

    /* grow table if there is not enough room */
    if(d->n >= d->size * MAX_LOAD_FACTOR) {
        grow(d);
    }
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
Method void * Search(Map* d, const char *key)
{
    MapItem *e;

    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
            return e->value;
        }
    }

    return 0;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
Method void Delete(Map* d, const char *key, bool contents)
{
    MapItem **prev;          /* what to change when MapItem is deleted */
    MapItem *e;              /* what to delete */

    for(prev = &(d->table[hash_function(key) % d->size]); 
        *prev != 0; 
        prev = &((*prev)->next)) {
        if(!strcmp((*prev)->key, key)) {
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            if (contents) free(e->value);
            free(e);

            return;
        }
    }
}

Method void Delete(Map* d, const char *key)
{
    Delete(d, key, false);
}