#pragma once

#include <Entity/Entity.hpp>

#include <Core/Variables.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/PipeFactory.hpp>

#include <Gameplay/Pipe/Components.hpp>
#include <Gameplay/Tele/Components.hpp>

class Pipe : public Entity
{
public:
    Pipe(float x, float y, float width, float height, float scale, int index, bool allowTeleport)
    {
        // Set the size of the collision box for the pipe
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);
        getComponent<BoxCollider2D>().offset = sf::Vector2f(2 * scale, 0);
        getComponent<BoxCollider2D>().size = sf::Vector2f((width - 4) * scale, height * scale);
        // Set the transform for the pipe
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        // Add the pipe tag
        addComponent<BlockTag>();

        addComponent<PipeTag>();

        // Set the texture for the pipe
        switch (index)
        {
        case 0:
            addComponent<Animation>(PipeFactory::getPipeTexture("pipe1"));
            break;
        case 1:
            addComponent<Animation>(PipeFactory::getPipeTexture("pipe2"));
            break;
        case 2:
            addComponent<Animation>(PipeFactory::getPipeTexture("pipe3"));
            break;
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