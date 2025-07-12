#pragma once
#include "gameObject.h"
#include "UI.h"

enum class BackGroundType
{
    Castle,
    SmallHill,
    BigHill,
    Cloud1,
    Cloud2,
    Cloud3,
    Plant1,
    Plant2,
    Plant3,
    FlagPole
};

class BackGround : public GameObject
{
private:
    // constant values
    BackGroundType type;

    // Background textures
    std::vector<sf::Texture> backgroundTextures;
    sf::Texture currentTexture;

public:
    BackGround() = default;
    BackGround(float x, float y, float width, float height, int scale, UI *ui, sf::RenderWindow &window,
               BackGroundType type);

    void render();
    void tick();

    BackGroundType getBackGroundID();

    // Check bounds
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();
};