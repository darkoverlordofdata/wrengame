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
#include <errno.h>
#include "../core.h"

#define DOUBLE_MIN_VALUE  DBL_MIN
#define DOUBLE_MAX_VALUE  DBL_MAX
#define DOUBLE_BYTES      (sizeof(double))
#define DOUBLE_SIZE       (DOUBLE_BYTES * CHAR_BIT)
#define DOUBLE_TYPE       (TYPE_DOUBLE)

type(Double)
{
    Object* Isa;
    double value;
};

/**
 * Constructor
 * create a new Double
 * 
 * @param value of double
 * 
 */
constructor(Double, const double value) {
    this->Isa = nullptr;
    this->value = value;
    return this;
}

/**
 * Returns a primitive double value parsed from input string. 
 */
proc double ParseDouble(char const *const s) {
    errno = 0;
    char* endptr;
    double result = strtod(s, endptr);

    // if (errno != 0)
    //     throw DSNumberFormatException(s, Source);

    // if (s == endptr || *endptr != '\0')
    //     throw DSNumberFormatException(s, Source);

    return result;
}

/**
 * Compare two double primitives.
 * @param  x double to compare
 * @param  y double to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const double x, const double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Double objects.
 *
 * @param   other  Double to be compared
 * @return same as Double_Compare
 */
method int CompareTo(const Double* const this, const Double* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Double* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Double* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Double* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Double* const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Double* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Double* const this) {
    return (short)this->value;
}

method char* ToString(const Double* const this) {
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

