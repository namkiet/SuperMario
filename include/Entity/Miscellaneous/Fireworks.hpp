#pragma once

#include <Entity/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/LifeSpan/Components.hpp>

#include <vector>

class Fireworks : public Entity
{
private:
    static int fireworksCount;

public:
    Fireworks(float width, float height)
    {
        // Set random positions
        int i = 0;
        if (!positions.empty())
        {
            i = std::rand() % positions.size();
        }

        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(positions[i].x * 3, positions[i].y * 3), sf::Vector2f(width, height));

        positions.erase(positions.begin() + i); // Remove the used position

        // Set the collision box for the fireworks
        addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the fireworks
        addComponent<Animation>(ItemFactory::getItemTexture("fireworks"));

        addComponent<LifeSpan>(1.0f);

        ++fireworksCount;
    }
    ~Fireworks()
    {
        --fireworksCount;
    }
    static int getFireworksCount() { return fireworksCount; }
    static std::vector<sf::Vector2f> positions;
};
