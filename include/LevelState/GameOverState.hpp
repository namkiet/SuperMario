#pragma once
#include <LevelState/LevelState.hpp>
class GameOverState : public LevelState
{
private:
    float timeElapsed = 0.0f;
    sf::Font font;

public:
    GameOverState()
    {
        font.loadFromFile("BalooBhai2-ExtraBold.ttf");
    }
    void update(GameManager *gameManager, float dt) override;
    std::shared_ptr<LevelState> getNewState(GameManager *gameManager) override;
    void render(GameManager *gameManager, sf::RenderWindow &window, int level) override;
};