#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <iostream>

class CollisionDetectionSystem : public System
{   
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity1 : world.findAll<BoxCollider2D, Transform>())
        {
            auto& coll = entity1->getComponent<BoxCollider2D>().collisions;
            coll.clear();

            for (Entity* entity2 : world.findAll<BoxCollider2D, Transform>())
            {
                if (entity1 == entity2) continue;

                auto overlap = Physics::GetCollisionOverlap(entity1, entity2);
                if (overlap.x > 0.0f && overlap.y > 0.0f)
                {
                    auto& pos1 = entity1->getComponent<Transform>().position;
                    auto& pos2 = entity2->getComponent<Transform>().position;
                    
                    Direction dir;
                    if (overlap.x > overlap.y)
                    {
                        dir = pos1.y < pos2.y ? Direction::Top : Direction::Bottom;
                    }
                    else
                    {
                        dir = pos1.x < pos2.x ? Direction::Left : Direction::Right;
                    }

                    coll.push_back(CollisionInfo(entity2, dir));
                }
            }
        }
    }
};