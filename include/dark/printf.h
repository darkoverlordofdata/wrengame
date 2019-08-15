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
#include <stdio.h> 
#include <stdbool.h> 
#include <stdarg.h>
#include <math.h> 

proc int DSvsnprintf(char* str, size_t n, const char* format, va_list _args)  
{
    char *current; 
    char result[40];
    char spec[40];
    int i;
    int l;
    int c;
    char *s;
    void* object;
    char *dst = str;
    bool update = (str != nullptr);
    int length = 0;
    char* types = "diuoxXfFeEgGaAcspn$";
    va_list arg; 
    va_copy(arg, _args);
    
    /**
     * decompose the format string into specifiers.
     * call sprintf for standard specifiers, and handle
     * new specifiers.
     */
    for (current = format; *current != '\0'; current++) { 

        while ( *current != '%' ) { 
            if (*current == '\0') return length;
            if (update) *dst++ = *current;
            current++; 
            length++;
        } 
        c = 0;
        memset(spec, 0, 40);
        spec[c++] = *current;
        current++;

        /** 
         * collect the specifier 
         * 
         *  %[flags][width][.precision][length]specifier 
         * 
         * Everything between the leading % and the specifier is collected
         * and passed on to stdlib sprintf. This is done to add a new
         * specifier, '$' for DaRKSTEP objects.
         * 
         */
        while ((*current != '\0') 
            && (strchr(types, *current) != nullptr)) {
            spec[c++] = *current;
            current++;
        }
        /** Back up one, and point to the specifier */
        current--;

        switch (*current) { 
        case 'c' :  /** char */
            i = va_arg(arg, int);    
            if (update) *dst++ = i;
            length++;
            break; 
                    
        case 'f' :  /** float */
        case 'F' : 
        case 'e' : 
        case 'E' : 
        case 'g' : 
        case 'G' : 
        case 'a' : 
        case 'A' : 
            l = sprintf(result, spec, va_arg(arg, double));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'u':   /** unsigned */
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'd':   /** integer */
        case 'i': 
            l = sprintf(result, spec, va_arg(arg, int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'o':   /** octal */
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;
                    
        case 's':   /** string */
            s = va_arg(arg, char *);       
            l = strlen(s);
            if (update) dst = strncpy(dst, s, l) + l;
            length += l;
            break; 
                    
        case 'x':   /** hex */
        case 'X':
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + 1;
            length += l;
            break;

        case '$':   /** DaRKSTEP object */
            object = va_arg(arg, void*);   
            l = strlen(ToString(object));
            if (update) dst = strncpy(dst, ToString(object), l) + l;
            length += l;
            break;
        }   
    } 
    va_end(arg); 
}


__attribute__((__format__ (__printf__, 1, 2)))                          \
proc char* DSsprintf(const char* format, ...) 
{
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = DSvsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return "";
    char* str = DScalloc((len+1), sizeof(char));
    len = DSvsnprintf(str, len+1, format, args2);
    va_end(args2);
    return str;
}

proc void DSvfprintf(FILE* stream, const char* format, va_list _args) 
{
    va_list args1;
    va_list args2;
    
    va_copy(args1, _args);
    va_copy(args2, _args);  

    int len = DSvsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    char* str = DScalloc((len+1), sizeof(char));
    len = DSvsnprintf(str, len+1, format, args2);
    va_end(args2);
    fputs(str, stream);
    return;
}

/**
 * DSLog
 * 
 * Writes output to stderr, with end of line.
 */
__attribute__((__format__ (__printf__, 1, 2)))
static inline void DSLog (char* format, ...) {

    va_list args;
    va_start(args, format);
    DSvfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}
