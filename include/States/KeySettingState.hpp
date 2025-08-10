#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <UI/Button.hpp>
class KeySettingState: public GameState
{
private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

    std::vector<std::shared_ptr<Button>> buttonList;
public:
    KeySettingState(std::shared_ptr<Game> game);

    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
};