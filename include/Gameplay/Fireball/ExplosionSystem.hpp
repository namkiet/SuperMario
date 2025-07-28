#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Fireball/Components.hpp>

namespace Fireball
{
    class ExplosionSystem : public System 
    {
    public:
        void update(World& world, float dt) override 
        {
            for (Entity* entity : world.findAll<FireballTag, ExplodedTag>())
            {
                entity->removeComponent<RigidBody>();
                entity->removeComponent<BoxCollider2D>();
                // entity->addComponent<Animation>();
                entity->addComponent<LifeSpan>(1.0f);

                entity->removeComponent<ExplodedTag>();
            }
        }
    };
}