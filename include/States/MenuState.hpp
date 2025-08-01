#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public GameState
{
private:
    sf::Font font;
    sf::Text playText;

public:
    MenuState();
    void handleEvent(Game &game, const sf::Event &event) override;
    void update(Game &game, float dt) override;
    void render(Game &game, sf::RenderWindow &window) override;
};