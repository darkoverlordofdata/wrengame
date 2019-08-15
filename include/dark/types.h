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
#include "collections/vector.h"
#include "collections/map.h"
#include "collections/list.h"
#include "types/boolean.h"
#include "types/string.h"
#include "types/stringbuilder.h"
#include "types/char.h"
#include "types/double.h"
#include "types/float.h"
#include "types/integer.h"
#include "types/long.h"
#include "types/short.h"

proc Boolean*   NewBoolean(bool b) { return new(Boolean, b); } 
proc Char*      NewChar(char c) { return new(Char, c); }
proc String*    NewString(char* s) { return new(String, s); }
proc Short*     NewShort(short i) { return new(Short, i); }
proc Long*      NewLong(long l) {return new(Long, l); }
proc Integer*   NewInteger(int i) { return new(Integer, i); }
proc Float*     NewFloat(float f) { return new(Float, f); }
proc Double*    NewDouble(double d) { return new(Double, d); }


/**
 *  MACRO $
 *      Wrap a primitive type in an Object*
 */
#define $(T) _Generic((T),                                              \
                                                                        \
        _Bool:              NewBoolean,                                \
        char:               NewChar,                                   \
        signed char:        NewChar,                                   \
        const char *:       NewString,                                 \
        char *:             NewString,                                 \
        short int:          NewShort,                                  \
        unsigned short int: NewShort,                                  \
        unsigned int:       NewInteger,                                \
        long int:           NewLong,                                   \
        unsigned long int:  NewLong,                                   \
        int:                NewInteger,                                \
        float:              NewFloat,                                  \
        double:             NewDouble,                                 \
        default:            NewString)(T)

        // double:             NewDouble,                                 \


/**
 *  MACRO typeof
 *      return the typename of T
 */
#define typeof(T)                                                       \
    _Generic((T),        /* wrap a primitive type */                    \
                                                                        \
        _Bool: "bool",                                                  \
        unsigned char: "unsigned char",                                 \
        char: "char",                                                   \
        signed char: "signed char",                                     \
        short int: "short int",                                         \
        unsigned short int: "unsigned short int",                       \
        int: "int",                                                     \
        unsigned int: "unsigned int",                                   \
        long int: "long int",                                           \
        unsigned long int: "unsigned long int",                         \
        long long int: "long long int",                                 \
        unsigned long long int: "unsigned long long int",               \
        float: "float",                                                 \
        double: "double",                                               \
        long double: "long double",                                     \
        char *: "pointer to char",                                      \
        void *: "pointer to void",                                      \
        int *: "pointer to int",                                        \
        const char *: "const pointer to char",                          \
        Object *: "Object",                                             \
        Boolean *: "Boolean",                                           \
        Char *: "Char",                                                 \
        Double *: "Double",                                             \
        Float *: "Float",                                               \
        Integer *: "Integer",                                           \
        Long *: "Long",                                                 \
        Short *: "Short",                                               \
        String *: "String",                                             \
        StringBuilder *: "StringBuilder",                               \
        Vector *: "Vector",                                             \
        Map *: "Map",                                                   \
        List *: "List",                                                 \
        default: "unknown")

