#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class SettingsState : public GameState 
{
private:
    sf::Font font;
    sf::Text info;

public:
    SettingsState();
    void handleEvent(Game& game, sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;
};
