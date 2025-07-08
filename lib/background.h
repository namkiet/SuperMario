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

    UI *ui;

    std::vector<Texture2D> backgroundTextures;

    Texture2D currentTexture;

public:
    BackGround(float x = 0, float y = 0, float width = 0, float height = 0, int scale = 0, UI *ui = nullptr, BackGroundType type = BackGroundType::Castle);

    void render();
    void tick();

    BackGroundType getBackGroundID();

    // Check bounds
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();
};