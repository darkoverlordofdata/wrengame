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
 *  MACRO type
 *  MACRO alloc
 *  MACRO New
 *  MACRO constructor
 *  MACRO method
 *  MACRO Super
 * 
 * Overloadeble multi-methods
 * 
 * requires clang, but then so does emscripten
 */
#define overload __attribute__((overloadable))
/**
 *  MACRO type
 *      The instance object
 */
#define type(T)                                                         \
    typedef struct T T;                                                 \
    struct T

/**
 *  MACRO constructor
 *      Define the constructor method
 */
#define constructor(T, args...) static inline T* T##_ctor(T* this, ## args)

/**
 *  MACRO alloc
 *      Allocate memory for 'this' struct
 */
#define alloc(T) (T*)malloc(sizeof(T))

/**
 *  MACRO New
 *      Allocate and initialize a new object
 */
#define new(T, args...) T##_ctor(alloc(T), ## args)

/**
 *  MACRO function
 *      All functions are static inline
 */
#define proc static inline
/**
 *  MACRO method
 *      Methods are overideable functions
 */
#define method proc overload


/**
 *  MACRO super
 *      callback into base class
 */
#define super(T, method)                                                \
    if (this->Isa != nullptr)                                           \
        ##method##((T*)this->Isa);                                      \

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
 *  MACRO __FILENAME__
 *      extracts the filename from the path
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 *  MACRO NARG
 *      Count the number of arguments
 */
#define PP_NARG(...)                                                    \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                                                   \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                                                       \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,                       \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,                       \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,                       \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,                       \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,                       \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,                       \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N()                                                     \
         63,62,61,60,                                                   \
         59,58,57,56,55,54,53,52,51,50,                                 \
         49,48,47,46,45,44,43,42,41,40,                                 \
         39,38,37,36,35,34,33,32,31,30,                                 \
         29,28,27,26,25,24,23,22,21,20,                                 \
         19,18,17,16,15,14,13,12,11,10,                                 \
         9,8,7,6,5,4,3,2,1,0


/**
 *  MACRO join
 *      String.join(..)
 */
#define Join(...) STR_JOIN(PP_NARG(__VA_ARGS__), __VA_ARGS__)

type (Object)
{
    Object* Isa;
};

