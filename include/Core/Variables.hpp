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
    inline bool IS_SELECTING_MARIO = true;
}

namespace SOUND
{
    inline bool shouldPlaySound = true;
    inline bool shouldPlayMusic = true;
    // inline bool SoundBlockMusic = false;
}