#pragma once
#include <Entity/Character/Character.hpp>

class Mario : public Character
{
public:
    Mario(float x, float y, float width, float height, float scale)
        : Character(x, y, width, height, scale)
    {
        addComponent<Animation>(TextureManager::load("assets/Player/SmallPlayer/marioSmall_0.png"));
        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>(), std::make_shared<PlayerSmallState>(), std::make_shared<PlayerNormalState>(), true);
        getComponent<PlayerTag>().speed = 400.0f;
        getComponent<PlayerTag>().jumpForce = 1100.0f;
    }
};