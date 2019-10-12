//
// Created by mingj on 19-10-12.
//

#include "SDL2Helper.h"

SDL2Helper *SDL2Helper::logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << "error: " << SDL_GetError() << std::endl;
    return this;
}

SDL2Helper::SDL2Helper(Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        logSDLError(std::cerr, "SDL_Init");
    } else {
        // initial SDL2 library success
        isSDL2Init = true;
    }
}

SDL2Helper *SDL2Helper::createWindow(SDL_Window *win, const std::string &title,
                                     int x, int y, int w, int h, Uint32 flags) {
    win = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (win == nullptr) {
        this->logSDLError(std::cerr, "CreateWindow")
                ->quit();
    } else {
        this->window = win;
    }
    return this;
}

#ifdef SDL2_HELPER_USE_SDL2_IMAGE

SDL2Helper *SDL2Helper::initSDL2Image(int flags) {
//    if(IMG_Init(flags))
    return this;
}

SDL2Helper *SDL2Helper::quit() {
#ifdef SDL2_HELPER_USE_SDL2_IMAGE
    if (isSDL2ImageInit) {
        IMG_Quit();
    }
#endif
#ifdef SDL2_HELPER_USE_SDL2_TTF
    if (isSDL2TtfInit) {
        TTF_Quit();
    }
#endif
    if (isSDL2Init) {
        SDL_Quit();
    }
    return this;
}

#endif
