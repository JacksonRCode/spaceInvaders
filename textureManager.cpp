#include "textureManager.hpp"

SDL_Texture* TextureManager::loadTexture(SDL_Renderer* renderer, const char* fileName) {
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;
}
