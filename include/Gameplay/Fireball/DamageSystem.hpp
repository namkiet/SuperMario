#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Fireball/Components.hpp>

namespace Fireball
{
    class DamageSystem : public System 
    {
    public:
        void update(World& world, float dt) override 
        {
            for (Entity* fireball : world.findAll<FireballTag, BoxCollider2D>())
            {
                for (auto& [collider, direction] : fireball->getComponent<BoxCollider2D>().collisions)
                {
                    if (!collider->hasComponent<FlammableTag>()) continue;

                    collider->addComponent<DespawnTag>();
                    fireball->addComponent<ExplodedTag>();
                }
            }
        }
    };
}