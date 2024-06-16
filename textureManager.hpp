#ifndef textureManager_hpp
#define textureManager_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class TextureManager {
public:
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* fileName);
};

#endif /* textureManager_hpp */
