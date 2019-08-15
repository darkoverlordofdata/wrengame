#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "dark.h"
#include "resourcemanager.h"

#define TicksPerMillisecond  10000.0
#define MillisecondsPerTick 1.0 / (TicksPerMillisecond)

#define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
#define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
// #include "tglm.h"


// 100,149,237,255
#define bgd_r 0.392156f
#define bgd_g 0.584313f
#define bgd_b 0.929411f

/**
 * The game type
 */
type (Game)
{
    Object* Isa;
    SDL_Window *window;
    SDL_GLContext context;
    char* title;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    double delta;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;
    double factor;
    bool *keys;
    ResourceManager resource;
};

static inline uint64_t GetTicks() { 
    struct timeval t;     
    gettimeofday(&t, nullptr);

    uint64_t ts = t.tv_sec;
    uint64_t us = t.tv_usec;
    return ((ts * 1000000L) + us) * 10;
}


static inline void LogSDLError(const char* msg)
{
    printf("%s error: %s", msg, SDL_GetError());
}

/**
 * alloc Game
 */
// Constructor Game* Game_init(Game* this, char* title, int x, int y, int width, int height, int flags)
constructor(Game, char* title, int x, int y, int width, int height, int flags)
{
    this->Isa = nullptr;
    this->title = strdup(title);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->flags = flags;

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0) {
        LogSDLError("Unable to initialize SDL2");
        return nullptr;
    }
    SDL_version sversion;
    SDL_GetVersion(&sversion);
    int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
    if (version <= 204) {
        printf("Please use SDL 2.0.5 or higher.\n");
    } else {
        printf("Using SDL Vesion %d.%d.%d\n", sversion.major, sversion.minor, sversion.patch);
    }
    
    this->frameSkip = 0;
    this->isRunning = false;
    this->previousTicks = 0;
    this->isFixedTimeStep = true;
    this->shouldExit = false;
    this->suppressDraw = false;
    this->maxElapsedTime = 500 * TicksPerMillisecond; 
    this->targetElapsedTime = 166667;
    this->accumulatedElapsedTime = 0;
    this->currentTime = GetTicks();
    this->keys = calloc(256, sizeof(bool));
    this->sdlVersion = version;
    this->gl_major_version = 3;
    #ifdef __EMSCRIPTEN__
    this->gl_minor_version = 0;
    #else
    this->gl_minor_version = 3;
    #endif
    Init(&this->resource);

    /* Request opengl 3.3 context.*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->gl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->gl_minor_version);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->window = SDL_CreateWindow(this->title, 
                                    this->x, 
                                    this->y, 
                                    this->width, 
                                    this->height, 
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    this->context = SDL_GL_CreateContext(this->window);

    #ifdef __EMSCRIPTEN__
    const int img_flags = IMG_INIT_PNG;
    #else
    const int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    #endif
    if (IMG_Init(img_flags) != img_flags) { 
        LogSDLError("Init image");
    }
    TTF_Init();
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        LogSDLError("Init mixer");
    }

    #ifndef __EMSCRIPTEN__
    // Load OpenGL EntryPoints for desktop
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
    #endif

    // OpenGL configuration
    glViewport(0, 0, this->width, this->height);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return this;
}



/**
 * Update
 */
method void DoUpdate(Game* this){

    // Super(Game, DoUpdate);

    if (this->Isa != nullptr)
        DoUpdate((Game*)this->Isa);
 }

/**
 * Render
 */
method void DoDraw(Game* this) 
{
    glClearColor(bgd_r, bgd_g, bgd_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(this->window);
}

/**
 * HandleEvents
 */
method void HandleEvents(Game* this) 
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                this->isRunning = false;
                return;
                break;
            case SDL_KEYDOWN: 
                this->keys[ event.key.keysym.sym & 0xff ] = true;
                break;
            case SDL_KEYUP:   
                this->keys[ event.key.keysym.sym & 0xff ] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->mouseDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                this->mouseDown = false;
                break;
            case SDL_MOUSEMOTION:
                this->mouseX = event.motion.x;
                this->mouseY = event.motion.y;
                break;
        }
    }
}


method void Start(Game* this) 
{
    printf("Game::Start\n");
    this->isRunning = true;

}
/**
 * Tick
 */
