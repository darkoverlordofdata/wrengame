#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "resourcemanager.h"

//////////////////////////////////////////////////////////////////////////////////
///////  wren api bindings 
//////////////////////////////////////////////////////////////////////////////////

/**
 *  xna/game::Allocate
 */
WrenApi xna_game_Allocate(WrenVM* vm) 
{
    Game** game = (Game**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Game*));
    const char* title = wrenGetSlotString(vm, 1); 
    const int x = wrenGetSlotDouble(vm, 2);
    const int y = wrenGetSlotDouble(vm, 3);
    const int w = wrenGetSlotDouble(vm, 4);
    const int h = wrenGetSlotDouble(vm, 5);
    const int flags = wrenGetSlotDouble(vm, 6);

    *game = GameNew(nullptr, title, x, y, w, h, flags); 
}

/**
 *  xna/game::Finalize
 */
WrenApi xna_game_Finalize(void* data) 
{
    Game** game = (Game**)data;
    if (*game != nullptr) {
        Dispose(*game);
    }
}

/**
 *  xna/game::Update
 */
WrenApi xna_game_DoUpdate(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    DoUpdate(*game);
}

/**
 *  xna/game::Render
 */
WrenApi xna_game_DoDraw(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    DoDraw(*game);
}

/**
 *  xna/game::Tick
 */
WrenApi xna_game_Tick(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Tick(*game);
}

/**
 *  xna/game::Dispose
 */
WrenApi xna_game_Dispose(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Dispose(*game);
    *game = nullptr;
}
/**
 *  xna/game::HandleEvents
 */
WrenApi xna_game_HandleEvents(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    HandleEvents(*game);
}

/**
 *  xna/game::Start
 */
WrenApi xna_game_Start(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Start(*game);
}

/**
 *  xna/game::Run
 */
WrenApi xna_game_Run(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Run(*game);
}

/**
 *  xna/game::Run
 */
WrenApi xna_game_RunLoop(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    RunLoop(*game);
}
