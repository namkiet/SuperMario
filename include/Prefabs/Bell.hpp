#pragma once
#include <ECS/Entity.hpp>

#include <Factories/ItemFactory.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Gameplay/Background/Components.hpp>

#include <vector>

class Bell : public Entity
{
public:
    Bell(float x, float y, float width, float height, float scale)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        // Set the collision box for the bell
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the animation for the bell
        std::vector<const sf::Texture *> textures = ItemFactory::getItemTextures("bell");
        addComponent<Animation>(textures, (int)width,(int) height, 0.3f, true);

        addComponent<BellTag>();
    }
};