#pragma once
#include <SFML/Graphics.hpp>
#include <Components/Declaration.hpp>
#include <Entity.hpp>

class PlayerInputSystem
{
public:
    void addEntity(Entity* entity)
    {
        entityList.push_back(entity);
    }

    void update(float dt)
    {
        for (Entity* entity : entityList)
        {
            auto& input = entity->getComponent<Input>();
            input.moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            input.moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            input.jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        }
    }   

private:
    std::vector<Entity*> entityList;
};