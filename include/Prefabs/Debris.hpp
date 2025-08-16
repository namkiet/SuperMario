#pragma once
#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Item/Components.hpp>

#include <vector>

class SmallDebris1 : public Entity
{
public:
    SmallDebris1(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x - width, y + height), sf::Vector2f(width, height));

        // Set the animation for the debris
        addComponent<Animation>(ItemFactory::getItemTexture("debris1"));

        // Set the rigid body for physics
        addComponent<RigidBody>(sf::Vector2f(0, -600));

        // Add the debris tag
        addComponent<DebrisTag>(); // General tag for debris

        //
        addComponent<Debris1Tag>(); // Add the specific debris tag

        // std::cout << "SmallDebris1 created at position: (" << x - width << ", " << y + height << ")" << std::endl;
    }
};

class SmallDebris2 : public Entity
{
public:
    SmallDebris2(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x - width, y - height), sf::Vector2f(width, height));

        // Set the animation for the debris
        addComponent<Animation>(ItemFactory::getItemTexture("debris2"));

        // Set the rigid body for physics
        addComponent<RigidBody>(sf::Vector2f(0, -600));

        // Add the debris tag
        addComponent<DebrisTag>(); // General tag for debris

        // Add the specific debris tag
        addComponent<Debris2Tag>();

        // std::cout << "SmallDebris2 created at position: (" << x - width << ", " << y - height << ")" << std::endl;
        
    }
};

class SmallDebris3 : public Entity
{
public:
    SmallDebris3(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x + width, y + height), sf::Vector2f(width, height));

        // Set the animation for the debris
        addComponent<Animation>(ItemFactory::getItemTexture("debris3"));

        // Set the rigid body for physics
        addComponent<RigidBody>(sf::Vector2f(0, -600));

        // Add the debris tag
        addComponent<DebrisTag>(); // General tag for debris

        // Add the specific debris tag
        addComponent<Debris3Tag>();

        // std::cout << "SmallDebris3 created at position: (" << x + width << ", " << y + height << ")" << std::endl;
    }
};

class SmallDebris4 : public Entity
{
public:
    SmallDebris4(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x + width, y - height), sf::Vector2f(width, height));

        // Set the animation for the debris
        addComponent<Animation>(ItemFactory::getItemTexture("debris4"));
        
        // Set the rigid body for physics
        addComponent<RigidBody>(sf::Vector2f(0, -600));

        // Add the debris tag
        addComponent<DebrisTag>(); // General tag for debris

        // Add the specific debris tag
        addComponent<Debris4Tag>();
        
        // std::cout << "SmallDebris4 created at position: (" << x + width << ", " << y - height << ")" << std::endl;
    }
};