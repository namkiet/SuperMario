#include <LevelState/LevelState.hpp>
#include <ScoreManager.hpp>
#include <LevelManager.hpp>
#include <CoinManager.hpp>
#include <TimeManager.hpp>
class InGameState : public LevelState
{
private:
    ScoreUI *scoreUI = nullptr;
    LevelUI *levelUI = nullptr;
    CoinUI *coinUI = nullptr;
    TimeUI *timeUI = nullptr;
    bool shouldRestart = false;

public:
    void setupButton();

public:
    // InGameState();
    InGameState(std::shared_ptr<Game> game);
    void update(GameManager *gameManager, float dt) override;
    std::shared_ptr<LevelState> getNewState(GameManager *gameManager) override;
    void render(GameManager *gameManager, sf::RenderWindow &window, int level) override;
    bool shouldReturnToMenu() const override;
};