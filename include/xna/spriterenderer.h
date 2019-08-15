#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include "texture2d.h"
#include "shader.h"
#include "dark.h"

type (SpriteRenderer)
{
    Object* Isa;
    Shader* mShader; 
    GLuint mQuadVAO;
};

method void InitRenderData(SpriteRenderer* this);

constructor (SpriteRenderer, Shader* shader)
{
    this->Isa = nullptr;
    this->mShader = shader;
    InitRenderData(this);
    return this;   
}

/**
 * Draw
 * 
 * @param texture the image to render
 * @param position to render at
 * @param size to render
 * @param rotate amount to rotate by
 * @param color to tint
 * 
 */
method void Draw(
    SpriteRenderer* this, 
    Texture2D* texture, 
    Vec2 position, 
    Vec2 size, 
    GLfloat 
    rotate, 
    Vec3 color)
{
    // printf("%s (%d,%d)\n", texture.Path, texture.Width, texture.Height);
    // Prepare transformations
    Use(this->mShader);
    Mat model= {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    model = glm_translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    model = glm_translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    model = glm_rotate(model, rotate, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    model = glm_translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back
    model = glm_scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale

    SetMatrix(this->mShader, "model", &model);

    // Render textured quad
    SetVector3(this->mShader, "spriteColor", &color);

    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(this->mQuadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


method void InitRenderData(SpriteRenderer* this)
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = { 
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->mQuadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->mQuadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}          

method void Dispose(SpriteRenderer* this)
{
    glDeleteVertexArrays(1, &this->mQuadVAO);
    free(this);
}

