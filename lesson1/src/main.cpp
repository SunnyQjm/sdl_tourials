//
// Created by ming on 19-10-11.
//

#include <iostream>
#include "SDL2Helper.h"
#include "res_path.h"

int main() {

    SDL2Helper sdl2Helper(SDL_INIT_VIDEO);
    sdl2Helper
            .createWindow("Hello World1", 100, 100, 640, 480)       // Open Window
            ->createRenderer();                                                         // Create Renderer

    // Load a Bitmap Image
    std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
    SDL_Surface *bmp = sdl2Helper.loadBMP(imagePath);

    // Create Texture from Surface
    SDL_Texture *tex = sdl2Helper.createTextureFromSurface(bmp);
    SDL_free(bmp);

    // Drawing the Texture
    for (int i = 0; i < 3; i++) {
        // First clear the renderer
        sdl2Helper.renderClear()
                ->renderCopy(tex)       // Draw the Texture
                ->renderPresent()       // Update the screen
                ->delay(1000);      // Take a quick break after all that hard work
    }

    // Before Exit, we need to clean and destroy all SDL object
    sdl2Helper.quit();

    return 0;
}