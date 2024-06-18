//
//  game.cpp
//  spaceInvaders
//
//  Created by Jackson Reid on 2024-06-16.
//
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& ship(manager.addEntity());

Game::Game() {}
Game::~Game() {}


void Game::Init(const char *title, int xPos, int yPos, int screenWidth, int screenHeight, bool fullscreen) {
    
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
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    
    map = new Map();
    
    ship.addComponent<TransformComponent>();
    ship.addComponent<SpriteComponent>("grnSpaceShip.png");
}
void Game::HandleEvents() {
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

void Game::Update() {

    manager.refresh();
    manager.update();
    ship.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
    
    if(ship.getComponent<TransformComponent>().position.x > 100) {
        ship.getComponent<SpriteComponent>().setTexture("redDevil.png");
    }
}
    

void Game::Render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::Running() {
    return isRunning;
}
