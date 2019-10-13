//
// Created by ming on 19-10-11.
//
#include <iostream>
#include <string>
#define SDL2_HELPER_USE_SDL2_IMAGE
#include <SDL2Helper.h>
#include "res_path.h"

/**
 * Lesson3: SDL extension library
 */

// Screen attribute
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// We'll be scalling out tiles to be 40 * 40
const int TILE_SIZE = 40;

int main() {
    //Start up SDL and make sure it went ok
    SDL2Helper sdl2Helper(SDL_INIT_VIDEO);
    sdl2Helper
            .initSDL2Image(IMG_INIT_PNG)
            ->createWindow("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT)
            ->createRenderer();

    //The textures we'll be using
    const std::string resPath = getResourcePath("Lesson3");
    SDL_Texture *background = sdl2Helper.loadTextureUseSDL2Image(resPath + "background.png");
    SDL_Texture *image = sdl2Helper.loadTextureUseSDL2Image(resPath + "image.png");
    //Make sure they both loaded ok
    if (background == nullptr || image == nullptr) {
        SDLCleanUp::cleanup(background, image);
        sdl2Helper.quit();
        return 1;
    }

    //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; ++i) {
        //Clear the window
        sdl2Helper.renderClear();

        //Determine how many tiles we'll need to fill the screen
        int xTiles = SCREEN_WIDTH / TILE_SIZE;
        int yTiles = SCREEN_HEIGHT / TILE_SIZE;

        //Draw the tiles by calculating their positions
        for (int j = 0; j < xTiles * yTiles; ++j) {
            int x = j % xTiles;
            int y = j / xTiles;
            sdl2Helper.renderTexture(background, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }

        //Draw our image in the center of the window
        //We need the foreground image's width to properly compute the position
        //of it's top left corner so that the image will be centered
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        int x = SCREEN_WIDTH / 2 - iW / 2;
        int y = SCREEN_HEIGHT / 2 - iH / 2;
        sdl2Helper.renderTexture(image, x, y)
                ->renderPresent()
                ->delay(1000);
    }

    //Destroy the various items
    SDLCleanUp::cleanup(background, image);
    sdl2Helper.quit();
    return 0;
}

