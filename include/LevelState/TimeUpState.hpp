#pragma once

#include <LevelState/LevelState.hpp>

class TimeUpState : public LevelState
{
private:
    // sf::Font font;
    float timeElapsed = 0.0f;

public:
    // TimeUpState();
    TimeUpState(std::shared_ptr<Game> game);
    void update(GameManager *gameManager, float dt) override;
    std::shared_ptr<LevelState> getNewState(GameManager *gameManager) override;
    void render(GameManager *gameManager, sf::RenderWindow &window, int level) override;
    bool shouldReturnToMenu() const override;
};