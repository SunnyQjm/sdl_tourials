//
// Created by ming on 19-10-11.
//

#ifndef SDL_TOURIALS_RES_PATH_H
#define SDL_TOURIALS_RES_PATH_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

std::string getResourcePath(const std::string &subDir = "") {
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
    static std::string baseRes;

    if(baseRes.empty()) {
        char *basePath = SDL_GetBasePath();
        if(basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }

        // We replace the last bin/ with res/ to get the resource path
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

#endif //SDL_TOURIALS_RES_PATH_H
