#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Item/Components.hpp>
#include <vector>
#include <iostream>

class SmallDebris1 : public Entity
{
public:
    SmallDebris1(float x, float y, float width, float height, int spriteIndex)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x - width, y + height), sf::Vector2f(width, height));

        // Set the animation for the debris
        std::string tileFolder = "assets/Debris/";
        addComponent<Animation>(TextureManager::load(tileFolder + "Debris" + std::to_string(spriteIndex) + "_0.png"));

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
    SmallDebris2(float x, float y, float width, float height, int spriteIndex)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x - width, y - height), sf::Vector2f(width, height));

        // Set the animation for the debris
        std::string tileFolder = "assets/Debris/";
        addComponent<Animation>(TextureManager::load(tileFolder + "Debris" + std::to_string(spriteIndex) + "_1.png"));

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
    SmallDebris3(float x, float y, float width, float height, int spriteIndex)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x + width, y + height), sf::Vector2f(width, height));

        // Set the animation for the debris
        std::string tileFolder = "assets/Debris/";
        addComponent<Animation>(TextureManager::load(tileFolder + "Debris" + std::to_string(spriteIndex) + "_2.png"));
        
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
    SmallDebris4(float x, float y, float width, float height, int spriteIndex)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x + width, y - height), sf::Vector2f(width, height));

        // Set the animation for the debris
        std::string tileFolder = "assets/Debris/";
        addComponent<Animation>(TextureManager::load(tileFolder + "Debris" + std::to_string(spriteIndex) + "_3.png"));

        // Set the rigid body for physics
        addComponent<RigidBody>(sf::Vector2f(0, -600));

        // Add the debris tag
        addComponent<DebrisTag>(); // General tag for debris

        // Add the specific debris tag
        addComponent<Debris4Tag>();
        
        // std::cout << "SmallDebris4 created at position: (" << x + width << ", " << y - height << ")" << std::endl;
    }
};