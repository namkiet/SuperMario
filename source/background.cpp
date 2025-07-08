#include <iostream>
#include "background.h"
using namespace std;

BackGround::BackGround(float x, float y, float width, float height, int scale, UI *ui, BackGroundType type)
    : GameObject(x, y, ObjectID::Background, width, height, scale), type(type), ui(ui)
{
    if (ui == nullptr)
    {
        std::cerr << "UI pointer is null in BackGround constructor!" << std::endl;
        return;
    }

    backgroundTextures = ui->getBackground();

    // cout << castleTextures.size() << " castle textures loaded." << endl;
}

void BackGround::render()
{
    switch (type)
    {
    case BackGroundType::Castle:
        currentTexture = backgroundTextures[0];
        break;
    case BackGroundType::SmallHill:
        currentTexture = backgroundTextures[1];
        break;
    case BackGroundType::BigHill:
        currentTexture = backgroundTextures[2];
        break;
    case BackGroundType::Cloud1:
        currentTexture = backgroundTextures[5];
        break;
    case BackGroundType::Cloud2:
        currentTexture = backgroundTextures[3];
        break;
    case BackGroundType::Cloud3:
        currentTexture = backgroundTextures[4];
        break;
    case BackGroundType::Plant1:
        currentTexture = backgroundTextures[6];
        break;
    case BackGroundType::Plant2:
        currentTexture = backgroundTextures[8];
        break;
    case BackGroundType::Plant3:
        currentTexture = backgroundTextures[7];
        break;
    case BackGroundType::FlagPole:
        currentTexture = backgroundTextures[9];
        break;
    default:
        std::cerr << "Unknown background type!" << std::endl;
        return;
    }
    DrawTexturePro(currentTexture,
                   {0, 0, (float)currentTexture.width, (float)currentTexture.height},
                   {getX(), getY(), getWidth(), getHeight()},
                   {0, 0}, 0.0f, WHITE);
}

void BackGround::tick()
{
    // Backgrounds don't tick, so this is empty
}

BackGroundType BackGround::getBackGroundID()
{
    return type;
}

Rectangle BackGround::getBounds()
{
    return {getX(),
            getY() + getHeight() / 2,
            getWidth(),
            getHeight() / 2};
}

Rectangle BackGround::getBoundsTop()
{
    return {getX(),
            getY(),
            getWidth(),
            getHeight() / 2};
}

Rectangle BackGround::getBoundsRight()
{
    return {getX() + getWidth() / 2,
            getY(),
            getWidth() / 4,
            getHeight()};
}

Rectangle BackGround::getBoundsLeft()
{
    return {getX() + getWidth() / 4,
            getY(),
            getWidth() / 4,
            getHeight()};
}