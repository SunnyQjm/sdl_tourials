//
// Created by mingj on 19-10-12.
//

#include "SDL2Helper.h"

SDL2Helper *SDL2Helper::logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << "\nerror: " << SDL_GetError() << std::endl;
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


#ifdef SDL2_HELPER_USE_SDL2_IMAGE

SDL2Helper *SDL2Helper::initSDL2Image(int flags) {
//    if(IMG_Init(flags))
    return this;
}

#endif


SDL2Helper *SDL2Helper::createWindow(const std::string &title,
                                     int x, int y, int w, int h, Uint32 flags) {
    window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (window == nullptr) {
        this->logSDLError(std::cerr, "CreateWindow")
                ->quit();
    }
    return this;
}

SDL2Helper *SDL2Helper::createRenderer(int index, Uint32 flags) {
    if (this->window == nullptr) {
        logSDLError(std::cerr, "Please invoke createWindow to create a SDL_Window object success first!");
        return this;
    }
    renderer = SDL_CreateRenderer(this->window, index, flags);
    if (renderer == nullptr) {
        this->logSDLError(std::cerr, "CreateRenderer")
                ->quit();
    }
    return this;
}

SDL2Helper *SDL2Helper::quit() {
    SDLCleanUp::cleanup(renderer, window);
#ifdef SDL2_HELPER_USE_SDL2_IMAGE
    if (isSDL2ImageInit) {
        IMG_Quit();
        isSDL2ImageInit = false;
    }
#endif
#ifdef SDL2_HELPER_USE_SDL2_TTF
    if (isSDL2TtfInit) {
        TTF_Quit();
        isSDL2TtfInit = false;
    }
#endif
    if (isSDL2Init) {
        SDL_Quit();
        isSDL2Init = false;
    }
    return this;
}

SDL_Window *SDL2Helper::getWindow() {
    return this->window;
}

SDL_Renderer *SDL2Helper::getRenderer() {
    return this->renderer;
}

SDL_Surface *SDL2Helper::loadBMP(const std::string &filePath) {
    SDL_Surface *bmp = SDL_LoadBMP(filePath.c_str());
    if (bmp == nullptr) {
        SDLCleanUp::cleanup(this->renderer, this->window);
        this->logSDLError(std::cerr, "SDL_LoadBMP -> " + filePath)
                ->quit();
    }
    return bmp;
}

SDL_Texture *SDL2Helper::createTextureFromSurface(SDL_Surface *surface) {
    SDL_Texture *tex = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (tex == nullptr) {
        SDLCleanUp::cleanup(this->renderer, this->window);
        this->logSDLError(std::cerr, "SDL_CreateTextFromSurface")
                ->quit();
    }
    return tex;
}

SDL2Helper *SDL2Helper::renderClear() {
    SDL_RenderClear(this->renderer);
    return this;
}

SDL2Helper *SDL2Helper::renderCopy(SDL_Texture *texture, const SDL_Rect *srcRect, const SDL_Rect *dstRect) {
    SDL_RenderCopy(this->renderer, texture, srcRect, dstRect);
    return this;
}

SDL2Helper *SDL2Helper::renderPresent() {
    SDL_RenderPresent(this->renderer);
    return this;
}

SDL2Helper *SDL2Helper::delay(Uint32 ms) {
    SDL_Delay(ms);
    return this;
}






