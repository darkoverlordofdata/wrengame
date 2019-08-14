#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dark.h"
#include "tglm.h"
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
Type (GameObject)
{
    Vec2        Position;
    Vec2        Size;
    Vec2        Velocity;
    Vec3        Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    Texture2D*  Sprite;	
    char*       Name;
};

/**
 * Constructor
 * 
 * @param Position initial placement
 * @param Size sprite size
 * @param Sprite to display
 * @param Color tiniting color
 */
Ctor (GameObject,
    char* name,  
    Vec2 Position, 
    Vec2 Size, 
    Texture2D* Sprite, 
    Vec3 Color)
{
    this->IsSolid = false;
    this->Destroyed = false;
    this->Position = Position;
    this->Size = Size;
    this->Sprite = Sprite;
    this->Color = Color;
    this->Name = strdup(name);

    return this;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
Method void Draw(
    GameObject* const this, 
    SpriteRenderer* renderer)
{
    Draw(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
Method char* ToString(const GameObject* const this)
{
    return "GameObject";
} 
