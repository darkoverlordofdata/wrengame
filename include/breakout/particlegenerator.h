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

// Represents a single particle and its state
type (Particle)
{
    Vec2 Position;
    Vec2 Velocity;
    Vec4 Color;
    GLfloat Life;

    // Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
type (ParticleGenerator) 
{
    Object* Isa;
    Particle* particles;
    GLuint amount;
    Shader* shader;
    Texture2D* texture;
    GLuint VAO;
};

/**
 * ParticleGenerator
 * 
 * @param shader to use
 * @param texture to source from
 * @param amount number of particles to generate
 * 
 */
constructor (ParticleGenerator*,
    Shader* shader, 
    Texture2D* texture, 
    int amount)
{
    this->shader = shader;
    this->texture = texture;
    this->amount = amount;
    init(this);
    return this;
}

/**
 * Update
 * 
 * @param dt delta time
 * @param object GameObject
 * @param newParticles count
 * @param offset to display from
 * 
 */
method void Update(
    ParticleGenerator* this, 
    GLfloat dt, 
    GameObject* object, 
    GLuint newParticles, 
    Vec2 offset)
{
    // Add new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle(this);
        respawnParticle(this, this->particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i)
    {
        this->particles[i].Life -= dt; // reduce life
        if (this->particles[i].Life > 0.0f)
        {	// particle is alive, thus update
                    
            this->particles[i].Position -= this->particles[i].Velocity * dt; 
            this->particles[i].Color[3] -= dt * 2.5;
        }
    }
}

/**
 * Render all particles
 * 
 */
method void Draw(ParticleGenerator* this)
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Use(this->shader);
    for (int i=0; i<this->amount; i++)
    {
        struct Particle particle = this->particles[i];
        if (particle.Life > 0.0f)
        {
            SetArray2(this->shader, "offset", &particle.Position);
            SetArray4(this->shader, "color", &particle.Color);
            Bind(this->texture);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * initialize generator
 */
static void init(ParticleGenerator* this)
{
    // Set up mesh and attribute properties
    GLuint VBO;
    GLfloat particle_quad[24] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    this->particles = DSmalloc(sizeof(Particle) * this->amount);
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
static GLuint firstUnusedParticle(ParticleGenerator* this)
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

static void respawnParticle(
    ParticleGenerator* this, 
    struct Particle particle, 
    GameObject* object, 
    Vec2 offset)
{
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle.Position = object->Position + random + offset;
    particle.Color = (Vec4){ rColor, rColor, rColor, 1.0f };
    particle.Life = 1.0f;
    particle.Velocity = object->Velocity * 0.1f;
}

/**
 * ToString
 */
method char* ToString(const ParticleGenerator* const this)
{
    return "ParticleGenerator";
}


