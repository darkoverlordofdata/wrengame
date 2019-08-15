#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include "dark.h"

type (Texture2D)
{
    Object* Isa;
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint Id;
    // Texture image dimensions
    GLuint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLuint Internal_Format; // Format of texture object
    GLuint Image_Format; // Format of loaded image
    // Texture configuration
    GLuint mWrap_S; // Wrapping mode on S axis
    GLuint mWrap_T; // Wrapping mode on T axis
    GLuint mFilter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint mFilter_Mag; // Filtering mode if texture pixels > screen pixels
    char* mPath;
};

constructor (Texture2D, const char* path)
{
    this->Isa = nullptr;
    this->mPath = strdup(path);
    this->Internal_Format = GL_RGB;
    this->Image_Format = GL_RGB;
    this->mWrap_S = GL_REPEAT;
    this->mWrap_T = GL_REPEAT;
    this->mFilter_Min = GL_LINEAR;
    this->mFilter_Mag = GL_LINEAR;

    glGenTextures(1, &this->Id);
    
    return this;   
}



/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
method void Generate(
    Texture2D* this, 
    GLuint width, 
    GLuint height, 
    unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->mWrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->mWrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->mFilter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->mFilter_Mag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Bind
 * 
 * binds the texture to GL
 */
method void Bind(Texture2D* this)
{
    glBindTexture(GL_TEXTURE_2D, this->Id);    
}

/**
 * Dispose
 * 
 * release resources
 */
method void Dispose(Texture2D* this)
{
    free(this);
}
