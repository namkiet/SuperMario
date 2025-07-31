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

// class TeleSystem: public System
// {
//     static bool totallyCollide(Entity* a, Entity* b, Direction dir)
//     {
//         if (dir == Direction::Top || dir == Direction::Bottom)
//         {
//             float leftA = a->getComponent<Transform>().position.x + a->getComponent<BoxCollider2D>().offset.x;
//             float rightA = leftA + a->getComponent<BoxCollider2D>().size.x;
//             float leftB = b->getComponent<Transform>().position.x + b->getComponent<BoxCollider2D>().offset.x;
//             float rightB = leftB + b->getComponent<BoxCollider2D>().size.x;
//             // std::cout << "leftB " << leftB << std::endl;
//             // std::cout << "leftA " << leftA << std::endl;
//             // std::cout << "rightA " << rightA << std::endl;
//             // std::cout << "rightB " << rightB << std::endl;

//             return (leftB <= leftA && rightA <= rightB);
//         }
//         else if (dir == Direction::Left || dir == Direction::Right)
//         {
//             float topA = a->getComponent<Transform>().position.y + a->getComponent<BoxCollider2D>().offset.y;
//             float bottomA = topA + a->getComponent<BoxCollider2D>().size.y;
//             float topB = b->getComponent<Transform>().position.y + b->getComponent<BoxCollider2D>().offset.y;
//             float bottomB = topB + b->getComponent<BoxCollider2D>().size.y;

//             // std::cout << "left, right totally collide" << std::endl;
//             return (topB <= topA && bottomA <= bottomB);
//         }
//         assert(false);
//         return false;
//     }

//     void update(World& world, float dt) override
//     {
//         auto player = world.findFirst<PlayerTag>();
//         if (!player) return;

//         // if it has teleTag
//         if (player->hasComponent<TeleChanneling>())
//         {
//             auto& tele = player->getComponent<TeleChanneling>();
//             bool prevTeleState = tele.DuringInTime;

//             tele.TeleTime -= dt;
//             auto teleInfo = tele.teleEntity->getComponent<TelePort>();
//             if (tele.TeleTime <= 0.f) // tele complete
//             {
//                 player->removeComponent<TeleChanneling>();

//                 // allow collider detection
//                 auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
//                 isDisabled = false;
//                 // allow input
//                 player->addComponent<InputTag>();
//                 player->addComponent<RigidBody>();

//             }
//             else  // has not completed
//             {
//                 auto& pos = player->getComponent<Transform>().position;
//                 tele.DuringInTime = (tele.TeleTime >= teleInfo.outtime);
//                 if (prevTeleState != tele.DuringInTime) // change state of tele
//                 {
//                     pos = teleInfo.destination;
//                 }
//                 // not truly inTime + outTime in total, a bit error of timeCount at change state
//                 if (tele.DuringInTime)
//                 {
//                     pos += teleInfo.inVel * dt;
//                 }
//                 else
//                 {
//                     pos += teleInfo.outVel * dt;
//                 }
//             }
//         }
//         // player not in tele Channeling
//         else
//         {
//             if (!player->hasComponent<BoxCollider2D>()) return;
//             auto& box = player->getComponent<BoxCollider2D>();

//             for (auto &[block, direction] : box.collisions)
//             {
//                 if (!block->hasComponent<TelePort>()) continue;
//                 if (direction != block->getComponent<TelePort>().requireCollisionDirection
//                     || !totallyCollide(player, block, direction)) {
//                         // std::cout << "not allow to continue" << std::endl;
//                         continue;
//                     }

//                 // std::cout << "LETS GOOOOOOO" <<std::endl;

//                 auto teleInfo = block->getComponent<TelePort>();

//                 player->addComponent<TeleChanneling>(block);
//                 // remove input tag
//                 player->removeComponent<InputTag>();
//                 // disable collider detect
//                 auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
//                 isDisabled = true;
//                 // remove vel
//                 player->removeComponent<RigidBody>();
//                 break;
//             }
//         }
//     }
// };

class TeleSystem : public System
{
    static bool totallyCollide(Entity *a, Entity *b, Direction dir)
    {
        // std::cout << "Check heree" << std::endl;
        if (dir == Direction::Top || dir == Direction::Bottom)
        {
            float leftA = a->getComponent<Transform>().position.x + a->getComponent<BoxCollider2D>().offset.x;
            float rightA = leftA + a->getComponent<BoxCollider2D>().size.x;
            float leftB = b->getComponent<Transform>().position.x + b->getComponent<BoxCollider2D>().offset.x;
            float rightB = leftB + b->getComponent<BoxCollider2D>().size.x;

            return (leftB <= leftA && rightA <= rightB);
        }
        else if (dir == Direction::Left || dir == Direction::Right)
        {
            float topA = a->getComponent<Transform>().position.y + a->getComponent<BoxCollider2D>().offset.y;
            float bottomA = topA + a->getComponent<BoxCollider2D>().size.y;
            float topB = b->getComponent<Transform>().position.y + b->getComponent<BoxCollider2D>().offset.y;
            float bottomB = topB + b->getComponent<BoxCollider2D>().size.y;
            return (topB - 10.f <= topA && bottomA <= bottomB + 10.f);
        }
        assert(false);
        return false;
    }
    static sf::Vector2f calVel(Direction dir, float speed = 200.f)
    {
        if (dir == Direction::Top)
            return sf::Vector2f(0.f, -speed);
        if (dir == Direction::Bottom)
            return sf::Vector2f(0.f, speed);
        if (dir == Direction::Right)
            return sf::Vector2f(speed, 0.f);
        if (dir == Direction::Left)
            return sf::Vector2f(-speed, 0.f);
    }
    Entity *findPipeDestination(World &world, Entity *player)
    {
        auto entities = world.findAll<PipeTag>();
        for (auto &e : entities)
        {
            if (Physics::GetCollisionDirection(player, e) != Direction::None)
                return e;
        }
        return nullptr;
    }

