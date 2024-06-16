#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

class Game {
    
public:
    Game();
    ~Game();
    
    void init(const char* title, int xPos, int yPos, int screenWidth, int screenHeight, bool fullScreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running();
    
private:
    int count;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif /* Game_hpp */