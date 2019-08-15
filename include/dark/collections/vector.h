/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "../core.h"

type (Vector) {
    Object* Isa;
    int length;
    // void **data;
    unsigned char **data;
    int capacity;
};

/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-Vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4

constructor (Vector)
{
    this->Isa = nullptr;
    this->capacity = ARRAY_INIT_CAPACITY;
    this->length = 0;
    this->data = malloc(sizeof(void *) * this->capacity);
    return this;
}

method int Length(Vector* this)
{
    return this->length;
}

method void Resize(Vector* this, int capacity)
{
    #ifdef DEBUG_ON
    printf("Resize: %d to %d\n", this->capacity, capacity);
    #endif

    unsigned char **data = realloc(this->data, sizeof(void *) * capacity);
    if (data) {
        this->data = data;
        this->capacity = capacity;
    }
}

method void Add(Vector* this, void *item)
{
    if (this->capacity == this->length)
        Resize(this, this->capacity * 2);
    this->data[this->length++] = item;
}

method void Set(Vector* this, int index, void *item)
{
    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

method void *Get(Vector* this, int index)
{
    if (index >= 0 && index < this->length)
        return this->data[index];
    return nullptr;
}

method void Delete(Vector* this, int index)
{
    if (index < 0 || index >= this->length)
        return;

    this->data[index] = nullptr;

    for (int i = index; i < this->length - 1; i++) {
        this->data[i] = this->data[i + 1];
        this->data[i + 1] = nullptr;
    }

    this->length--;

    if (this->length > 0 && this->length == this->capacity / 4)
        Resize(this, this->capacity / 2);
}

method void Dispose(Vector* this)
{
    free(this->data);
}