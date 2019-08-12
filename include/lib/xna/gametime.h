#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../dark.h"
#include "../../wren.h"
#include "../../vm/config.h"

typedef struct GameTime GameTime;

typedef struct GameTime
{
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    bool isRunningSlowly;

} GameTime;

static inline 
GameTime NewGameTime() 
{
    GameTime this;
    this.totalGameTime = 0;
    this.elapsedGameTime = 0;
    this.isRunningSlowly = false;
    return this;
}
