#pragma once
#include "GameState.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>

class PlayingState : public GameState
{
public:
    PlayingState();
    void handleEvent(Game &game, const sf::Event& event, sf::RenderWindow& window) override;
    void update(Game &game, float dt) override;
    void render(Game &game, sf::RenderWindow &window) override;
    void setLevel(int level);
    ~PlayingState() override;

private:
    GameManager *gameManager;
    int level = 1;
};
