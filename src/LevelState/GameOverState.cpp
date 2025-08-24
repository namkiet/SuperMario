#include <LevelState/GameOverState.hpp>
#include <LevelState/IntroState.hpp>
#include <iostream>
#include <LevelManager.hpp>
#include <CoinManager.hpp>
#include <ScoreManager.hpp>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>

// GameOverState::GameOverState()
// {
//     font.loadFromFile("BalooBhai2-ExtraBold.ttf");
// }

GameOverState::GameOverState(std::shared_ptr<Game> game) : LevelState(game)
{
    UIFont.loadFromFile("BalooBhai2-ExtraBold.ttf");
    auto &texholder = game->getTexHolder();

    using namespace UIConstant;

    auto makeButtonUtil = [this](
                              sf::Vector2f pos,
                              std::shared_ptr<sf::Shape> shape,
                              const std::string &label,
                              const StateColor &colors,
                              bool toggle,
                              unsigned int textSize,
                              std::function<void()> onClick = nullptr,
                              std::shared_ptr<sf::Sprite> sprite = nullptr,
                              sf::Color textColor = sf::Color::White,
                              bool setCenter = false)
    {
        return helperBuilder::makeButton(pos, shape, label, colors, toggle, textSize,
                                         UIFont, onClick, sprite, textColor, setCenter);
    };
    auto makeTextUtil = [this](
                            const std::string &content,
                            sf::Vector2f pos,
                            int charSize,
                            const StateColor &colorSetting,
                            bool setCenter = false)
    {
        return helperBuilder::makeText(content, pos, charSize, UIFont, colorSetting, setCenter);
    };

    auto dummydrawElement = std::make_shared<DrawableElement>();
    auto dummyInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), dummydrawElement);
    std::shared_ptr<UIContainer> dummyContainer = std::make_shared<UIContainer>(dummyInteractUI);
    dummyContainer->setActive(true);

    auto Deathrect = std::make_shared<sf::RectangleShape>(sf::Vector2f(UIConstant::ws.x, UIConstant::ws.y));
    Deathrect->setFillColor(sf::Color(34, 34, 34));
    auto DeathPanelDE = std::make_shared<DrawableElement>(Deathrect);
    Interact Deathpanelinteract(StateColor(sf::Color(34, 34, 34), sf::Color(34, 34, 34)));

    auto DeathIU = std::make_shared<InteractUI>(Deathpanelinteract, DeathPanelDE);
    std::shared_ptr<Panel> DeathPanel = std::make_shared<Panel>(DeathIU);
    DeathPanel->setActiveKey(sf::Keyboard::X);
    DeathPanel->setActive(true);
    dummyContainer->addComponent(DeathPanel);

    auto gameOverButton = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 3),
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(600.f, 100.f), 30.f),
        "",
        StateColor(sf::Color(255, 239, 235, 255), sf::Color(255, 239, 235, 255)),
        false,
        90,
        nullptr, nullptr, sf::Color(255, 49, 49, 255), true);

    auto gameOverText = helperBuilder::makeText("Game Over",
                                                sf::Vector2f(UIConstant::ws.x * 0.5f, UIConstant::ws.y * 0.27f),
                                                100,
                                                UIFont,
                                                StateColor(sf::Color::White, sf::Color::White, sf::Color(255, 49, 49), sf::Color::White), true);

    auto restartBtnDeath = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x * 0.5f, UIConstant::ws.y * 0.5), // Vị trí Restart
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Restart",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        50,
        [this, DeathPanel]()
        {
            shouldRestart = true;
            // // Hàm restart game
            // this->game->popState();
            // this->game->pushState("play");
            DeathPanel->setActive(false);
        },
        nullptr, sf::Color::White, true);

    auto exitBtnDeath = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x * 0.5f, UIConstant::ws.y * 0.6),
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Exit",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        50,
        [this]()
        {
            this->game->popState();
            this->game->pushState("menu");
        },
        nullptr, sf::Color::White, true);
    dummyContainer->addComponent(DeathPanel);
    DeathPanel->addComponent(gameOverText);
    DeathPanel->addComponent(restartBtnDeath);
    DeathPanel->addComponent(exitBtnDeath);

    uiRoot = dummyContainer;
}

void GameOverState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
    timeElapsed += dt;
}

void GameOverState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // // std::cout << "Rendering GameOverState" << std::endl;
    // //  Render game over screen
    // window.clear(sf::Color::Black);

    // sf::Text text;
    // text.setFont(UIFont);
    // text.setString("Game Over");
    // text.setCharacterSize(80);
    // text.setFillColor(sf::Color({255, 49, 49, 255}));
    // text.setPosition(250, 200);

    // window.draw(text);
    // if (uiRoot) uiRoot->draw(window);
    // std::cout << "render something in gameoverstate" << std::endl;
}

std::shared_ptr<LevelState> GameOverState::getNewState(GameManager *gameManager)
{
    if (shouldRestart)
    {
        shouldRestart = false;
        LevelManager::instance().getPrevMarioPosition() = sf::Vector2f(0.f, 0.f);
        LevelManager::instance().setSkipUpdate(true);
        LevelManager::instance().setLevel(LevelManager::instance().getLevel());
        gameManager->setLives(5);
    }
    return nullptr; // Placeholder, replace with actual logic if needed
}

bool GameOverState::shouldReturnToMenu() const
{
    return false;
}