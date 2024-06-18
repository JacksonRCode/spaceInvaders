#pragma once

#include "Components.hpp"

// Inherits publicly from class Component
class PositionComponent : public Component {
private:
    int xPos;
    int yPos;
    
public:
    
    PositionComponent() {
        xPos = 0;
        yPos = 0;
    }
    
    PositionComponent(int x, int y) {
        xPos = x;
        yPos = y;
    }
    
    void update() override {
        xPos++;
        yPos++;
    }
    
    int x() {return xPos;}
    void x(int x) { xPos = x; }
     
    int y() {return yPos;}
    void y(int y) { yPos = y; }
    
    void setPos(int x, int y) {
        xPos = x;
        yPos = y;
    }
    
};

