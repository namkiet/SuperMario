#pragma once
#include <vector>
#include "raylib.h"
#include "UI.h"
class Debris
{
private:
    // Debris texture
    std::vector<Texture2D> debris;

    Image debris_sheet;
    int scale;
    int width, height;
    float velX, velY;
    std::vector<float> x;
    std::vector<float> y;
    UI *ui;

public:
    Debris(float x = 0, float y = 0, float width = 0, float height = 0, float scale = 0, UI *ui = nullptr);
    void applyGravity();
    void tick();
    bool shouldRemove();
    void draw();
};