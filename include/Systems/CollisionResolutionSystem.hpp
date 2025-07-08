#pragma once
#include <ECS/System.hpp>
#include <Components/BoxCollider2D.hpp>
#include <Components/Transform.hpp>
#include <Components/RigidBody.hpp>
#include <Core/Physics.hpp>

class CollisionResolutionSystem : public System
{   
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<BoxCollider2D, Transform, RigidBody>())
        {
            auto& tf = entity->getComponent<Transform>();
            auto& rb = entity->getComponent<RigidBody>();
            auto& box = entity->getComponent<BoxCollider2D>();

            rb.onGround = false;
            
            // Check if the current entity is solid
            if (!box.isSolid) continue;

            // Check if it collided with any entity
            if (!box.colInfo.collider) continue;

            // Check if the entity it collided is solid
            if (!box.colInfo.collider->getComponent<BoxCollider2D>().isSolid) continue;

            switch (box.colInfo.direction)
            {
                case CollisionDirection::Top:
                    tf.position.y -= box.colInfo.overlap.y;
                    rb.velocity.y = 0.0f;
                    rb.onGround = true;
                    break;
                
                case CollisionDirection::Bottom:
                    tf.position.y += box.colInfo.overlap.y;
                    rb.velocity.y = 0.0f;
                    break;
                
                case CollisionDirection::Left:
                    tf.position.x -= box.colInfo.overlap.x;
                    break;
                
                case CollisionDirection::Right:
                    tf.position.x += box.colInfo.overlap.x;
                    break;
                
                default:
                    break;
            }
        }
    }
};