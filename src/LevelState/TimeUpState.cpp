#include <LevelState/TimeUpState.hpp>
#include <iostream>
#include <LevelState/IntroState.hpp>
#include <LevelManager.hpp>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>


TimeUpState::TimeUpState(std::shared_ptr<Game> game): LevelState(game) 
{
    UIFont.loadFromFile("BalooBhai2-ExtraBold.ttf");
    auto& texholder = game->getTexHolder();


    using namespace UIConstant;

     auto makeButtonUtil =[this](
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
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
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        const StateColor& colorSetting,
        bool setCenter = false)
        {
            return helperBuilder::makeText(content, pos, charSize, UIFont, colorSetting, setCenter);
        };
    

        auto dummydrawElement = std::make_shared<DrawableElement>();
        auto dummyInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), dummydrawElement);
        std::shared_ptr<UIContainer> dummyContainer = std::make_shared<UIContainer>(dummyInteractUI);
        dummyContainer->setActive(true);
        
        auto TimeUprect = std::make_shared<sf::RectangleShape>(sf::Vector2f(UIConstant::ws.x, UIConstant::ws.y));
        TimeUprect->setFillColor(sf::Color(34, 34, 34));
        auto TimeUpPanelDE = std::make_shared<DrawableElement>(TimeUprect);
        Interact panelinteract(StateColor(sf::Color(34,34,34), sf::Color(34,34,34)));
        
        auto TimeUpIU = std::make_shared<InteractUI>(panelinteract, TimeUpPanelDE);
        auto TimeUpPanel = std::make_shared<Panel>(TimeUpIU);
        TimeUpPanel->setActiveKey(sf::Keyboard::C);
        dummyContainer->addComponent(TimeUpPanel);
        // ============== TimeUp =========================
        auto timeUpText = helperBuilder::makeText("Time Up", 
                                               sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 3),
                                               40, UIFont, StateColor(sf::Color::White, sf::Color::White,
                                            sf::Color(255,49, 49), sf::Color::White), true);

        auto restartBtnTimeUp = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.5),  // Vị trí Restart
            std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f), 
            "Restart", 
            StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
            false,
            25, 
            [this, TimeUpPanel]() { 
                this->game->popState(); 
                this->game->pushState("play");
                TimeUpPanel->setActive(false);
            }, nullptr, sf::Color::White, true
        );

            auto exitBtnTimeUp = makeButtonUtil(
                sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.6),
                std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
                "Exit", 
                StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
                false,
                25, 
                [this]() { 
                    this->game->popState(); 
                    this->game->pushState("menu");
                },
                nullptr, sf::Color::White, true
            );
        auto exitBtnDeath = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.6),
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Exit", 
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        25, 
        [this]() { 
            this->game->popState(); 
            this->game->pushState("menu");
        },
        nullptr, sf::Color::White, true
    );
    dummyContainer->addComponent(TimeUpPanel);
        TimeUpPanel->addComponent(timeUpText);
        TimeUpPanel->addComponent(restartBtnTimeUp);
        TimeUpPanel->addComponent(exitBtnTimeUp);

    uiRoot = dummyContainer;
}


void TimeUpState::update(GameManager *gameManager, float dt)
{
    if (GameManager::getLives() > 1)
    {
        return;
    }
    timeElapsed += dt;
}

std::shared_ptr<LevelState> TimeUpState::getNewState(GameManager *gameManager)
{
    if (GameManager::getLives() > 1)
    {
        LevelManager::instance().setSkipUpdate(true);
        return std::make_shared<IntroState>(game);
    }
    return nullptr;
}

void TimeUpState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering TimeUpState" << std::endl;
    // Render the time up state, e.g., show a message or animation
    // sf::Text text;
    // text.setFont(UIFont);
    // text.setString("Time Up!");
    // text.setCharacterSize(100);
    // text.setFillColor(sf::Color({255, 49, 49, 255}));
    // text.setPosition(250, 200);

    // window.draw(text);
}

// TimeUpState::TimeUpState()
// {
//     UI.loadFromFile("BalooBhai2-ExtraBold.ttf");
// }

bool TimeUpState::shouldReturnToMenu() const
{
    if (timeElapsed > 1.5f)
        return true;
    return false;
}