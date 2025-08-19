#include <LevelState/IntroState.hpp>
#include <LevelState/InGameState.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>


// IntroState::IntroState()
// {
//     font.loadFromFile("BalooBhai2-ExtraBold.ttf");
// }

void IntroState::update(GameManager *gameManager, float dt)
{
    timeElapsed += dt;
}

std::shared_ptr<LevelState> IntroState::getNewState(GameManager *gameManager)
{
    if (timeElapsed >= 1.5f) // Assuming 3 seconds for the intro
    {
        TimeManager::instance().reset();
        return std::make_shared<InGameState>(game);
    }
    return nullptr;
}

void IntroState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering IntroState" << std::endl;
    window.setView(window.getDefaultView());
    window.clear(sf::Color(34, 34, 34, 255));

    sf::Sprite smallMap;

    std::string lives = std::to_string(GameManager::getLives());
    sf::Text livesText;
    livesText.setFont(UIFont);
    livesText.setString("x " + lives);
    livesText.setCharacterSize(100);
    livesText.setFillColor(sf::Color({255, 239, 235, 255}));
    livesText.setPosition(500, 180);
    window.draw(livesText);

    sf::Text introText;
    introText.setFont(UIFont);
    introText.setCharacterSize(100);
    introText.setFillColor(sf::Color({255, 239, 235, 255}));
    introText.setPosition(307, 50);

    if (level == 1)
    {
        smallMap = sf::Sprite(TextureManager::load("assets/Background/map11_3.png"));
        introText.setString("World 1");
    }

    else if (level == 2)
    {
        smallMap = sf::Sprite(TextureManager::load("assets/Background/map61_3.png"));
        introText.setString("World 2");
    }
    else if (level == 3)
    {
        smallMap = sf::Sprite(TextureManager::load("assets/Background/map54_3.png"));
        introText.setString("World 3");
    }

    smallMap.setPosition(240, 345);
    window.draw(smallMap);
    window.draw(introText);
}

bool IntroState::shouldReturnToMenu() const
{
    return false;
}