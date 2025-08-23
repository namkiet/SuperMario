// for another file
#include <ECS/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <Gameplay/Tele/Components.hpp>
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Entity/Player/Mario.hpp>
#include <unordered_map>
#include <cassert>
#include <iostream>



class TeleSystem : public System
{
    int TeleFade = -1;
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
    static bool totallyBypass(Entity* a, Entity* b, Direction dir)
{
    const auto& ta = a->getComponent<Transform>();
    const auto& ca = a->getComponent<BoxCollider2D>();
    const auto& tb = b->getComponent<Transform>();
    const auto& cb = b->getComponent<BoxCollider2D>();

    const float leftA   = ta.position.x + ca.offset.x;
    const float rightA  = leftA + ca.size.x;
    const float topA    = ta.position.y + ca.offset.y;
    const float bottomA = topA + ca.size.y;

    const float leftB   = tb.position.x + cb.offset.x;
    const float rightB  = leftB + cb.size.x;
    const float topB    = tb.position.y + cb.offset.y;
    const float bottomB = topB + cb.size.y;

    constexpr float eps = 0.5f; // nới nhẹ cho sai số float

    switch (dir)
    {
        case Direction::Top:
            return topA >= (topB - eps);

        case Direction::Bottom:
            return bottomA >= (bottomB - eps);

        case Direction::Left:
            return leftA >= (leftB - eps);

        case Direction::Right:
            return rightA <= (rightB + eps);

        default:
            return false;
    }
}

    static sf::Vector2f calVel(Direction dir, float speed = 70.f)
    {
        if (dir == Direction::Top)
            return sf::Vector2f(0.f, -speed);
        if (dir == Direction::Bottom)
            return sf::Vector2f(0.f, speed);
        if (dir == Direction::Right)
            return sf::Vector2f(speed, 0.f);
        if (dir == Direction::Left)
            return sf::Vector2f(-speed, 0.f);

        return sf::Vector2f(0, 0);
    }
    static void getSpawnPosAtPipeExit(Entity* pipe, Entity* player, Direction outDir)
    {
        auto& pos = player->getComponent<Transform>().position;
        const auto pipeBox   = Physics::GetCollisionBounds(pipe);
        const auto playerBox = Physics::GetCollisionBounds(player);

        switch (outDir)
        {
            case Direction::Top:
            case Direction::Bottom:
            {
                float centerX = pipeBox.left + pipeBox.width * 0.5f - playerBox.width * 0.5f;
                pos.x = centerX - player->getComponent<BoxCollider2D>().offset.x;
                break;
            }
            case Direction::Left:
            case Direction::Right:
            {
                float centerY = pipeBox.top + pipeBox.height * 0.5f - playerBox.height * 0.5f;
                pos.y = centerY - player->getComponent<BoxCollider2D>().offset.y;
                break;
            }
            default:
                break;
        }
    }
    Entity *findPipeDestination(World &world, Entity *player)
    {
        auto entities = world.findAll<PipeTag>();
        for (auto &e : entities)
        {
            if (!e) continue;
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
            if (!tele.beforeActualTele)
            {
                if (tele.teleEntity->hasComponent<hasPipeDestination>())
                {

                    auto &PipeDestination = tele.teleEntity->getComponent<hasPipeDestination>();
                    // PipeDestination.pipe = findPipeDestination(world, player);
                    if (!findPipeDestination(world, player))
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
                if (totallyBypass(player, tele.teleEntity, tele.teleEntity->getComponent<TelePort>().requireCollisionDirection) && TeleFade == -1)
                {
                    auto& anim = player->getComponent<Animation>();
                    sf::Color temp = anim.sprite.getColor();
                    TeleFade = temp.a;
                    temp.a = 0;
                    anim.sprite.setColor(temp);

                }
                if (tele.teleInTime < 0) // doing tele
                {
                    auto& anim = player->getComponent<Animation>();
                    sf::Color temp = anim.sprite.getColor();
                    temp.a = TeleFade; TeleFade = -1;
                    anim.sprite.setColor(temp);

                    tele.beforeActualTele = false;
                    auto &pos = player->getComponent<Transform>().position;
                    pos = tele.teleEntity->getComponent<TelePort>().destination;
                    if (tele.teleEntity->hasComponent<hasPipeDestination>())
                    {
                        auto &PipeDestination = tele.teleEntity->getComponent<hasPipeDestination>();
                        PipeDestination.pipe = findPipeDestination(world, player);
                        assert(PipeDestination.pipe != nullptr);
                        // set pos of player middle of pipe
                        getSpawnPosAtPipeExit(PipeDestination.pipe, player, PipeDestination.OutDirection);
                    }
                    
                    // anim.sprite.setColor(sf::Color(255,255,255,255)); // default;
                }
            }
        }

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
                auto& keybinding = KeyBinding::Instance();

                if (direction != block->getComponent<TelePort>().requireCollisionDirection || !totallyCollide(player, block, direction))
                {
                    // std::cout << "not allow to continue" << std::endl;
                    continue;
                }
                if (direction == Direction::Top && !sf::Keyboard::isKeyPressed(keybinding.getKey(KeyBinding::Action::Tele)))
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
                block->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/flagpole.wav"), false, true, sf::seconds(1.f));
                break;
            }
        }
    }
};


// tao 1 cai struct chua thong tin
// neu -1 thi set 9 va truyen thong tin vao struct
// neu 