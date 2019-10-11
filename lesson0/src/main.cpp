//
// Created by ming on 19-10-11.
//
#include <iostream>
#include <SDL2/SDL.h>
#include "res_path.h"

using namespace std;

int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_INIT error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Resource path is: " << getResourcePath() << std::endl;
    SDL_Quit();
    return 0;
}