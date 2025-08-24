#pragma once

#include <Entity/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Rendering/ZIndex.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <vector>

class Star : public Entity
{
public:
    Star(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        // addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        std::vector<const sf::Texture *> textures = ItemFactory::getItemTextures("star");
        addComponent<Animation>(textures,(int) width,(int) height, 0.15f, true);
        addComponent<ZIndex>(-3);

        addComponent<StarTag>();
        // addComponent<CollectableTag>();
    }
};