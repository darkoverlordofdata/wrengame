#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
char* strdup(const char* s) {
    size_t len = strlen(s)+1;
    void* new = malloc(len);
    if (new == NULL) return NULL;
    return (char*)memcpy(new, s, len);
}
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
// #include "tglm.h"

typedef struct Game Game;
typedef void (*GameFn)(Game* game);
static void Game_Update(Game*);
static void Game_Render(Game*);
static void Game_Tick(Game*);
static void Game_Dispose(Game*);
static void Game_HandleEvents(Game*);
static void Game_GameLoop(Game*);

/**
 * The game object
 */
typedef struct Game
{
    GameFn Update;
    GameFn Render;
    GameFn Tick;
    GameFn Dispose;
    GameFn HandleEvents;
    GameFn GameLoop;
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Renderer *renderer;
    char* title;
    int x;
    int y;
    int h;
    int w;
    Uint32 flags;
    bool running;
    int sdlVersion;
    int gl_major_version;
    int gl_minor_version;
    int ticks;
    int fps;
    float factor;
    float delta;
    float mark1;
    float mark2;
    int mouseX;
    int mouseY;
    bool mouseDown;
    bool *keys;
} Game;

static inline void LogSDLError(const char* msg)
{
    printf("%s error: %s", msg, SDL_GetError());
}

/**
 * Update
 */
static inline void Game_Update(Game* game){
    if (game->keys[SDLK_ESCAPE]) {
        game->running = false;
    }
}

/**
 * Render
 */
static inline void Game_Render(Game* game) {
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // 100,149,237,255
    glClearColor(0.392156f, 0.584313f, 0.929411f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(game->window);
}

/**
 * HandleEvents
 */
static inline void Game_HandleEvents(Game* game) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            game->running = false;
            return;
            break;
        case SDL_KEYDOWN: 
            game->keys[ event.key.keysym.sym & 0xff ] = true;
            break;
        case SDL_KEYUP:   
            game->keys[ event.key.keysym.sym & 0xff ] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            game->mouseDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            game->mouseDown = false;
            break;
        case SDL_MOUSEMOTION:
            game->mouseX = event.motion.x;
            game->mouseY = event.motion.y;
            break;

        }
    }
}

/**
 * Tick
 */
static inline void Game_Tick(Game* game) {
    game->HandleEvents(game);
    game->Update(game);
    game->Render(game);
}

/**
 * Dispose
 */
static inline void Game_Dispose(Game* game) {
    SDL_DestroyWindow(game->window);
    free(game->title);
    free(game->keys);
    free(game);
    IMG_Quit();
    SDL_Quit();
}

/**
 * GameLoop
 */
static inline void Game_GameLoop(Game* game) {
#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)game->Tick, (void*)game, -1, 1);
#else
    while (true) {
        game->Tick(game);
        if (!game->running) break;
    }
#endif
}


/**
 * New Game
 */
static inline Game* GameNew(char* title, int x, int y, int w, int h, int flags)
{
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

    Game* game = malloc(sizeof(Game));
    game->sdlVersion = version;
    game->title = strdup(title);
    game->x = x;
    game->y = y;
    game->w = w;
    game->h = h;
    game->flags = flags;
    game->running = true;
    game->keys = calloc(256, sizeof(bool));
    game->gl_major_version = 3;
    #ifdef __EMSCRIPTEN__
    game->gl_minor_version = 0;
    #else
    game->gl_minor_version = 3;
    #endif

    /* Request opengl 3.3 context.*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, game->gl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, game->gl_minor_version);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    game->window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    game->context = SDL_GL_CreateContext(game->window);

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
    glViewport(0, 0, game->w, game->h);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // wrire up the methods
    game->Update = Game_Update;
    game->Render = Game_Render;
    game->Tick = Game_Tick;
    game->HandleEvents = Game_HandleEvents;
    game->Dispose = Game_Dispose;
    game->GameLoop = Game_GameLoop;
    return game;
}
