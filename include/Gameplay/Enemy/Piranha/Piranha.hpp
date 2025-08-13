#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Rendering/ZIndex.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Enemy/Piranha/Components.hpp>
#include <Gameplay/Enemy/Piranha/PiranhaNormalState.hpp>
#include <Gameplay/Enemy/Piranha/PiranhaBehaviour.hpp>
#include <Factories/EnemyFactory.hpp>

class Piranha : public Entity
{
public:
    Piranha(float x, float y, float scale)
    {
        addComponent<RigidBody>(sf::Vector2f(0, 0), false);
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(16, 24) * scale);
        addComponent<BoxCollider2D>(sf::Vector2f(16, 24) * scale);
        addComponent<Animation>(EnemyFactory::getEnemyTexture("piranha_normal"), 16, 24, 2, 0.25f);
        addComponent<ZIndex>(-1);
        addComponent<EnemyTag>(std::make_shared<PiranhaNormalState>(), std::make_shared<PiranhaBehaviour>());
        addComponent<PiranhaPatrol>(y * scale, 24 * 3 + 16, 2.0f, 2.0f);
        addComponent<PassThroughTag>();

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Top, Direction::Bottom};
        addComponent<DamageOnContactComponent>(directions);
    }
};