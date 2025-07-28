#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <iostream>

class CollisionDetectionSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity* entity1 : world.findAll<BoxCollider2D, Transform, RigidBody>())
        {
            if (entity1->getComponent<BoxCollider2D>().isDisabled)
                continue;
            auto &coll = entity1->getComponent<BoxCollider2D>().collisions;
            coll.clear();

            for (Entity *entity2 : world.findAll<BoxCollider2D, Transform>())
            {
                if (entity1 == entity2)
                    continue;

                auto dir = Physics::GetCollisionDirection(entity1, entity2);
                if (dir != Direction::None)
                {
                    coll.push_back(CollisionInfo(entity2, dir));
                }
            }
        }
    }
};