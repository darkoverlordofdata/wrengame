#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "lib/io.h"
#include "lib/sdl.h"


/**
 * wren_BindForeignMethod
 */
static inline WrenForeignMethodFn 
wren_BindForeignMethod( WrenVM* vm, 
                        const char* module, 
                        const char* className, 
                        bool isStatic, 
                        const char* signature) 
{
    if (strcmp(module, "lib/io/path") == 0) 
    {
        if (strcmp(className, "Path") == 0) 
        { 

            if ( isStatic && strcmp(signature, "Absolute") == 0)        return io_path_Absolute; 
            if ( isStatic && strcmp(signature, "Relative") == 0)        return io_path_Relative; 
            if ( isStatic && strcmp(signature, "Simple") == 0)          return io_path_Simple; 
            if ( isStatic && strcmp(signature, "Cwd") == 0)             return io_path_Cwd; 

            if (!isStatic && strcmp(signature, "Type()") == 0)          return io_path_Type; 
            if (!isStatic && strcmp(signature, "DirName()") == 0)       return io_path_DirName; 
            if (!isStatic && strcmp(signature, "RemoveExtension()") == 0)   return io_path_RemoveExtension; 
            if (!isStatic && strcmp(signature, "Join(_)") == 0)         return io_path_Join;
            if (!isStatic && strcmp(signature, "AppendChar(_)") == 0)   return io_path_AppendChar; 
            if (!isStatic && strcmp(signature, "AppendString(_)") == 0) return io_path_AppemdString; 
            if (!isStatic && strcmp(signature, "Normalize()") == 0)     return io_path_Normalize; 
            if (!isStatic && strcmp(signature, "ToString()") == 0)      return io_path_ToString; 
        }
    }

    if (strcmp(module, "lib/io/stream") == 0) 
    {
        if (strcmp(className, "Stream") == 0) 
        { 
            if (!isStatic && strcmp(signature, "Write(_)") == 0)    return io_stream_Write; 
            if (!isStatic && strcmp(signature, "Read()") == 0)      return io_stream_Read; 
            if (!isStatic && strcmp(signature, "Close()") == 0)     return io_stream_Close; 
        }
    }

    if (strcmp(module, "lib/io/file") == 0) 
    {
        if (strcmp(className, "File") == 0) 
        { 
        }
    }

    if (strcmp(module, "lib/sdl") == 0) 
    {
        if (strcmp(className, "Sdl") == 0) 
        { 
            if (isStatic && strcmp(signature, "Init(_)") == 0)      return sdl_Init;
            if (isStatic && strcmp(signature, "Delay(_)") == 0)     return sdl_Delay;
            if (isStatic && strcmp(signature, "Quit()") == 0)       return sdl_Quit;
        }
    }

    if (strcmp(module, "lib/sdl/window") == 0) 
    {
        if (strcmp(className, "Window") == 0) 
        { 
            if (!isStatic && strcmp(signature, "Close()") == 0)     return sdl_window_Close;
        }
    }

    if (strcmp(module, "lib/sdl/renderer") == 0) 
    {
        if (strcmp(className, "Renderer") == 0) 
        { 
            if (!isStatic && strcmp(signature, "DrawColor(_,_,_,_)") == 0)  return sdl_renderer_DrawColor;
            if (!isStatic && strcmp(signature, "Clear()") == 0)             return sdl_renderer_Clear;
            if (!isStatic && strcmp(signature, "Present()") == 0)           return sdl_renderer_Present;
        }
    }


    // Unknown method.
    return NULL; 
    
}
