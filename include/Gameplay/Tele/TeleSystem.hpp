// for another file
#include <ECS/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <Gameplay/Tele/Components.hpp>
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Prefabs/Mario.hpp>
#include <unordered_map>
#include <cassert>
#include <iostream>



class TeleSystem: public System
{
    static bool totallyCollide(Entity* a, Entity* b, Direction dir)
    {
        if (dir == Direction::Top || dir == Direction::Bottom)
        {
            float leftA = a->getComponent<Transform>().position.x + a->getComponent<BoxCollider2D>().offset.x;
            float rightA = leftA + a->getComponent<BoxCollider2D>().size.x;
            float leftB = b->getComponent<Transform>().position.x + b->getComponent<BoxCollider2D>().offset.x;
            float rightB = leftB + b->getComponent<BoxCollider2D>().size.x;
            // std::cout << "leftB " << leftB << std::endl;
            // std::cout << "leftA " << leftA << std::endl;
            // std::cout << "rightA " << rightA << std::endl;
            // std::cout << "rightB " << rightB << std::endl;
                        
            return (leftB <= leftA && rightA <= rightB);
        }
        else if (dir == Direction::Left || dir == Direction::Right)
        {
            float topA = a->getComponent<Transform>().position.y + a->getComponent<BoxCollider2D>().offset.y;
            float bottomA = topA + a->getComponent<BoxCollider2D>().size.y;
            float topB = b->getComponent<Transform>().position.y + b->getComponent<BoxCollider2D>().offset.y;
            float bottomB = topB + b->getComponent<BoxCollider2D>().size.y;
            
            // std::cout << "left, right totally collide" << std::endl;
            return (topB <= topA && bottomA <= bottomB);
        }
        assert(false);
        return false;
    }

    // static std::unordered_map<Entity*, BoxCollider2D> getColliders;
    // BoxCollider2D& recoverInfo(Entity* entity)
    // {
    //     assert(getColliders.find(entity) != getColliders.end() && "Entity does not have saved collider info");
    //     auto& box = getColliders[entity];
    //     getColliders.erase(entity);
    //     return box;
    // }
    // void saveCollider(Entity* entity)
    // {
    //     if (getColliders.find(entity) != getColliders.end())
    //     {
    //         getColliders.erase(entity);
    //     }
    //     getColliders[entity] = entity->getComponent<BoxCollider2D>();
    // }

    void update(World& world, float dt) override
    {
        auto player = world.findFirst<PlayerTag>();
        if (!player) return;
        
        // if it has teleTag
        if (player->hasComponent<TeleChanneling>())
        {
            auto& tele = player->getComponent<TeleChanneling>();
            bool prevTeleState = tele.DuringInTime;

            tele.TeleTime -= dt;
            auto teleInfo = tele.teleEntity->getComponent<TelePort>();
            if (tele.TeleTime <= 0.f) // tele complete
            {
                player->removeComponent<TeleChanneling>();
                
                // allow collider detection
                auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
                isDisabled = false;
                // allow input
                player->addComponent<InputTag>();
                player->addComponent<RigidBody>();

            }
            else  // has not completed
            {
                auto& pos = player->getComponent<Transform>().position;
                tele.DuringInTime = (tele.TeleTime >= teleInfo.outtime);
                if (prevTeleState != tele.DuringInTime) // change state of tele
                {
                    pos = teleInfo.destination;
                }
                // not truly inTime + outTime in total, a bit error of timeCount at change state
                if (tele.DuringInTime)
                {
                    pos += teleInfo.inVel * dt;
                }
                else
                {
                    pos += teleInfo.outVel * dt;
                }
            }
        }
        // player not in tele Channeling
        else
        {
            auto& box = player->getComponent<BoxCollider2D>();

            for (auto &[block, direction] : box.collisions)
            {
                if (!block->hasComponent<TelePort>()) continue;
                if (direction != block->getComponent<TelePort>().requireCollisionDirection
                    || !totallyCollide(player, block, direction)) {
                        // std::cout << "not allow to continue" << std::endl;
                        continue;
                    }

                // std::cout << "LETS GOOOOOOO" <<std::endl;

                auto teleInfo = block->getComponent<TelePort>();
                
                player->addComponent<TeleChanneling>(block);
                // remove input tag
                player->removeComponent<InputTag>();
                // disable collider detect
                auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
                isDisabled = true;
                // remove vel
                player->removeComponent<RigidBody>();
                break;
            }
        }
    }
};
