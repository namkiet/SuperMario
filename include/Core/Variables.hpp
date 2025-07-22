#pragma once

namespace SIZE
{
    inline sf::Vector2f GRID        = sf::Vector2f(64, 64);
    inline sf::Vector2f MARIO       = GRID;
    // inline sf::Vector2f MARIO       = GRID;
    inline sf::Vector2f SCREEN      = sf::Vector2f(1200, 800); 
};

namespace PHYSICS
{
    inline float GRAVITY            = 2560.0f;
    inline float JUMP_FORCE         = 1280.0f;
}