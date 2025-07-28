#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Pipe/Components.hpp>
#include <Gameplay/Tele/Components.hpp>
class Pipe : public Entity
{
public:
    Pipe(float x, float y, float width, float height, int scale, int index, bool allowTeleport = false)
    {
        // Set the size of the collision box for the pipe
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));
        getComponent<BoxCollider2D>().offset = sf::Vector2f(2 * scale, 0);
        getComponent<BoxCollider2D>().size = sf::Vector2f((width - 4) * scale, height * scale);
        // Set the transform for the pipe
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        // Add the pipe tag
        addComponent<BlockTag>();

        addComponent<PipeTag>();
        // Set the texture for the player
        if (index == 0)
        {
            addComponent<Animation>(TextureManager::load("assets/Pipe/Pipe1_0.png"));
        }

        else if (index == 1)
        {
            
            addComponent<Animation>(TextureManager::load("assets/Pipe/Pipe1_1.png"));
        }

        else if (index == 2)
        {
            addComponent<Animation>(TextureManager::load("assets/Pipe/Pipe1_2.png"));
        }

        else if (index == 3)
        {
            addComponent<Animation>(TextureManager::load("assets/Pipe/Pipe1_3.png"));
        }

        if (allowTeleport)
        {
            addComponent<TelePort>();
        }
        else
        {
            addComponent<unenterablePipe>();
        }
    }
};