#include <iostream>
#include "debris.h"
using namespace std;

Debris::Debris(float x, float y, float width, float height, float scale, UI *ui)
    : ui(ui), scale(scale), width(width / 2), height(height / 2), velX(2.0f), velY(-7.0f)
{
    this->x.push_back(x - this->width); // Left down debris
    this->x.push_back(x - this->width); // Top left debris
    this->x.push_back(x + this->width); // Right down debris
    this->x.push_back(x + this->width); // Top right debris

    this->y.push_back(y + this->height);
    this->y.push_back(y - this->height);
    this->y.push_back(y + this->height);
    this->y.push_back(y - this->height);

    // for (int i = 0; i < 4; ++i)
    // {
    //     cout << "Debris position " << i << ": (" << this->x[i] << ", " << this->y[i] << ")" << endl;
    // }
    debris = ui->getDebris1();
}

void Debris::applyGravity()
{
    velY += 0.5f;
    // cout << "applyGravity called. velY = " << velY << endl;
}

void Debris::tick()
{
    // cout << "Vel Y = " << velY << endl;
    x[0] = -velX + x[0];
    x[1] = -velX + x[1];
    x[2] = velX + x[2];
    x[3] = velX + x[3];

    y[0] = velY + y[0];
    y[1] = velY + y[1] - 2;
    y[2] = velY + y[2];
    y[3] = velY + y[3] - 2;

    applyGravity();
    // cout << "Debris::tick() called. VelY: " << velY << endl;
    // cout << "----------------------------------------------------------" << endl;
    
}

bool Debris::shouldRemove()
{
    // cout << "Debris y[1]: " << y[1] << ", y[3]: " << y[3] << ", ScreenHeight: " << GetScreenHeight() << endl;
    if (y[1] > GetScreenHeight() || y[3] > GetScreenHeight())
    {
        // cout << "Debris is below the screen. Removing debris." << endl;
        return true; // Remove if the debris falls below the screen
    }
    else
    {
        return false; // Keep the debris if it is still visible
    }
}

void Debris::draw()
{
    for (int i = 0; i < 4; ++i)
    {
        if (debris[i].id == 0) // Check if the texture is valid
        {
            cerr << "Error: Debris texture " << i << " is invalid!" << endl;
            continue;
        }
        DrawTexturePro(
            debris[i],
            Rectangle{0, 0, (float)debris[i].width, (float)debris[i].height},
            Rectangle{x[i], y[i], (float)width, (float)height},
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE);
    }
}