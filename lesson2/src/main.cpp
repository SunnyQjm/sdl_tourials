//
// Created by mingj on 19-10-11.
//

#include <iostream>
#include "SDL2Helper.h"
#include "res_path.h"

/**
 * Lesson2 Don't put Everything in Main
 */

// Screen attribute
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
    // Start up SDL and make sure it went ok
    SDL2Helper sdl2Helper(SDL_INIT_VIDEO);
    sdl2Helper
            .createWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT)
            ->createRenderer();

    // Get the Texture we we'll be using
    const std::string resPath = getResourcePath("Lesson2");
    SDL_Texture *background = sdl2Helper.loadTextureFromBMP(resPath + "background.bmp");
    SDL_Texture *image = sdl2Helper.loadTextureFromBMP(resPath + "image.bmp");
    // Make sure they both ok
    if (background == nullptr || image == nullptr) {
        SDLCleanUp::cleanup(background, image);
        sdl2Helper.quit();
        return 1;
    }

    // A Sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; i++) {
        sdl2Helper.renderClear();

        // Get the width and height from the texture so we know how much to move x,y
        // to tile it correctly
        int bW, bH;
        SDL_QueryTexture(background, nullptr, nullptr, &bW, &bH);
        // We want to tile our background, so draw it 4 times
        sdl2Helper.renderTexture(background, 0, 0)
                ->renderTexture(background, bW, 0)
                ->renderTexture(background, 0, bH)
                ->renderTexture(background, bW, bH);


        // Draw image in the center of the window
        // We need the foreground image's width to properly compute the postion
        // of it's top left corner so that the image will be centered
        int iW, iH;
        SDL_QueryTexture(image, nullptr, nullptr, &iW, &iH);
        int x = SCREEN_WIDTH / 2 - iW / 2;
        int y = SCREEN_HEIGHT / 2 - iH / 2;
        sdl2Helper.renderTexture(image, x, y)
                ->renderPresent()
                ->delay(1000);
    }

    SDLCleanUp::cleanup(background, image);
    sdl2Helper.quit();
    return 0;

}