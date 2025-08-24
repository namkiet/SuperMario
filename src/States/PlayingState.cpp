#include <Game.hpp>
#include <States/PlayingState.hpp>
#include <Core/Variables.hpp>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>
#include <UI/KeyBinding.hpp>
#include <LevelState/InGameState.hpp>
#include <LevelState/IntroState.hpp>
#include <LevelState/LevelChosenState.hpp>
#include <LevelManager.hpp>
#include <Core/MessageBus.hpp>

PlayingState::PlayingState(std::shared_ptr<Game> game) : GameState(game), gameManager(nullptr)
{
    uiRoot = nullptr;

    // std::cout << " to playstate constructor ok" << std::endl;
    setupButton();
    // std::cout << "playstate constructor ok" << std::endl;
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
    }

    if (gameManager)
        gameManager->handleEvent(event, game->getWindow());
    // std::cout << "handle event here" << std::endl; 
    if (currentLevelState && currentLevelState->uiRoot) currentLevelState->uiRoot->handleEvent(event);
}

void PlayingState::update(float dt)
{
    if (LevelManager::instance().getSkipUpdate())
    {
        std::cout << "newLevel = " << LevelManager::instance().getLevel() << std::endl;
        setLevel(LevelManager::instance().getLevel());
        return;
    }
    else if (LevelManager::instance().getShouldLoadNextLevel())
    {
        if (level + 1 > 3 || level == -1)
        {
            game->popState();
            game->pushState("menu");
            return;
        }
        LevelManager::instance().setLevel(level + 1);
        // std::cout << "newLevel = " << newLevel << std::endl;
        setLevel(level + 1, true);
        return;
    }
    else if (currentLevelState && currentLevelState->shouldReturnToMenu())
    {
        game->popState();
        game->pushState("menu");
        return;
    }

    // if (gameManager)
    //     gameManager->update(dt);

    if (currentLevelState)
    {
        auto newState = currentLevelState->getNewState(gameManager);
        if (newState && newState.get() != currentLevelState.get())
        {
            currentLevelState = std::move(newState);
        }
        currentLevelState->update(gameManager, dt);
        
    }
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
    if (currentLevelState)
        currentLevelState->render(gameManager, window, level);
    if (currentLevelState && currentLevelState->uiRoot) currentLevelState->uiRoot->draw(window);
}

/*
level:
- intro: draw world
- levelChosenState: chon man
- inGame
- gameOver:
- time
*/
void PlayingState::setupButton()
{
    if (!UIFont.loadFromFile("BalooBhai2-ExtraBold.ttf"))
        assert(false);

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
}

void PlayingState::setLevel(int level, bool hasWonLastLevel, GameManager::Mode mode, const json& data)
{
    this->level = level;
    if (gameManager)
        delete gameManager;
        gameManager = new GameManager(level, hasWonLastLevel, mode, data);
        // std::cout << "manager is deleted and create again" << std::endl;
    setupButton();

    LevelManager::instance().setSkipUpdate(false);
    LevelManager::instance().setStatus("playing");
    LevelManager::instance().setShouldLoadNextLevel(false);

    if (mode != GameManager::Mode::NewGame)
    {
        LevelManager::instance().setLevel(level);
    }

    if (level == -1) 
    {
        currentLevelState = std::make_unique<InGameState>(game);
    }
    else
    {
        currentLevelState = std::make_unique<IntroState>(game);
    }
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

void PlayingState::reset()
{
    setLevel(0);
    currentLevelState = std::make_unique<LevelChosenState>(game);
}