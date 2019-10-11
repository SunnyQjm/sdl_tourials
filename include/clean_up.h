//
// Created by mingj on 19-10-11.
//

#ifndef SDL_TOURIALS_CLEAN_UP_H
#define SDL_TOURIALS_CLEAN_UP_H

#include <SDL2/SDL.h>
#include <utility>

template <typename T, typename... Args>
void cleanup(T *t, Args&&... args) {
    cleanup(t);
    cleanup(std::forward<Args>(args)...);
}


template <>
inline void cleanup<SDL_Window>(SDL_Window* win) {
    if(!win)
        return;
    SDL_DestroyWindow(win);
}


template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren){
    if (!ren){
        return;
    }
    SDL_DestroyRenderer(ren);
}
template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex){
    if (!tex){
        return;
    }
    SDL_DestroyTexture(tex);
}
template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surf){
    if (!surf){
        return;
    }
    SDL_FreeSurface(surf);
}
#endif //SDL_TOURIALS_CLEAN_UP_H
