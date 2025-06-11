#pragma once
#include <World.hpp>
#include <Components/RigidBody.hpp>
#include <Components/Sprite2D.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>

class StateSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity: world.findAll<RigidBody, Sprite2D>())
        {
            auto& rb = entity->getComponent<RigidBody>();
            auto& sp = entity->getComponent<Sprite2D>();

            if (rb.getVelocity().x != 0)
            {
                sp.setSprite("Running");
            }
            else
            {
                sp.setSprite("Idling");
            }
        }
    }
};