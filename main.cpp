//
//  main.cpp
//  spaceInvaders
//
//  Created by Jackson Reid on 2024-06-07.
//

#include "Game.hpp"

const char *TITLE = "Space Invaders";
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

Game *game = nullptr;

int main(int argc, const char * argv[]) {
    game = new Game();
    
    game->init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    
    while (game->running()) {
        
        game->handleEvents();
        game->update(SCREEN_WIDTH, SCREEN_HEIGHT);
        game->render();
        
    }
    
    game->clean();
    
    return 0;
}
