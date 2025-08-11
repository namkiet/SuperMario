#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/Stomp/Components.hpp>

class StompSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        for (Entity* stomper : world.findAll<StomperTag, BoxCollider2D>())
        {
            for (auto& [stompable, direction, overlap] : stomper->getComponent<BoxCollider2D>().collisions)
            {
                if (!stompable->hasComponent<StompableTag>()) continue;
                
                if (direction == Direction::Top)
                {
                    stomper->getComponent<RigidBody>().velocity.y = -800.0f;
                    stomper->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));
                    // std::cout << "Stomp system: stomper. velocity = " 
                    //           << stomper->getComponent<RigidBody>().velocity.y << std::endl;
                    // stompable->addComponent<DespawnTag>();
                    // std::cout << "despawn at stomp system" << std::endl;
                    // // assert(false);
                }
            }
        }
    }
};
