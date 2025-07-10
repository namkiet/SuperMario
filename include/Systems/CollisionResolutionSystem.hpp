#pragma once
#include <ECS/System.hpp>
#include <Components/BoxCollider2D.hpp>
#include <Components/Transform.hpp>
#include <Components/RigidBody.hpp>
#include <Components/BlockTag.hpp>
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
            for (auto& [collider, direction] : box.collisions)
            {
                // Check if the entity it collides with is solid
                if (!collider->hasComponent<BlockTag>()) continue;

                sf::Vector2f overlap = Physics::GetCollisionOverlap(entity, collider);

                // Check if they are still colliding
                if (overlap.x <= 0.0f || overlap.y <= 0.0f) continue;

                switch (direction)
                {
                    case Direction::Top:
                        tf.position.y -= overlap.y;
                        rb.velocity.y = 0.0f;
                        rb.onGround = true;
                        break;
                    
                    case Direction::Bottom:
                        tf.position.y += overlap.y;
                        rb.velocity.y = 0.0f;
                        break;
                    
                    case Direction::Left:
                        tf.position.x -= overlap.x;
                        rb.velocity.x = 0.0f;
                        break;
                    
                    case Direction::Right:
                        tf.position.x += overlap.x;
                        rb.velocity.x = 0.0f;
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
};