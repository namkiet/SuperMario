#pragma once
#include <Entity/Character/Character.hpp>

class Luigi : public Character
{
public:
    Luigi(float x, float y, float width, float height, float scale)
        : Character(x, y, width, height, scale)
    {
        addComponent<Animation>(TextureManager::load("assets/Player/SmallPlayer/luigiSmall_0.png"));
        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>(), std::make_shared<PlayerSmallState>(), std::make_shared<PlayerNormalState>());
        getComponent<PlayerTag>().speed = 300.0f;
        getComponent<PlayerTag>().jumpForce = 1400.0f;
    }
};