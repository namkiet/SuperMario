#pragma once
#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y)
    {
        addComponent<Animation>(TextureManager::load("assets/mario_idling.png"));
        addComponent<BoxCollider2D>(SIZE::MARIO);
        // addComponent<Gravity>(Gravity(200.f));
        addComponent<Input>();
        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>());
        addComponent<RigidBody>(sf::Vector2f(0, 0));
        addComponent<Transform>(sf::Vector2f(x, y), SIZE::MARIO);
    }
};