    void update(World &world, float dt) override
    {
        auto player = world.findFirst<PlayerTag>();
        if (!player)
            return;

        // if it has teleTag
        if (player->hasComponent<TeleChanneling>()) // being tele
        {
            auto &tele = player->getComponent<TeleChanneling>();
            if (tele.teleInTime < 0.f)
            {
                if (tele.teleEntity->hasComponent<hasPipeDestination>())
                {

                    auto &PipeDestination = tele.teleEntity->getComponent<hasPipeDestination>();
                    // PipeDestination.pipe = findPipeDestination(world, player);
                    if (Physics::GetCollisionDirection(player, PipeDestination.pipe) == Direction::None)
                    {
                        player->removeComponent<TeleChanneling>();
                        // allow collider detection
                        auto &isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
                        isDisabled = false;
                        // allow input
                        player->addComponent<InputTag>();
                        player->addComponent<RigidBody>();

                        return;
                    }
                    sf::Vector2f vel = calVel(PipeDestination.OutDirection);
                    auto &pos = player->getComponent<Transform>().position;
                    pos += vel * dt;
                }
                else
                {
                    player->removeComponent<TeleChanneling>();
                    // allow collider detection
                    auto &isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
                    isDisabled = false;
                    // allow input
                    player->addComponent<InputTag>();
                    player->addComponent<RigidBody>();

                    return;
                }
            }

            else // tele.teleInTime >= 0.f
            {
                tele.teleInTime -= dt; // update counting if it stills in in-time
                auto teleInfo = tele.teleEntity->getComponent<TelePort>();
                auto &pos = player->getComponent<Transform>().position;
                pos += teleInfo.inVel * dt;
                // std::cout << "update pos ok here" << std::endl;
                if (tele.teleInTime < 0.f) // doing tele
                {

                    auto &pos = player->getComponent<Transform>().position;
                    pos = tele.teleEntity->getComponent<TelePort>().destination;
                    if (tele.teleEntity->hasComponent<hasPipeDestination>())
                    {
                        auto &PipeDestination = tele.teleEntity->getComponent<hasPipeDestination>();
                        PipeDestination.pipe = findPipeDestination(world, player);
                        // std::cout << "sth" << std::endl;
                        assert(PipeDestination.pipe != nullptr);
                    }
                }
            }
        }

        //     if (tele.teleInTime <= 0.f) // tele go-in complete
        //     {
        //         pos = teleInfo.destination;
        //         if (tele.teleEntity->hasComponent<hasPipeDestination>()) // if it connect to another pipe
        //         {
        //             auto PipeDestination = tele.teleEntity->getComponent<hasPipeDestination>();
        //             sf::Vector2f vel = calVel(PipeDestination.OutDirection);
        //             pos += vel * dt;
        //             if (Physics::GetCollisionDirection(player, PipeDestination.pipe) == Direction::None)
        //             {
        //                 player->removeComponent<TeleChanneling>();
        //             // allow collider detection
        //                 auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
        //                 isDisabled = false;
        //                 // allow input
        //                 player->addComponent<InputTag>();
        //                 player->addComponent<RigidBody>();
        //             }
        //         }
        //         else // if no pipe is connected to it
        //         {
        //             player->removeComponent<TeleChanneling>();

        //             // allow collider detection
        //             auto& isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
        //             isDisabled = false;
        //             // allow input
        //             player->addComponent<InputTag>();
        //             player->addComponent<RigidBody>();
        //         }

        //     }
        //     else  // has not completed
        //     {
        //         auto& pos = player->getComponent<Transform>().position;
        //         pos += teleInfo.inVel * dt;
        //     }
        // }

        // player not in tele Channeling
        else
        {
            if (!player->hasComponent<BoxCollider2D>())
                return;
            auto &box = player->getComponent<BoxCollider2D>();

            for (auto &[block, direction, overlap] : box.collisions)
            {
                if (!block->hasComponent<TelePort>())
                    continue;
                if (direction != block->getComponent<TelePort>().requireCollisionDirection || !totallyCollide(player, block, direction))
                {
                    // std::cout << "not allow to continue" << std::endl;
                    continue;
                }

                // std::cout << "LETS GOOOOOOO" <<std::endl;

                auto teleInfo = block->getComponent<TelePort>();

                player->addComponent<TeleChanneling>(block);
                // remove input tag
                player->removeComponent<InputTag>();
                // disable collider detect
                auto &isDisabled = player->getComponent<BoxCollider2D>().isDisabled;
                isDisabled = true;
                // remove vel
                player->removeComponent<RigidBody>();
                break;
            }
        }
    }
};
