// #pragma once
// #include <ECS/Entity.hpp>
// #include <Engine/Core/Transform.hpp>
// #include <Engine/Core/RigidBody.hpp>
// #include <Engine/Animation/Animation.hpp>
// #include <Engine/Physics/BoxCollider2D.hpp>
// #include <Gameplay/Patrol/Components.hpp>
// #include <Gameplay/Stomp/Components.hpp>
// #include <Gameplay/DamageOnContact/Components.hpp>
// #include <Core/TextureManager.hpp>
// #include <Core/Variables.hpp>

// class Enemy : public Entity
// {
// public:
//     Enemy(float x, float y)
//     {
//         addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
//         addComponent<Transform>(Transform(sf::Vector2f(x, y), 0.5f * SIZE::GRID));
//         addComponent<BoxCollider2D>(BoxCollider2D(0.5f * SIZE::GRID));

//         addComponent<Animation>(Animation(TextureManager::load("assets/goomba.png"), 16, 16, 2, 0.5f / 2));


//         addComponent<BlockTag>();

//         addComponent<PatrolComponent>();
//         addComponent<StompableTag>();

//         std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
//         addComponent<DamageOnContactComponent>(directions);
//     }
// };

#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <vector>

class Enemy : public Entity
{
public:
    Enemy(float x, float y, float width, float height, int scale, int index)
    {
        // Add enemy tag
        // addComponent<EnemyTag>();

        // // Set the rigid body for physics interactions
        // addComponent<RigidBody>(sf::Vector2f(0, 0), false);

        // if (index == 0)
        // {
        //     // Add the goomba tag
        //     addComponent<Goomba>();

        //     // Set the texture for the goomba
        //     std::vector<sf::Texture> textures = {
        //         TextureManager::load("assets/Enemy/Goomba/NormalGoomba1_0.png"),
        //         TextureManager::load("assets/Enemy/Goomba/NormalGoomba1_1.png")};

        //     addComponent<Animation>(textures, width * scale, height * scale, 0.15f, true);

        //     // Set the size of the collision box for the enemy
        //     addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        //     // Set the transform for the enemy
        //     addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));
        // }
        // else if (index == 1)
        // {
        //     // Add the koopa tag
        //     addComponent<Koopa>();

        //     // Set the texture for the koopa
        //     std::vector<sf::Texture> textures = {
        //         TextureManager::load("assets/Enemy/Koopa/NormalKoopa1_0.png"),
        //         TextureManager::load("assets/Enemy/Koopa/NormalKoopa1_1.png")};

        //     addComponent<Animation>(textures, width * scale, height * scale, 0.15f, true);

        //     // Set the size of the collision box for the enemy
        //     addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        //     // Set the transform for the enemy
        //     addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));
        // }

        // addComponent<PatrolComponent>();

        // addComponent<StompableTag>();

        // std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};

        // addComponent<DamageOnContactComponent>(directions);
    }
};
