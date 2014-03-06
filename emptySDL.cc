#include <stdio.h> 
#include <assert.h> 

#include <SDL.h> 
#include <SDL_opengles2.h> 

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
    SDL_GL_MakeCurrent(oWindow, oGlContext); 

    printf("GL_VERSION: %s\n", reinterpret_cast<const char *>(glGetString(GL_VERSION))); 
    printf("GL_SHADING_LANGUAGE_VERSION: %s\n", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION))); 

    /* Clear our buffer with a red background */ 
    glViewport(0, 0, 320, 480); 
    glClearColor(1, 0, 0, 1); 
    glClear(GL_COLOR_BUFFER_BIT); 
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
