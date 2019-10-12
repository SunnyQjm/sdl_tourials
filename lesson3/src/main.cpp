//
// Created by ming on 19-10-11.
//
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "res_path.h"
#include "clean_up.h"

/**
 * Lesson3: SDL extension library
 */

// Screen attribute
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// We'll be scalling out tiles to be 40 * 40
const int TILE_SIZE = 40;


void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << "error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren) {
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    // Make sure convert went ok too
    if(texture == nullptr) {
        logSDLError(std::cout, "CreateTextureFromSurface");
    }
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    renderTexture(tex, ren, x, y, w, h);
}

int main() {
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }

    //Setup our window and renderer
    SDL_Window *window = SDL_CreateWindow("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    //The textures we'll be using
    const std::string resPath = getResourcePath("Lesson3");
    SDL_Texture *background = loadTexture(resPath + "background.png", renderer);
    SDL_Texture *image = loadTexture(resPath + "image.png", renderer);
    //Make sure they both loaded ok
    if (background == nullptr || image == nullptr){
        cleanup(background, image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; ++i){
        //Clear the window
        SDL_RenderClear(renderer);

        //Determine how many tiles we'll need to fill the screen
        int xTiles = SCREEN_WIDTH / TILE_SIZE;
        int yTiles = SCREEN_HEIGHT / TILE_SIZE;

        //Draw the tiles by calculating their positions
        for (int i = 0; i < xTiles * yTiles; ++i){
            int x = i % xTiles;
            int y = i / xTiles;
            renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }

        //Draw our image in the center of the window
        //We need the foreground image's width to properly compute the position
        //of it's top left corner so that the image will be centered
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        int x = SCREEN_WIDTH / 2 - iW / 2;
        int y = SCREEN_HEIGHT / 2 - iH / 2;
        renderTexture(image, renderer, x, y);

        //Update the screen
        SDL_RenderPresent(renderer);
        //Take a quick break after all that hard work
        SDL_Delay(1000);
    }

    //Destroy the various items
    cleanup(background, image, renderer, window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

