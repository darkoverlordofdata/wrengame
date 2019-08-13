#pragma once

#ifndef strdup
static inline char* strdup(const char* s) {
    size_t len = strlen(s)+1;
    void* new = malloc(len);
    if (new == NULL) return NULL;
    return (char*)memcpy(new, s, len);
}
#endif

#include "xna/game.h"
#include "xna/resourcemanager.h"
#include "xna/shader.h"
#include "xna/spriterenderer.h"
#include "xna/texture2d.h"
