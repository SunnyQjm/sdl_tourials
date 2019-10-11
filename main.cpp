#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

string getResourcePath(const string &subDir = "") {
//    const char PATH_SEP = "/";
    static string baseRes;
    if(baseRes.empty()) {
        char *basePath = SDL_GetBasePath();
        if(basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            cerr << "Error getting resource path: " << SDL_GetError() << endl;
            return "";
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}