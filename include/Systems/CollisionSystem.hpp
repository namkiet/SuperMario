#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>

class CollisionSystem : public System
{   
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity1 : world.findAll<BoxCollider2D, Transform, RigidBody>())
        {
            if (!entity1->getComponent<BoxCollider2D>().isSolid) continue;
            auto& tf1 = entity1->getComponent<Transform>();
            auto& rb1 = entity1->getComponent<RigidBody>();
            rb1.onGround = false;

            for (Entity* entity2 : world.findAll<BoxCollider2D, Transform>())
            {
                if (!entity2->getComponent<BoxCollider2D>().isSolid || entity1 == entity2) continue;

                auto info = Physics::AABBOverlap2(entity1, entity2);
                switch (info.direction)
                {
                    case Physics::CollisionDirection::Top:
                        tf1.position.y -= info.overlap.y;
                        rb1.velocity.y = 0.0f;
                        rb1.onGround = true;
                        
                        break;
                    
                    case Physics::CollisionDirection::Bottom:
                        tf1.position.y += info.overlap.y;
                        rb1.velocity.y = 0.0f;
                        break;
                    
                    case Physics::CollisionDirection::Left:
                        tf1.position.x -= info.overlap.x;
                        break;
                    
                    case Physics::CollisionDirection::Right:
                        tf1.position.x += info.overlap.x;
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }

    // void update(World& world, float dt) override
    // {
    //     for (Entity* entity1 : world.findAll<BoxCollider2D, Transform, RigidBody>())
    //     {
    //         auto& tf1 = entity1->getComponent<Transform>();
    //         auto& box1 = entity1->getComponent<BoxCollider2D>();
    //         auto& rb1 = entity1->getComponent<RigidBody>();
    //         rb1.onGround = false;

    //         for (Entity* entity2 : world.findAll<BoxCollider2D, Transform>())
    //         {
    //             if (entity1 == entity2) continue;

    //             auto& tf2 = entity2->getComponent<Transform>();
    //             auto& box2 = entity2->getComponent<BoxCollider2D>();

    //             sf::Vector2f overlap = Physics::AABBOverlap(box1.size, tf1.position + box1.offset, box2.size, tf2.position + box2.offset);
                
    //             if (overlap.x > 0.f && overlap.y > 0.f) 
    //             { 
    //                 sf::Vector2f prevOverlap = Physics::AABBOverlap(box1.size, tf1.prevPos + box1.offset, box2.size, tf2.prevPos + box2.offset);

    //                 if (prevOverlap.y > 0.f) 
    //                 {
    //                     if (tf1.prevPos.x < tf2.position.x) 
    //                     {
    //                         // Comming from the left
    //                         tf1.position.x -= overlap.x;
    //                     } 
    //                     else 
    //                     {
    //                         // Comming from the right
    //                         tf1.position.x += overlap.x;
    //                     }
    //                 } 
    //                 else if (prevOverlap.x > 0.f) 
    //                 {
    //                     rb1.velocity.y = 0.0f;
                        
    //                     if (tf1.prevPos.y < tf2.position.y) 
    //                     {
    //                         // Comming from the top
    //                         tf1.position.y -= overlap.y;
    //                         rb1.onGround = true;
    //                     } 
    //                     else 
    //                     {
    //                         // Comming from bellow
    //                         tf1.position.y += overlap.y;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    
};