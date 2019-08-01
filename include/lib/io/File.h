#pragma once
#include <stdio.h>
#include <string.h>
#include "wren.h"

/**
 *  private
 *  io/file::close_file
 */
static inline void io_file_close_file(FILE** file) 
{ 
    if (*file == nullptr) return;
    fclose(*file); 
    *file = nullptr; 
}


/**
 *  io/file::Allocate
 */
static inline void io_file_Allocate(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(FILE*)); 
    const char* path = wrenGetSlotString(vm, 1); 
    *file = fopen(path, "w"); 
}

/**
 *  io/file::Finalize
 * 
 */
static inline void io_file_Finalize(void* data) 
{ 
    io_file_close_file((FILE**) data); 
}

/**
 *  io/file::Write
 * 
 */
static inline void io_file_Write(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenGetSlotForeign(vm, 0);

    // Make sure the file is still open.
    if (*file == nullptr) 
    { 
        wrenSetSlotString(vm, 0, "Cannot write to a closed file."); 
        wrenAbortFiber(vm, 0); 
        return; 
    }

    const char* text = wrenGetSlotString(vm, 1); 
    fwrite(text, sizeof(char), strlen(text), *file); 
}

/**
 *  io/file::Close
 * 
 */
static inline void io_file_Close(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenGetSlotForeign(vm, 0); 
    io_file_close_file(file); 
}
