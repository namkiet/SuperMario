#pragma once
#include <Framework/World.hpp>

#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Factories/EnemyFactory.hpp>

#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/Obstacles/Components.hpp>

#include <World.hpp>
class PodobooSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *podoboo : world.findAll<PodobooTag, Transform, Animation>())
        {
            // Change direction based on upright state
            auto &podobooTag = podoboo->getComponent<PodobooTag>();
            auto &transform = podoboo->getComponent<Transform>();
            auto &rigidBody = podoboo->getComponent<RigidBody>();

            if (podobooTag.upright && transform.position.y <= podobooTag.highestY)
            {
                // If upright and at the highest point, switch to falling
                podobooTag.upright = false;
                rigidBody.velocity.y = -rigidBody.velocity.y; // Falling speed
                podoboo->removeComponent<Animation>();
                podoboo->addComponent<Animation>(EnemyFactory::getEnemyTexture("podoboo_fall"));
            }
            else if (!podobooTag.upright && transform.position.y >= podobooTag.lowestY)
            {
                // If not upright and at the lowest point, switch to rising
                podobooTag.upright = true;
                rigidBody.velocity.y = -rigidBody.velocity.y; // Rising speed
                podoboo->removeComponent<Animation>();
                podoboo->addComponent<Animation>(EnemyFactory::getEnemyTexture("podoboo_rise"));
            }
        }
    }
};