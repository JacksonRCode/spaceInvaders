#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <stdio.h>

class Game {
    
public:
    Game();
    ~Game();
    
    void Init(const char* title, int xPos, int yPos, int screenWidth, int screenHeight, bool fullScreen);
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool Running();
    
    static SDL_Renderer* renderer;
    static SDL_Event event;
private:
    int count;
    bool isRunning;
    SDL_Window *window;
};

#endif /* Game_hpp */
