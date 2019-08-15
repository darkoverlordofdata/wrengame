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

type(Char)
{
    Object* Isa;
    char value;
};

/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
constructor(Char, const char value)
{
    this->Isa = nullptr;
    this->value = value;
    return this;
}

/**
 * Compare two char primitives.
 * @param  x char to compare
 * @param  y char to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const char x, const char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as Char_Compare
 */
method int CompareTo(const Char* const this, const Char* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Char* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Char* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Char* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Char* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Char* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Char* const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
method char* ToString(const Char* const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}


