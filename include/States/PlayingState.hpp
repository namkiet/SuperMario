#pragma once
#include "GameState.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>

class PlayingState : public GameState
{
public:
    PlayingState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
    void setLevel(int level);
    ~PlayingState() override;

private:
    GameManager *gameManager;
    int level = 1;
};
