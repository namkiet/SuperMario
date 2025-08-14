#include <Game.hpp>
#include <States/PlayingState.hpp>
#include <Core/Variables.hpp>

PlayingState::PlayingState(std::shared_ptr<Game> game) : GameState(game), gameManager(nullptr)
{
}

void PlayingState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            game->popState();
            game->pushState("menu");
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            game->pushState("settings");
        }
    }

    if (gameManager)
        gameManager->handleEvent(event);
}

void PlayingState::update(float dt)
{
    if (gameManager->getWorld().getSkipUpdate())
    {
        setLevel(gameManager->getWorld().getNewLevel());
        return;
    }

    if (gameManager)
        gameManager->update(dt);

}

void PlayingState::render(sf::RenderWindow &window)
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
    gameManager->draw(window, level);
}

void PlayingState::setLevel(int level)
{
    this->level = level;
    if (gameManager)
        delete gameManager;
    gameManager = new GameManager(level, [this](int newLevel)
                                  { this->requestLevelReload(newLevel); });
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