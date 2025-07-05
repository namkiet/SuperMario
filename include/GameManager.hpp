#pragma once

#include <SFML/Graphics.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>
#include <Ground.hpp>
#include <World.hpp>

class GameManager
{
public:
                            GameManager();
    void                    handleEvent(const sf::Event& event);
    void                    update(float dt);
    void                    draw(sf::RenderWindow& window) const;

private:
    World                   world;
    Entity* pipe;
};
