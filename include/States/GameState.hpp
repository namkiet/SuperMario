#pragma once
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
    std::shared_ptr<Game> game;
public:
    GameState(std::shared_ptr<Game> game);
    virtual ~GameState() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
