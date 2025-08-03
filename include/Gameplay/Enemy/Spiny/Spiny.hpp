#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyEggState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyEggBehaviour.hpp>
#include <iostream>

class Spiny : public Entity
{
public:
    Spiny(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y) * scale, sf::Vector2f(14, 16) * scale));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(14, 16) * scale));

        addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Spiny/spiny_egg.png"), 14, 16, 2, 0.5f / 2));

        addComponent<EnemyTag>(std::make_shared<SpinyEggState>(), std::make_shared<SpinyEggBehaviour>());
        addComponent<SpinyPatrol>();

        addComponent<BlockTag>();
        addComponent<CanHitBlockTag>();

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom, Direction::Top};
        addComponent<DamageOnContactComponent>(directions);
    }
};