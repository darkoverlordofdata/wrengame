#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "texture2d.h"
#include "shader.h"

type (ResourceManager)
{
    Object* Isa;
    Map* Shaders;
    Map* Textures;
};

method Shader* LoadShaderFromFile(ResourceManager* this, const GLchar *vShaderFile, const GLchar *fShaderFile);
method Texture2D* LoadTextureFromFile(ResourceManager* this, const GLchar *file, GLboolean alpha);

method void Init(ResourceManager* this)
{
    this->Shaders = new(Map);
    this->Textures = new(Map);
}

constructor (ResourceManager)
{
    this->Isa = nullptr;
    Init(this);
    return this;
}

method void Dispose(ResourceManager* this)
{
    Dispose(this->Shaders);
    Dispose(this->Textures);
    free(this);
}

/**
 * LoadShader
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @param name to cache as
 * @returns loaded, compiled and linked shader program
 */
method Shader* LoadShader(
    ResourceManager* this, 
    const GLchar *vShaderFile, 
    const GLchar *fShaderFile, 
    const char* name)
{
    Put(this->Shaders, name, LoadShaderFromFile(this, vShaderFile, fShaderFile));
    return Get(this->Shaders, name);
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
method Shader* GetShader(
    ResourceManager* this, 
    const char* name)
{
    return Get(this->Shaders, name);    
}

/**
 * loadTexture
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @param name to cache as
 * @returns Texture
 * 
 */
method Texture2D* LoadTexture(
    ResourceManager* this, 
    const GLchar *file, 
    GLboolean alpha,
    const char* name)
{
    Put(this->Textures, name, LoadTextureFromFile(this, file, alpha));
    return Get(this->Textures, name);
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
method Texture2D* GetTexture(
    ResourceManager* this, 
    const char* name)
{
    return Get(this->Textures, name);    
}

method void Clear(ResourceManager* this)
{
    Dispose(this->Shaders);
    Dispose(this->Textures);
    this->Shaders = new(Map);
    this->Textures = new(Map);

}

// static inline char* join(const char* s1, const char* s2) { return nullptr;}
/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */
method Shader* LoadShaderFromFile(
    ResourceManager* this, 
    const GLchar *vShaderFile, 
    const GLchar *fShaderFile)
{
    char* vFile = Join("assets/", vShaderFile);
    char* fFile = Join("assets/", fShaderFile);

    FILE* vertexShaderFile = fopen(vFile, "r");
    FILE* fragmentShaderFile = fopen(fFile, "r");

    if (!vertexShaderFile) SDL_Log("Unable to open %s", vShaderFile);
    if (!fragmentShaderFile) SDL_Log("Unable to open %s", fShaderFile);

    // Read file's buffer contents into streams
    const GLchar *vShaderCode = ReadTextFile(vertexShaderFile);
    const GLchar *fShaderCode = ReadTextFile(fragmentShaderFile);
    // close file handlers
    fclose(vertexShaderFile);
    fclose(fragmentShaderFile);

    // 2. Now create shader object from source code
    Shader* shader = new(Shader);
    Compile(shader, vShaderCode, fShaderCode, nullptr);
    return shader;

}

/**
 * loadTextureFromFile
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @returns Texture
 * 
 */
method Texture2D* LoadTextureFromFile(
    ResourceManager* this, 
    const GLchar *file, 
    GLboolean alpha)
{
    // Create Texture object
    Texture2D* texture = new(Texture2D, (char*)file);
    if (alpha)
    {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format = GL_RGBA;
    }
    // Load image
    int width, height;
    
    SDL_Surface * surface = IMG_Load(file);
    if (SDL_MUSTLOCK(surface)) 
        SDL_LockSurface(surface);
    // Now generate texture
    printf("%s: (%d,%d)\n", file, surface->w, surface->h);
    Generate(texture, surface->w, surface->h, (unsigned char*)surface->pixels);
    if (SDL_MUSTLOCK(surface)) 
        SDL_UnlockSurface(surface);
    // And finally free image data
    SDL_FreeSurface(surface);
    return texture;

}
