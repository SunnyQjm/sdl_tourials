//
// Created by mingj on 19-10-11.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "clean_up.h"
#include "res_path.h"

/**
 * Lesson2 Don't put Everything in Main
 */

// Screen attribute
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << "error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren) {
    SDL_Texture *texture = nullptr;

    // Load image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    // If the loading went ok, convert to texture and return texture
    if(loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        cleanup(loadedImage);
        // Make sure convert went ok too
        if(texture == nullptr) {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    } else {
        logSDLError(std::cout, "LoadBmp");
    }
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
    // Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    // Query the texture to get its width and height to use
    SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, nullptr, &dst);
}


int main() {
    // Start up SDL and make sure it went ok
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(std::cout, "SDL_INIT");
        return 1;
    }

    // Setup out window and renderer
    SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr)  {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    // Get the Texture we we'll be using
    const std::string resPath = getResourcePath("Lesson2");
    SDL_Texture *background = loadTexture(resPath + "background.bmp", ren);
    SDL_Texture *image = loadTexture(resPath + "image.bmp", ren);
    // Make sure they both ok
    if(background == nullptr || image == nullptr) {
        cleanup(background, image, ren, window);
        SDL_Quit();
        return 1;
    }

    // A Sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; i++) {
        // Clear the window
        SDL_RenderClear(ren);

        // Get the width and height from the texture so we know how much to move x,y
        // to tile it correctly
        int bW, bH;
        SDL_QueryTexture(background, nullptr, nullptr, &bW, &bH);
        // We want to tile our background, so draw it 4 times
        renderTexture(background, ren, 0, 0);
        renderTexture(background, ren, bW, 0);
        renderTexture(background, ren, 0, bH);
        renderTexture(background, ren, bW, bH);


        // Draw image in the center of the window
        // We need the foreground image's width to properly compute the postion
        // of it's top left corner so that the image will be centered
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;
		renderTexture(image, ren, x, y);

		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
    }

    cleanup(background, image, ren, window);
	SDL_Quit();

	return 0;

}