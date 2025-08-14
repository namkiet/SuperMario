#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBulletBehaviour.hpp>

class BowserBullet : public Entity
{
public:
    BowserBullet(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0), false));
        addComponent<Transform>(Transform(sf::Vector2f(x, y) * scale, sf::Vector2f(24, 15) * scale));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(24, 15) * scale));

        addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_bullet"), 24, 15, 3, 0.25f);

        addComponent<EnemyTag>(nullptr, std::make_shared<BowserBulletBehaviour>());
        addComponent<BowserBulletPatrol>();

        addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/fire.wav"));

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom, Direction::Top};
        addComponent<DamageOnContactComponent>(directions);
    }
};