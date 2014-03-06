#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>


const int win_width = 640;
const int win_height = 480;

// hack due problems with Visual Studio compilation
#undef main


int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // FIXME: don't work with depth size = 32
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    SDL_Window *window = SDL_CreateWindow("Empty SDL",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            win_width, win_height,
            SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    int status = SDL_GL_MakeCurrent(window, glcontext);
    if (status) {
        std::cerr << "Failed MakeCurrent" << SDL_GetError() << std::endl;
        return 1;
    }

    bool quit = false;
    while (!quit) {
        // process events
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
	    }
        }

        // draw
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);

        // delay
        SDL_Delay(100);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_Quit();
    return 0;
}
