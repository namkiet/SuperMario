#pragma once
#include <States/GameState.hpp>
#include <SFML/Graphics.hpp>

class SettingsState : public GameState 
{
private:
    sf::Font font;
    sf::Text info;

public:
    SettingsState(Game* game);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};