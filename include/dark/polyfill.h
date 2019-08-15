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

//  some string related functions that should be in the stdlib

/**
 * strrstr - Returns a pointer to the first occurrence of str2 
 * in str1, or a null pointer if str2 is not part of str1.
 * 
 * @param str string to search in
 * @param str2 string to search for
 * @return ptr to the substring
 */
#ifndef strrstr
proc char * strrstr(char *str1, char *str2)
{
  size_t slen = strlen(str1);
  size_t flen = strlen(str2);
  if (flen > slen) return nullptr;

  for (char* result = str1 + slen - flen; result >= str1; result--)
  {
    if (strncmp(result, str2, flen) == 0)
        return result;
  }
  return nullptr;
}
#endif

/**
 * strndup - Returns a pointer to a null-terminated byte string, which 
 * is a duplicate of the string pointed to by str1. The returned pointer 
 * must be passed to free to avoid a memory leak.
 * 
 * @param str string to duplicate
 * @param size of the new string
 * @return ptr to the new string
 */
#ifndef strdup
proc char* strdup(const char* s) {
    size_t len = strlen(s)+1;
    void* new = malloc(len);
    if (new == nullptr) return nullptr;
    return (char*)memcpy(new, s, len);
}
#endif

/**
 * join strings
 * 
 * @param count of strings
 * @param ... list of char*'s
 * @returns all strings concantenated together.
 */
proc char* STR_JOIN(int count, ...)
{
    
    int size = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);  

    /**
     * Caclulate length of the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args1, char*);
        size += strlen(str);
    }
    va_end(args1);
    char* result = calloc((size+1),  sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args2, char*);
        strcat(result, str);
    }
    va_end(args2);
    return result;
}

/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
proc char* ReadTextFile(FILE* f)
{
    fseek(f, 0L, SEEK_END);
    long s = ftell(f);
    rewind(f);
    char* buf = calloc(1, s+1);
    buf[s] = '\0';

    if (buf != nullptr)
    {
        fread(buf, s, 1, f);
        return buf;
    }
    return buf;
}

/**
 * println
 * 
 * Writes output to stderr, with end of line.
 */
__attribute__((__format__ (__printf__, 1, 2)))
static inline void println (char* format, ...) {

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\n");
}


// type (Object)
// {
//     Object* Isa;
// };

/**
 *  Length of string
 */
method int Length(char* s) {
    return strlen(s);
}

