//
// Created by ming on 19-10-11.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "res_path.h"
#include <clean_up.h>

int main() {

    // Init
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Open a Window
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(win == nullptr) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Creating a Renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Load a Bitmap Image
    std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if(bmp == nullptr) {
        cleanup(ren, win);
//        SDL_DestroyRenderer(ren);
//        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_free(bmp);
    if(tex == nullptr) {
        cleanup(ren, win);
//        SDL_DestroyRenderer(ren);
//        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Drawing the Texture
    for (int i = 0; i < 3; i++) {
        // First clear the renderer
        SDL_RenderClear(ren);
        // Draw the Texture
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        // Update the screen
        SDL_RenderPresent(ren);
        // Take a quick break after all that hard work
        SDL_Delay(1000);
    }

    // Before Exit, we need to clean and destroy all SDL object
    cleanup(tex, ren, win);
//    SDL_DestroyTexture(tex);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}