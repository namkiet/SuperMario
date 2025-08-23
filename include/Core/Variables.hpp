#pragma once

namespace SIZE
{
    inline sf::Vector2f GRID = sf::Vector2f(64, 64);
    inline sf::Vector2f MARIO = GRID;
    // inline sf::Vector2f MARIO       = GRID;
    inline sf::Vector2f SCREEN = sf::Vector2f(960, 720);
};

namespace PHYSICS
{
    inline float GRAVITY = 2560.0f;
    inline float JUMP_FORCE = 1100.0f;
}

namespace PLAYER
{
    // inline float HORIZONTAL_SPEED = 400.0f;
    
    inline float HORIZONTAL_SPEED = 800.0f;

}
namespace SOUND
{
    inline bool shouldPlaySound = true;
    inline bool shouldPlayMusic = true;
    // inline bool SoundBlockMusic = false;
}