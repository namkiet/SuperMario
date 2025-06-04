#pragma once
#include "GameState.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>

class PlayingState : public GameState 
{
public:
    PlayingState();
    void handleEvent(Game& game, sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;

private:
    World world;
};
