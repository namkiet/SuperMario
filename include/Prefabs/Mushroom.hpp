#pragma once

#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Rendering/ZIndex.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <vector>

class Mushroom1 : public Entity
{
public:
    Mushroom1(float x, float y, float width, float height, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        // addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        // addComponent<Animation>(TextureManager::load("assets/Item/Mushroom/Mushroom1_0.png"));

        addComponent<Animation>(itemFactory.getItemTexture("mushroom1"));
        addComponent<ZIndex>(-1);

        addComponent<MushroomTag>(MushroomTag::Buff::GROW_UP);
    }
};

class Mushroom2 : public Entity
{
public:
    Mushroom2(float x, float y, float width, float height, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        // addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        // addComponent<Animation>(TextureManager::load("assets/Item/Mushroom/Mushroom1_1.png"));

        addComponent<Animation>(itemFactory.getItemTexture("mushroom2"));
        addComponent<ZIndex>(-1);

        addComponent<MushroomTag>(MushroomTag::Buff::GIVE_ONE_MORE_LIFE);
    }
};

class LevelMushroom : public Entity
{
public:
    LevelMushroom(float x, float y, float width, float height, int newLevel, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        addComponent<Animation>(itemFactory.getItemTexture("mushroom1"));
        addComponent<ZIndex>(-1);

        if (newLevel == 1)
            addComponent<MushroomTag>(MushroomTag::Buff::GET_TO_LEVEL_1);
        else if (newLevel == 2)
            addComponent<MushroomTag>(MushroomTag::Buff::GET_TO_LEVEL_2);
        else if (newLevel == 3)
            addComponent<MushroomTag>(MushroomTag::Buff::GET_TO_LEVEL_3);
        else if (newLevel == 4)
            addComponent<MushroomTag>(MushroomTag::Buff::GET_TO_LEVEL_4);
    }
};