#include <Game.hpp>
#include <States/PlayingState.hpp>
#include <Core/Variables.hpp>
#include <LevelState/InGameState.hpp>
#include <LevelState/IntroState.hpp>
#include <LevelState/LevelChosenState.hpp>

PlayingState::PlayingState() : gameManager(nullptr)
{
    currentLevelState = std::make_unique<LevelChosenState>();
}

void PlayingState::handleEvent(Game &game, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            game.popState();
            game.pushState("menu");
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            game.pushState("settings");
        }
    }

    if (gameManager)
        gameManager->handleEvent(event);
}

void PlayingState::update(Game &game, float dt)
{
    if (gameManager->getWorld().getSkipUpdate())
    {
        setLevel(gameManager->getWorld().getNewLevel());
        return;
    }
    else if (gameManager->getShouldLoadNextLevel())
    {
        if (level + 1 > 3)
        {
            game.popState();
            game.pushState("menu");
            return;
        }
        setLevel(level + 1);
        return;
    }
    else if (gameManager->goBackToMenu())
    {
        game.popState();
        game.pushState("menu");
        return;
    }

    // if (gameManager)
    //     gameManager->update(dt);

    if (level != 0 && currentLevelState)
    {
        auto newState = currentLevelState->getNewState(gameManager);
        if (newState && newState.get() != currentLevelState.get())
        {
            currentLevelState = std::move(newState);
        }
        currentLevelState->update(gameManager, dt);
    }
    else
    {
        gameManager->update(dt);
    }
}

void PlayingState::render(Game &, sf::RenderWindow &window)
{
    switch (level)
    {
    case 1:
        window.clear(sf::Color(92, 148, 252, 255));
        break;
    case 2:
        window.clear(sf::Color(0, 0, 0, 255));
        break;
    case 3:
        window.clear(sf::Color(0, 0, 0, 255));
        break;
    default:
        window.clear(sf::Color(0, 0, 0, 255));
        break;
    }
    // gameManager->draw(window, level);
    if (level != 0 && currentLevelState)
        currentLevelState->render(gameManager, window, level);
    else
        gameManager->draw(window, level);
}

void PlayingState::setLevel(int level)
{
    this->level = level;
    if (gameManager)
        delete gameManager;
    gameManager = new GameManager(level, [this](int newLevel)
                                  { this->requestLevelReload(newLevel); });
    currentLevelState = std::make_unique<IntroState>();
}

PlayingState::~PlayingState()
{
    if (gameManager)
        delete gameManager;
    gameManager = nullptr;
}

void PlayingState::requestLevelReload(int newLevel)
{
    setLevel(newLevel);
}