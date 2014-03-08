#include <stdio.h> 
#include <assert.h> 

#include <SDL.h> 
#include <SDL_opengles2.h> 


typedef struct GLES2_Context
{
#define SDL_PROC(ret,func,params) ret (APIENTRY *func) params;
#include "parentdir_src_render_opengles2_SDL__gles2funcs.h"
#undef SDL_PROC
} GLES2_Context;

static GLES2_Context ctx;

static int LoadContext(GLES2_Context * data)
{
#if SDL_VIDEO_DRIVER_UIKIT
#define __SDL_NOGETPROCADDR__
#elif SDL_VIDEO_DRIVER_ANDROID
#define __SDL_NOGETPROCADDR__
#elif SDL_VIDEO_DRIVER_PANDORA
#define __SDL_NOGETPROCADDR__
#endif

#if defined __SDL_NOGETPROCADDR__
#define SDL_PROC(ret,func,params) data->func=func;
#else
#define SDL_PROC(ret,func,params) \
    do { \
        data->func = (ret (APIENTRY *) params) SDL_GL_GetProcAddress(#func); \
        if ( ! data->func ) { \
            return SDL_SetError("Couldn't load GLES2 function %s: %s\n", #func, SDL_GetError()); \
        } \
    } while ( 0 );
#endif /* _SDL_NOGETPROCADDR_ */

#include "parentdir_src_render_opengles2_SDL__gles2funcs.h"
#undef SDL_PROC
    return 0;
}


// hack for Visual Studio
#undef main

int main(int _nArg, char *_aArg[]) 
{ 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0); 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 

    assert(SDL_Init(SDL_INIT_EVERYTHING) == 0); 

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 

    SDL_Window * oWindow = SDL_CreateWindow("Default", 100, 100, 320, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); 
    assert(oWindow); 
    SDL_GLContext oGlContext = SDL_GL_CreateContext(oWindow); 
    assert(oGlContext); 

    if (LoadContext(&ctx) < 0) {
        printf("Could not load GLES2 functions\n");
        SDL_GL_DeleteContext(oGlContext);
        return 0;
    }

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    printf("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
    printf("\n");
    // print loaded context info
    printf("Vendor       : %s\n", ctx.glGetString(GL_VENDOR));
    printf("Renderer     : %s\n", ctx.glGetString(GL_RENDERER));
    printf("Version      : %s\n", ctx.glGetString(GL_VERSION));
    printf("Extensions   : %s\n", ctx.glGetString(GL_EXTENSIONS));
    printf("GLSL version : %s\n", ctx.glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("\n");
    // print default context info
    printf("Vendor       : %s\n", glGetString(GL_VENDOR));
    printf("Renderer     : %s\n", glGetString(GL_RENDERER));
    printf("Version      : %s\n", glGetString(GL_VERSION));
    printf("Extensions   : %s\n", glGetString(GL_EXTENSIONS));
    printf("GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("\n");

    SDL_GL_MakeCurrent(oWindow, oGlContext); 

    /* Clear our buffer with a red background */ 
    ctx.glViewport(0, 0, 320, 480); 
    ctx.glClearColor(1, 0, 0, 1); 
    ctx.glClear(GL_COLOR_BUFFER_BIT); 
    SDL_GL_SwapWindow(oWindow); 

    bool quit = false;
    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(100); 
    }
    SDL_GL_DeleteContext(oGlContext); 
    SDL_DestroyWindow(oWindow); 

    SDL_Quit(); 
    return 0; 
} 
