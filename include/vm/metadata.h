#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "dark.h"
#include "lib/io/io.h"
#include "lib/xna/xna.h"

/**
 * Bind Wren Script api to native functions
 */
typedef struct WrenMethod
{
    char* name;
    void* addr;

} WrenMethod;

typedef struct Script 
{
    char* module;
    char* className;
    void* allocate;
    void* finalize;
    WrenMethod methods[100];

} Script;

#define WrenApi static inline void

static inline Script* GetMetaData()
{
    /**
     * native class bindings
     */
    static struct Script metadata[] = 
    {
        {
            "lib/io/path", "Path",  io_path_Allocate, io_path_Finalize,
            { 
                { "+Absolute",              io_path_Absolute },
                { "+Relative",              io_path_Relative },
                { "+Simple",                io_path_Simple },
                { "+Cwd",                   io_path_Cwd },
                { "+type(_)",               io_path_Type },
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
                { "DoUpdate()",             xna_game_DoUpdate },
                { "DoDraw()",               xna_game_DoDraw },
                { "Tick()",                 xna_game_Tick },
                { "Dispose()",              xna_game_Dispose },
                { "HandleEvents()",         xna_game_HandleEvents },
                { "Start()",                xna_game_Start },
                { "Run()",                  xna_game_Run },
                { "RunLoop()",              xna_game_RunLoop },
            }
        }
    };
    return (Script*)&metadata;
}
