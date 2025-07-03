#pragma once
#include <raylib.h>
#include "gameObject.h"
#include <vector>
#include "UI.h"
class Pipe : public GameObject
{
private:
    bool enterable;
    UI *ui;
    std::vector<Texture2D> pipeTextures;
    int index = 0;

public:
    Pipe(int x = 0, int y = 0, int width = 0, int height = 0, int index = 0, int scale = 0, bool enterable = false, UI *ui = nullptr);
    
    // Update
    void tick();
    void render();
    
    // Check for collision
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();
    void showBounds();

    // 

    ~Pipe() = default; // Default destructor
};