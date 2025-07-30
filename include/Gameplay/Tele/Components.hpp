#pragma once
#include <ECS/Component.hpp>
#include <SFML/System/Vector2.hpp>

// for another file
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Prefabs/Mario.hpp>
#include <unordered_map>
#include <cassert>

struct TelePort: public Component // for pipe
{
    Direction requireCollisionDirection;

    float intime;
    sf::Vector2f inVel;

    sf::Vector2f destination;

    float outtime;
    sf::Vector2f outVel;

    TelePort(Direction requireCollisionDirection = Direction::Top, float intime = 1.f, sf::Vector2f inVel = sf::Vector2f(0.f, 200.f), sf::Vector2f destination = sf::Vector2f(1000, 200), float outtime = 1.f, sf::Vector2f outVel = sf::Vector2f(0.f, -200.f))
    {
        this->requireCollisionDirection = requireCollisionDirection;
        this->intime = intime;
        this->inVel = inVel;
        this->destination = destination;
        this->outtime = outtime;
        this->outVel = outVel;
    }
};
struct TeleChanneling: public Component // for player
{
    float TeleTime; // time left to teleport
    bool DuringInTime;
    Entity* teleEntity; // ensure that it has teleport component
    TeleChanneling(Entity* teleEntity)
        : teleEntity(teleEntity), DuringInTime(true) {
            auto& teleInfo = teleEntity->getComponent<TelePort>();
            TeleTime = teleInfo.intime + teleInfo.outtime;
        }
};
