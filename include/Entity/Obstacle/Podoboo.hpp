#pragma once

#include <Entity/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>

#include <Factories/EnemyFactory.hpp>

#include <Gameplay/Obstacles/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

class Podoboo : public Entity
{
public:
    Podoboo(float x, float y, float width, float height, float scale, bool upright)
    {
        // std::cout << "Creating Podoboo at position: (" << x << ", " << y << ") with size: (" << width << ", " << height << ")\n";
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        // Set the collision box for the Podoboo
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        addComponent<PodobooTag>(upright);

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom, Direction::Top};
        addComponent<DamageOnContactComponent>(directions);

        // Set the animation for the Podoboo
        if (upright)
        {
            addComponent<Animation>(EnemyFactory::getEnemyTexture("podoboo_rise"));
            addComponent<RigidBody>(sf::Vector2f(0.f, -1400.f));
            getComponent<RigidBody>().antiGravity = -800;
        }
        else
        {
            addComponent<Animation>(EnemyFactory::getEnemyTexture("podoboo_fall"));
            addComponent<RigidBody>(sf::Vector2f(0.f, 0.f));
            getComponent<RigidBody>().antiGravity = -800;
        }
    }
};
