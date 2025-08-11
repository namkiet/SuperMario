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
#include <Gameplay/Enemy/Lakitu/Components.hpp>
#include <Gameplay/Enemy/Lakitu/LakituNormalState.hpp>
#include <Gameplay/Enemy/Lakitu/LakituNormalBehaviour.hpp>

class Lakitu : public Entity
{
public:
    Lakitu(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0), false));
        addComponent<Transform>(Transform(sf::Vector2f(x, y) * scale, sf::Vector2f(16, 24) * scale));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(16, 24) * scale));

        addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Lakitu/Lakitu_normal.png"), 16, 24, 1, 0));

        addComponent<EnemyTag>(std::make_shared<LakituNormalState>(), std::make_shared<LakituNormalBehaviour>());
        addComponent<LakituPatrol>();
        addComponent<LakituAttack>();
        addComponent<TowardPlayer>();
        
        addComponent<StompableTag>();

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};
        addComponent<DamageOnContactComponent>(directions);
    }
};