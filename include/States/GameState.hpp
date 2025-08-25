#pragma once
#include <UI/Composite.hpp>
#include <memory>
namespace sf
{
    class Event;
    class RenderWindow;
}

class Game;

class GameState
{
protected:
    Game* game;
public:
    GameState(Game* game);
    virtual ~GameState() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
