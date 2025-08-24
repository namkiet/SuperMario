#pragma once

#include <States/GameState.hpp>

#include <SFML/Graphics.hpp>

#include <vector>

class LoadState : public GameState
{
private:
    std::vector<sf::RectangleShape> saveBoxes;
    std::vector<sf::Sprite> saveBoxSprites;

public:
    LoadState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
};