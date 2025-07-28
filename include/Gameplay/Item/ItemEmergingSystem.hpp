#pragma once
#include <World.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <iostream>

class ItemEmergingSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *item: world.findAll<ItemEmerging, Transform>())
        {
            auto &emerging = item->getComponent<ItemEmerging>();
            auto &pos = item->getComponent<Transform>().position;
            auto &size = item->getComponent<Transform>().size;
            if (!emerging.finished)
            {
                pos.y -= emerging.speedY * dt;
                if (pos.y <= emerging.finalY)
                {
                    pos.y = emerging.finalY;
                    // std::cout << pos.y << std::endl;
                    emerging.finished = true;
                    item->removeComponent<ItemEmerging>();

                    // Set the size of the collision box for the player
                    item->addComponent<BoxCollider2D>(size);

                    // Patrol 
                    item->addComponent<PatrolComponent>();
                    item->getComponent<PatrolComponent>().moveSpeed = 200.0f;

                    // Apply gravity
                    item->addComponent<RigidBody>(sf::Vector2f(0, 0));

                    // Add collectable tag
                    item->addComponent<CollectableTag>();

                    // Add block collision detection
                    item->addComponent<CanHitBlockTag>();

                    // Apply direction to the mushroom
                    // std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};
                    // mushroom->addComponent<DamageOnContactComponent>(directions);
                }
            }
        }
    }
};