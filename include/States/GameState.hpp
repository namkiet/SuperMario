#pragma once

namespace sf
{
    class Event;
    class RenderWindow;
}

class Game;

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void handleEvent(Game& game, const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(Game& game, float dt) = 0;
    virtual void render(Game& game, sf::RenderWindow& window) = 0;
};
