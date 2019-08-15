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

type (ListNode) {
    void* data;
    ListNode* next;
};


type (List) {
    void* Isa;
    int length;
    ListNode* head;
};

typedef int (*List_Compare) (void*, void*);
typedef void (^List_Iterator) (void*);

/**
 * Create new ListNode
 * 
 * @param data to add
 * @param next node in list
 * 
 */
// function ListNode* NewListNode(void* data, ListNode* next)
constructor(ListNode, void* data, ListNode* next)
{
    this->data = data;
    this->next = next;
    return this;
}

constructor(List)
{
    this->Isa = nullptr;
    this->length = 0;
    this->head = nullptr;
    return this;
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
method void Insert(List* this, void* data, List_Compare comp)
{
    if (this->head == nullptr) {
        this->head = new(ListNode, data, nullptr);
        return;
    }

    // Find spot in linked list to insert new node
    ListNode* prev = nullptr;
    ListNode* curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = new(ListNode, data, this->head);
    else 
        prev->next = new(ListNode, data, curr);

    this->length++;
    return;

}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
method void Add(List* this, void* data)
{
    if (this->head == nullptr) {
        this->head = new(ListNode, data, nullptr);
    }
    else { 
       this->head = new(ListNode, data, this->head);
    }
    this->length++;

}

/**
 * Remove item at end of list
 */
method void* Remove(List* this, void* data)
{
    ListNode* head = this->head;

    void* popped_data = head->data;
    this->head = head->next;

    // delete(head);
    this->length--;
    return popped_data;

}

/**
 * Iterate over list
 * 
 * @param iter function to call for each iteration
 * 
 */
method void Iterate(List* const this, void (*iter)(void*))
{
    for (ListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}


method void Dispose(List* this)
{
}

method int Length(List* this)
{
    return this->length;
}

