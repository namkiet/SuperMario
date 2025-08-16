#pragma once
#include <Framework/World.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <SFML/Graphics.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <iostream>

class AnimationSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<Animation>())
        {
            auto &anim = entity->getComponent<Animation>();

            if (entity->hasComponent<TowardPlayer>())
            {
                auto &direction = entity->getComponent<TowardPlayer>().direction;
                if (direction == Direction::Left)
                {
                    entity->addComponent<FlipXTag>();
                }
                else 
                {
                    entity->removeComponent<FlipXTag>();
                }
            }
            else if (entity->hasComponent<RigidBody>())
            {
                auto &rb = entity->getComponent<RigidBody>();
                if (rb.velocity.x > 0.0f)
                {
                    entity->removeComponent<FlipXTag>();
                }
                else if (rb.velocity.x < 0.0f)
                {
                    entity->addComponent<FlipXTag>();
                }
            }

            updateAnimation(entity->getComponent<Animation>(), dt);
        }
    }
};