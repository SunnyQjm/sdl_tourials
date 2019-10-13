//
// Created by mingj on 19-10-12.
//

#include <iostream>
#include <string>

#define SDL2_HELPER_USE_SDL2_IMAGE

#include <SDL2Helper.h>
#include "res_path.h"

/**
 * Lesson 4: Handling Event
 */

// Screen attribute
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {

    SDL2Helper sdl2Helper(SDL_INIT_VIDEO);
    sdl2Helper
            .createWindow("Lesson 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT)
            ->createRenderer();

    //The texture we'll be using
    const std::string resPath = getResourcePath("Lesson4");
    SDL_Texture *image = sdl2Helper.loadTextureUseSDL2Image(resPath + "image.png");
    if (image == nullptr) {
        SDLCleanUp::cleanup(image);
        sdl2Helper.quit();
        return 1;
    }

    //Our texture size won't change, so we can get it here
    //instead of constantly allocating/deleting ints in the loop
    int iW, iH;
    SDL_QueryTexture(image, nullptr, nullptr, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    // Our Event struct
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Read any Events that occured, for now we'll just quit if any event occurs
        while (SDL_PollEvent(&e)) {
            // If user close the window
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // If user press any key
            if (e.type == SDL_KEYDOWN) {
                quit = true;
            }

            // If user clicks the mouse
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                quit = true;
            }
        }
        sdl2Helper.renderClear()
                ->renderTexture(image, x, y)
                ->renderPresent();
    }

    // Destroy the various items
    SDLCleanUp::cleanup(image);
    sdl2Helper.quit();
    return 0;
}