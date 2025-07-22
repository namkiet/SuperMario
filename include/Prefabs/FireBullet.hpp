#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <vector>

class FireBullet : public Entity
{
private:
    static int count;

public:
    FireBullet(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the animation for the fire bullet
        std::vector<const sf::Texture *> textures =
            {
                &TextureManager::load("assets/Item/FireBullet/FireBullet_0.png"),
                &TextureManager::load("assets/Item/FireBullet/FireBullet_1.png"),
                &TextureManager::load("assets/Item/FireBullet/FireBullet_2.png"),
                &TextureManager::load("assets/Item/FireBullet/FireBullet_3.png")};
        addComponent<Animation>(textures, width, height, 0.15f, true);

        addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        addComponent<PatrolComponent>();
        getComponent<PatrolComponent>().moveSpeed = 200.0f;

        addComponent<RigidBody>(sf::Vector2f(0, 50));


        // Add the fire bullet tag
        addComponent<FireBulletTag>();

        ++count;
    }
    ~FireBullet()
    {
        // std::cout << "FireBullet destroyed" << std::endl;
        --count;
    }
    static int getCount()
    {
        return count;
    }
};

int FireBullet::count = 0; // Initialize static count variable