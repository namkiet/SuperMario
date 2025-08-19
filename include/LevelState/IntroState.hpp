#pragma once
#include <LevelState/LevelState.hpp>

class IntroState : public LevelState
{
private:
    float timeElapsed = 0.0f;
    // sf::Font font;

public:
    // IntroState();
    IntroState(std::shared_ptr<Game> game): LevelState(game) {
    }
    void update(GameManager *gameManager, float dt) override;
    std::shared_ptr<LevelState> getNewState(GameManager *gameManager) override;
    void render(GameManager *gameManager, sf::RenderWindow &window, int level) override;
    bool shouldReturnToMenu() const override;
};
