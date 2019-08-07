#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "dark.h"
#include "lib/io.h"
#include "lib/xna.h"

static inline Class* GetMetaData()
{
    /**
     * native class bindings
     */
    static struct Class metadata[] = 
    {
        {
            "lib/io/path", "Path",  io_path_Allocate, io_path_Finalize,
            { 
                { "+Absolute",              io_path_Absolute },
                { "+Relative",              io_path_Relative },
                { "+Simple",                io_path_Simple },
                { "+Cwd",                   io_path_Cwd },
                { "+Type(_)",               io_path_Type },
                { "DirName()",              io_path_DirName },
                { "RemoveExtension()",      io_path_RemoveExtension }, 
                { "Join(_)",                io_path_Join },
                { "AppendChar(_)",          io_path_AppendChar }, 
                { "AppendString(_)",        io_path_AppemdString }, 
                { "Normalize()",            io_path_Normalize }, 
                { "ToString()",             io_path_ToString }, 
            }
        },
        {
            "lib/io/stream", "Stream", io_stream_Allocate, io_stream_Finalize,
            {
                { "Write(_)",               io_stream_Write },
                { "Read()",                 io_stream_Read },
                { "Close()",                io_stream_Close }, 
            }
        },
        {
            "lib/xna/game", "GameImpl", xna_game_Allocate, xna_game_Finalize,
            {
                { "Update()",               xna_game_Update },
                { "Render()",               xna_game_Render },
                { "Tick()",                 xna_game_Tick },
                { "Dispose()",              xna_game_Dispose },
                { "HandleEvents()",         xna_game_HandleEvents },
                { "GameLoop()",             xna_game_GameLoop },
            }
        }
    };
    return (Class*)&metadata;
}
