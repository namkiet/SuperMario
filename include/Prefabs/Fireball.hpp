#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Fireball/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

namespace Prefab
{
    class Fireball : public Entity
    {
    public:
        Fireball(float x, float y)
        {
            addComponent<Animation>(TextureManager::load("assets/Mario/mario_idling_small.png"));

            addComponent<BoxCollider2D>(0.25f * SIZE::GRID, sf::Vector2f(0, 0), true);
            addComponent<RigidBody>(sf::Vector2f(400, 0));
            addComponent<Transform>(sf::Vector2f(x, y), 0.25f * SIZE::GRID);

            addComponent<FireballTag>();
        }
    };
}