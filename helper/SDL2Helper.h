//
// Created by mingj on 19-10-12.
//

#ifndef SDL_TOURIALS_SDL2HELPER_H
#define SDL_TOURIALS_SDL2HELPER_H
#define SDL2_HELPER_USE_SDL2_IMAGE
#define SDL2_HELPER_USE_SDL2_TTF

#include <iostream>
#include <SDL2/SDL.h>

// Judge if use SDL2_image extension library
#ifdef SDL2_HELPER_USE_SDL2_IMAGE
#include <SDL2/SDL_image.h>
#endif

// Judge if use SDL2_ttf extension library
#ifdef SDL2_HELPER_USE_SDL2_TTF
#include <SDL2/SDL_ttf.h>
#endif

class SDL2Helper {
private:
    bool isSDL2Init = false;
    bool isSDL2ImageInit = false;
    bool isSDL2TtfInit = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

public:

    /**
     * Create SDL2Helper Object and init SDL2 library
     * @param flags is the param of SDL2_Init
     */
    SDL2Helper(Uint32 flags);

    /**
     * The Wrapper of SDL_CreateWindow
     * @param win           if create success, win will indicate the window created now
     * the other param is same as SDL_CreateWindow
     * @return
     */
    SDL2Helper* createWindow(
            SDL_Window* win,
            const std::string& title, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED,
            int w = 640, int h = 480, Uint32 flags = SDL_WINDOW_SHOWN
            );


    ///////////////////////////////////////////////////////////
    ///////// SDL2_image's wrapper functions
    ///////////////////////////////////////////////////////////
#ifdef SDL2_HELPER_USE_SDL2_IMAGE

    /**
     * init SDL2_Image library
     * @param flags see IMG_InitFlags
     * @return
     */
    SDL2Helper *initSDL2Image(int flags);
#endif


    //////////////////////////////////////////////////////////
    ///////// Utils
    //////////////////////////////////////////////////////////
    SDL2Helper *logSDLError(std::ostream &os, const std::string &msg);
    SDL2Helper *quit();

    /**
     * 析构时释放所有的资源
     */
    ~SDL2Helper() {
        // Destroy
        this->quit();
    }
};


#endif //SDL_TOURIALS_SDL2HELPER_H
