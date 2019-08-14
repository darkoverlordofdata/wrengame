#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "tglm.h"

Type (Shader) 
{
    GLuint Id; 
};

Ctor (Shader)
{
    return this;

}

/**
 * Use shader
 */
Method Shader* Use(Shader* this)
{
    glUseProgram(this->Id);
    return this;
}

/**
 * CheckCompileErrors
 * 
 * Checks if compilation or linking failed and if so, print the error logs
 */
Method void CheckCompileErrors(
    Shader* this, 
    GLuint object, 
    char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (strncmp(type, "PROGRAM", 7) != 0)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            printf("| ERROR::SHADER: Compile-time error: Type: %s\n%s\n", type, infoLog);
            printf(" -- --------------------------------------------------- --\n");
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            printf("| ERROR::SHADER: Link-time error: Type: %s\n%s\n", type, infoLog);
            printf(" -- --------------------------------------------------- --\n");
        }
    }
}        

/**
 * Compile
 * 
 * @param vertexSource vertex shader source code
 * @param fragmentSource fragment shader source code
 * 
 */
Method void Compile(
    Shader* this, 
    const GLchar* vertexSource, 
    const GLchar* fragmentSource, 
    const GLchar* geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileErrors(this, sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileErrors(this, sFragment, "FRAGMENT");

    this->Id = glCreateProgram();
    glAttachShader(this->Id, sVertex);
    glAttachShader(this->Id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->Id, gShader);
    glLinkProgram(this->Id);
    CheckCompileErrors(this, this->Id, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);

} 

Method void SetFloat(
    Shader* this, 
    const GLchar *name, 
    GLfloat value, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform1f(glGetUniformLocation(this->Id, name), value);
}

Method void SetFloat(
    Shader* this, 
    const GLchar *name, 
    GLfloat value)
{
    SetFloat(this, name, value, true);
}

Method void SetInteger(
    Shader* this, 
    const GLchar *name, 
    GLint value, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform1i(glGetUniformLocation(this->Id, name), value);
}

Method void SetInteger(
    Shader* this, 
    const GLchar *name, 
    GLint value)
{
    SetInteger(this, name, value, true);
}

Method void SetVector2(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
}

Method void SetVector2(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y)
{
    SetVector2(this, name, x, y, true);
}

Method void SetVector2(
    Shader* this, 
    const GLchar *name, 
    const Vec2 value, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform2f(glGetUniformLocation(this->Id, name), value.x, value.y);
}

Method void SetVector2(
    Shader* this, 
    const GLchar *name, 
    const Vec2 value)
{
    SetVector2(this, name, value, true);
}

Method void SetVector3(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
}

Method void SetVector3(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z)
{
    SetVector3(this, name, x, y, z, true);
}

Method void SetVector3(
    Shader* this, 
    const GLchar *name, 
    const Vec3* value, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform3f(glGetUniformLocation(this->Id, name), value->x, value->y, value->z);
}

Method void SetVector3(
    Shader* this, 
    const GLchar *name, 
    const Vec3* value)
{
    SetVector3(this, name, value, true);
}

Method void SetVector4(
    Shader* this, 
    const GLchar *name,
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLfloat w, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
}

Method void SetVector4(
    Shader* this, 
    const GLchar *name,
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLfloat w)
{
    SetVector4(this, name, x, y, z, w, true);

}
Method void SetVector4(
    Shader* this, 
    const GLchar *name, 
    const Vec4 value, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniform4f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z, value.w);
}

Method void SetVector4(
    Shader* this, 
    const GLchar *name, 
    const Vec4 value)
{
    SetVector4(this, name, value, true);
}

Method void SetMatrix(
    Shader* this, 
    const GLchar *name, 
    const Mat* matrix, 
    GLboolean useShader)
{
    if (useShader)
        Use(this);
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, (GLfloat*)matrix);
}

Method void SetMatrix(
    Shader* this, 
    const GLchar *name, 
    const Mat* matrix)
{
    SetMatrix(this, name, matrix, true);
}

