#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "dark.h"
#include "lib/io.h"
#include "lib/sdl.h"
/**
 * Wren native class bindings
 */
struct Class metadata[] = 
{
    {
        "lib/io/path", "Path",  io_path_Allocate, io_path_Finalize,
        { 
            { "+Absolute",              io_path_Absolute },
            { "+Relative",              io_path_Relative },
            { "+Simple",                io_path_Simple },
            { "+Cwd",                   io_path_Cwd },
            { "Type()",                 io_path_Type },
            { "DirName()",              io_path_DirName },
            { "RemoveExtension()",      io_path_RemoveExtension }, 
            { "Join(_)",                io_path_Join },
            { "AppendChar(_)",          io_path_AppendChar }, 
            { "AppendString(_)",        io_path_AppemdString }, 
            { "Normalize()",            io_path_Normalize }, 
            { "ToString()",             io_path_ToString }, 
        }
    },{
        "lib/io/stream", "Stream", io_stream_Allocate, io_stream_Finalize,
        {
            { "Write(_)",               io_stream_Write },
            { "Read()",                 io_stream_Read },
            { "Close()",                io_stream_Close }, 
        }
    },{
        "lib/sdl", "Sdl", nullptr, nullptr,
        {
            { "+Init(_)",               sdl_Init },
            { "+Delay(_)",              sdl_Delay },
            { "+Quit()",                sdl_Quit },
        }
    },{
        "lib/sdl/window", "Window", sdl_window_Allocate, sdl_window_Finalize,
        {
            { "Close()",                sdl_window_Close },
        }
    },{
        "lib/sdl/renderer", "Renderer", sdl_renderer_Allocate, sdl_renderer_Finalize,
        {
            { "DrawColor(_,_,_,_)",     sdl_renderer_DrawColor },
            { "Clear()",                sdl_renderer_Clear },
            { "Present()",              sdl_renderer_Present },
            { "Close()",                sdl_renderer_Close },
        }
    }
};
