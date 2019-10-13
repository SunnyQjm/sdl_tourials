//
// Created by mingj on 2019/10/13.
//
#include <iostream>

#define SDL2_HELPER_USE_SDL2_IMAGE

#include <SDL2Helper.h>
#include <fstream>
#include "res_path.h"

int main() {
    const std::string resPath = getResourcePath("Lesson3");
    const std::string imagePath = resPath + "image.png";
    const std::string backgroundPath = resPath + "background.png";
    SDL2Helper sdl2Helper(SDL_INIT_VIDEO);
    sdl2Helper
            .initSDL2Image(IMG_INIT_PNG)
            ->createWindow("Load from memory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480)
            ->createRenderer();

    std::ifstream is;
    is.open(imagePath, std::ios::binary | std::ios::in);
    char buffer[10000];
    is.read(buffer, 3342 * sizeof(char));
    is.close();
    SDL_Texture *imageTexture = sdl2Helper.loadTextureFromMemUseSDL2Image(buffer, 3342);
    is.open(backgroundPath, std::ios::binary);
    is.read(buffer, 9891 * sizeof(char));
    is.close();
    SDL_Texture *backgroundTexture = sdl2Helper.loadTextureFromMemUseSDL2Image(buffer, 9891);

    sdl2Helper.renderClear()
            ->renderTexture(backgroundTexture, 0, 0, 640, 480)
            ->renderTexture(imageTexture, 100, 100)
            ->renderPresent()
            ->delay(5000);

    return 0;
}