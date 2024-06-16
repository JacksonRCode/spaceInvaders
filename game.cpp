//
//  game.cpp
//  spaceInvaders
//
//  Created by Jackson Reid on 2024-06-16.
//
#include "Game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xPos, int yPos, int screenWidth, int screenHeight, bool fullscreen) {
    
    isRunning = true;
    
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Initialization failed. SDL_ERROR: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
    
    window = SDL_CreateWindow(title, xPos, yPos, screenWidth, screenHeight, flags);
    if (window == nullptr) {
        std::cout << "Window creation failed. SDL_ERROR: " << SDL_GetError() <<std::endl;
        isRunning = false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        std::cout << "Renderer creation failed. SDL_ERROR: " << SDL_GetError() << std::endl;
        isRunning =  false;
    }
}
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
            
        default:
            break;
    }
}

void Game::update() {
    count++;
    if ((count % 1000) == 0) {
        
        std::cout << count << std::endl;
    }
}
    

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    // Add stuff to render here
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() {
    return isRunning;
}
