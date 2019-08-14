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

/**
 * No need to yell...
 */
#ifndef nullptr
#define nullptr NULL 
#endif

/** 
 * c11 has type inference 
 */
#define var __auto_type
#define auto __auto_type

/**
 *  MACRO Type
 *  MACRO Alloc
 *  MACRO New
 *  MACRO Ctor
 *  MACRO Method
 *  MACRO Super
 * 
 * Overloadeble multi-methods
 * 
 * requires clang, but then so does emscripten
 */
#define overload __attribute__((overloadable))
/**
 *  MACRO Type
 *      The instance object
 */
#define Type(T)                                                         \
    typedef struct T T;                                                 \
    struct T

/**
 *  MACRO Ctor
 *      Define the constructor method
 */
#define Ctor(T, args...) static inline T* T##_ctor(T* this, ## args)

/**
 *  MACRO Alloc
 *      Allocate memory for 'this' struct
 */
#define Alloc(T) (T*)malloc(sizeof(T))

/**
 *  MACRO New
 *      Allocate and initialize a new object
 */
#define new(T, args...) T##_ctor(Alloc(T), ## args)

/**
 *  MACRO Method
 *      Allocate and initialize a new object
 */
#define Method static inline overload

/**
 *  MACRO Super
 *      callback into base class
 */
#define Super(T, method) \
    if (this->base != nullptr) \
        ##method##((T*)this->base); \

/**
 * Redefine true and false for use with _Generic,
 * such that true and false match bool, not int.
 */
#undef true
#undef false
#define true (_Bool)1
#define false (_Bool)0
#define yes true
#define no false

/**
 *  MACRO Min
 *      cache results of calculation in pocket scope 
 */
#define Min(a, b)                                                       \
({                                                                      \
    auto _a = a;                                                        \
    auto _b = b;                                                        \
    (_a < _b) ? _a : _b;                                                \
})

/**
 *  MACRO Max
 *      cache results of calculation in pocket scope 
 */
#define Max(a, b)                                                       \
({                                                                      \
    auto _a = a;                                                        \
    auto _b = b;                                                        \
    (_a > _b) ? _a : _b;                                                \
})

/**
 * Bind Wren Script api to native functions
 */
typedef struct WrenMethod
{
    char* name;
    void* addr;

} WrenMethod;

typedef struct Class 
{
    char* module;
    char* className;
    void* allocate;
    void* finalize;
    WrenMethod methods[100];

} Class;

#define WrenApi static inline void
