#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/Fireball/Components.hpp>

namespace Fireball
{
    class BlockCollisionSystem : public System
    {   
    public:
        void update(World& world, float dt) override
        {
            for (Entity* entity : world.findAll<FireballTag, BoxCollider2D, RigidBody>())
            {
                auto& rb = entity->getComponent<RigidBody>();
                for (auto& [block, direction] : entity->getComponent<BoxCollider2D>().collisions)
                {
                    // Check if the entity it collides with is solid
                    if (!block->hasComponent<BlockTag>()) continue;
                    
                    // If collide from top, then bounce, else disappear
                    if (direction == Direction::Top)
                    {
                        rb.velocity.y = -400.0f;
                    }
                    else if (direction == Direction::Left || direction == Direction::Right)
                    {
                        entity->addComponent<ExplodedTag>();
;                   }
                }
            }
        }
    };
}