#pragma once
#include <World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
class GameManager
{
public:
                            GameManager();
    void                    handleEvent(const sf::Event& event);
    void                    update(float dt);
    void                    draw(sf::RenderWindow& window) const;

private:
    World                   world;
    LevelHandler levelHandler;
};
