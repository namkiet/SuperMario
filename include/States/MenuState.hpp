#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public GameState
{
private:
    sf::Font font;
    sf::Text playText;

public:
    MenuState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
};