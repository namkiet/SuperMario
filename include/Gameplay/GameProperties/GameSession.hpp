#pragma once
#include <ECS/Entity.hpp>
#include <Gameplay/GameProperties/Components.hpp>

class GameSession : public Entity
{
private:
public:
    GameSession(int level, int theme)
    {
        // Add time component
        addComponent<TimeComponent>(400); // Initialize with 400 seconds

        // Add level component
        addComponent<LevelComponent>(level);

        // Add coin component
        addComponent<CoinComponent>();

        // Add theme component
        addComponent<ThemeComponent>(theme);
    }
};