//
//  main.cpp
//  spaceInvaders
//
//  Created by Jackson Reid on 2024-06-07.
//

#include "Game.hpp"

const char *TITLE = "Space Invaders";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

Game *game = nullptr;

int main(int argc, const char * argv[]) {
    Uint32 frameStart;
    int frameTime;
    
    game = new Game();
    
    game->Init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    
    while (game->Running()) {
        
        // GetTicks() gets time since sdl was first initialized
        frameStart = SDL_GetTicks();
        
        game->HandleEvents();
        game->Update();
        game->Render();
        
        // How long its taken to handle events, update, and render
        frameTime = SDL_GetTicks() - frameStart;
        
        // Delays frames -- fixed screen flicker as well
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        
    }
    
    game->Clean();
    
    return 0;
}
