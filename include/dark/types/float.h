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

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

type(Float)
{
    Object* Isa;
    float value;
};

/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
constructor(Float, const float value)
{
    this->Isa = nullptr;
    this->value = value;
    return this;
}

/**
 * Returns a primitive float value parsed from input string. 
 */
proc float ParseFloat(const char* s)
{
    
    double d = ParseDouble(s);
    // if (d < FLOAT_MIN_VALUE || d > FLOAT_MAX_VALUE)
    //     throw DSNumberFormatException(s, Source);
    return (float)d;
}

/**
 * Compare two float primitives.
 * @param  x float to compare
 * @param  y float to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const float x, const float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as Float_Compare
 */
method int CompareTo(const Float* this, const Float* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Float* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Float* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Float* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Float* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Float* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Float* const this) {
    return (short)this->value;
}


method char* ToString(const Float* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}
