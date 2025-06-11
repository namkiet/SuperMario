#pragma once
#include <World.hpp>
#include <Components/Input.hpp>
#include <SFML/Graphics.hpp>

class PlayerInputSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Input>())
        {
            auto& input = entity->getComponent<Input>();
            input.moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            input.moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            input.jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        }
    }
};