method void Tick(Game* this) 
{
    while (true) {
        // Advance the accumulated elapsed time.
        long currentTicks = (GetTicks() - this->currentTime);//*10;
        this->accumulatedElapsedTime = this->accumulatedElapsedTime + currentTicks - this->previousTicks;
        this->previousTicks = (long)currentTicks;

        // If we're in the fixed timestep mode and not enough time has elapsed
        // to perform an update we sleep off the the remaining time to save battery
        // life and/or release CPU time to other threads and processes.
        if (this->isFixedTimeStep && this->accumulatedElapsedTime < this->targetElapsedTime)
        {
            int sleepTime = (int)((this->targetElapsedTime - this->accumulatedElapsedTime) * MillisecondsPerTick ); //).TotalMilliseconds();
            if (sleepTime < 1) { break; }
            // NOTE: While sleep can be inaccurate in general it is 
            // accurate enough for frame limiting purposes if some
            // fluctuation is an acceptable result.
            #ifndef usleep
            SDL_Delay(sleepTime);
            #else
            usleep(sleepTime*1000);
            #endif
            // goto RetryTick;
        }
        else break;
    }    
    // Do not allow any update to take longer than our maximum.
    if (this->accumulatedElapsedTime > this->maxElapsedTime)
        this->accumulatedElapsedTime = this->maxElapsedTime;

    if (this->isFixedTimeStep)
    {
        this->elapsedGameTime = this->targetElapsedTime;
        int stepCount = 0;

        // Perform as many full fixed length time steps as we can.
        while (this->accumulatedElapsedTime >= this->targetElapsedTime && !this->shouldExit)
        {
            this->totalGameTime += this->targetElapsedTime;
            this->accumulatedElapsedTime -= this->targetElapsedTime;
            ++stepCount;
            this->delta = (double)this->elapsedGameTime * SecondsPerTick;
            DoUpdate(this);
        }
        //Every update after the first accumulates lag
        this->updateFrameLag += Max(0, stepCount - 1);
        //If we think we are isRunning slowly, wait until the lag clears before resetting it
        if (this->isRunningSlowly)
        {
            if (this->updateFrameLag == 0)
            
                this->isRunningSlowly = false;
        }
        else if (this->updateFrameLag >= 5)
        {
            //If we lag more than 5 frames, start thinking we are isRunning slowly
            this->isRunningSlowly = true;
        }
        //Every time we just do one update and one draw, then we are not isRunning slowly, so decrease the lag
        if (stepCount == 1 && this->updateFrameLag > 0)
            this->updateFrameLag--;

        // Draw needs to know the total elapsed time
        // that occured for the fixed length updates.
        this->elapsedGameTime = this->targetElapsedTime * stepCount;
    }
    else
    {
        // Perform a single variable length update.
        this->elapsedGameTime = this->accumulatedElapsedTime;
        this->totalGameTime += this->accumulatedElapsedTime;
        this->accumulatedElapsedTime = 0;
        
        // Update();
        this->delta = (double)this->elapsedGameTime * SecondsPerTick;
        DoUpdate(this);
    }
    // Draw unless the update suppressed it.
    if (this->suppressDraw)
        this->suppressDraw = false;
    else
    {
        // Draw();
        DoDraw(this);
    }

    if (this->shouldExit) 
        this->isRunning = false;
        // Platform.Exit();
}

/**
 * Dispose
 */
method void Dispose(Game* this) 
{
    SDL_DestroyWindow(this->window);
    free(this->title);
    free(this->keys);
    free(this);
    IMG_Quit();
    SDL_Quit();
}

method void RunLoop(Game* this)
{
    HandleEvents(this);
    if (this->keys[SDLK_ESCAPE]) {
        this->shouldExit = true;
    }
    Tick(this);
}

/**
 * GameLoop
 */
method void Run(Game* this) 
{
    // this->Initialize(this);
    // this->LoadContent(this);
    Start(this);
#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)RunLoop, (void*)this, -1, 1);
#else
    while (this->isRunning) 
    {
        RunLoop(this);
    }
#endif
}


// /**
//  * alloc Game
//  */
// // Constructor Game* Game_init(Game* this, char* title, int x, int y, int width, int height, int flags)
// constructor(Game, char* title, int x, int y, int width, int height, int flags)
// {
//     if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0) {
//         LogSDLError("Unable to initialize SDL2");
//         return nullptr;
//     }
//     SDL_version sversion;
//     SDL_GetVersion(&sversion);
//     int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
//     if (version <= 204) {
//         printf("Please use SDL 2.0.5 or higher.\n");
//     } else {
//         printf("Using SDL Vesion %d.%d.%d\n", sversion.major, sversion.minor, sversion.patch);
//     }

//     this->Isa = nullptr;
//     this->title = strdup(title);
//     this->x = x;
//     this->y = y;
//     this->width = width;
//     this->height = height;
//     this->flags = flags;
    
//     this->frameSkip = 0;
//     this->isRunning = false;
//     this->previousTicks = 0;
//     this->isFixedTimeStep = true;
//     this->shouldExit = false;
//     this->suppressDraw = false;
//     this->maxElapsedTime = 500 * TicksPerMillisecond; 
//     this->targetElapsedTime = 166667;
//     this->accumulatedElapsedTime = 0;
//     this->currentTime = GetTicks();
//     this->keys = calloc(256, sizeof(bool));
//     this->sdlVersion = version;
//     this->gl_major_version = 3;
//     #ifdef __EMSCRIPTEN__
//     this->gl_minor_version = 0;
//     #else
//     this->gl_minor_version = 3;
//     #endif
//     Init(&this->resource);

//     /* Request opengl 3.3 context.*/
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->gl_major_version);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->gl_minor_version);

//     /* Turn on double buffering with a 24bit Z buffer.
//      * You may need to change this to 16 or 32 for your system */
//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

//     this->window = SDL_CreateWindow(this->title, 
//                                     this->x, 
//                                     this->y, 
//                                     this->width, 
//                                     this->height, 
//                                     SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
//     this->context = SDL_GL_CreateContext(this->window);

//     #ifdef __EMSCRIPTEN__
//     const int img_flags = IMG_INIT_PNG;
//     #else
//     const int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
//     #endif
//     if (IMG_Init(img_flags) != img_flags) { 
//         LogSDLError("Init image");
//     }
//     TTF_Init();
//     if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
//         LogSDLError("Init mixer");
//     }

//     #ifndef __EMSCRIPTEN__
//     // Load OpenGL EntryPoints for desktop
//     glewExperimental = GL_TRUE;
//     glewInit();
//     glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
//     #endif

//     // OpenGL configuration
//     glViewport(0, 0, this->width, this->height);
//     glEnable(GL_CULL_FACE);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     return this;
// }

