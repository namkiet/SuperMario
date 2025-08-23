#include <LevelState/LevelChosenState.hpp>
#include <LevelState/IntroState.hpp>
#include <LevelManager.hpp>
#include <CoinManager.hpp>
#include <ScoreManager.hpp>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>
#include <Core/MessageBus.hpp>

LevelChosenState::LevelChosenState(std::shared_ptr<Game> game): LevelState(game) 
{
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
        // std::cout << "level = " << LevelManager::instance().getLevel() << " \n";
    // assert(LevelManager::instance().getLevel() == 0);

    float sameHeightStat = UIConstant::ws.y * 0.9;
        StateColor marionameColorSetting(sf::Color::White, sf::Color::White, sf::Color(153, 153, 153), sf::Color(255, 49, 49)); 
        StateColor luiginameColorSetting(sf::Color::White, sf::Color::White, sf::Color(153, 153, 153), sf::Color(102, 210, 50));
        auto MarioNameMessage = helperBuilder::makeCanActiveText("Mario", sf::Vector2f(UIConstant::ws.x * 0.35, sameHeightStat),
                            30, UIFont, marionameColorSetting, true);

        auto LuigiNameMessage = helperBuilder::makeCanActiveText("Luigi", sf::Vector2f(UIConstant::ws.x * 0.85, sameHeightStat),
                            30, UIFont, luiginameColorSetting, true);

        auto RedMarioBtn = makeButtonUtil(
            sf::Vector2f(UIConstant::ws.x * 0.2, sameHeightStat), 
            std::make_shared<sf::CircleShape>(60.f),
            "",
            StateColor(sf::Color(0,0,0,0), sf::Color(153,153,153, 200)),
            true,
            0,
            [MarioNameMessage]() {
                MarioNameMessage->setActive(true);
                MessageBus::publish("SelectedMario");
            },
            std::make_shared<sf::Sprite>(texholder.get(TexType::mariochoose)),
            sf::Color::White, /*setCenter = */true
            );

        auto GreenMarioBtn = makeButtonUtil(
            sf::Vector2f(UIConstant::ws.x * 0.7, sameHeightStat), 
            std::make_shared<sf::CircleShape>(60.f),
            "",
            StateColor(sf::Color(0,0,0,0), sf::Color(153,153,153, 200)),
            true,
            0,
            [LuigiNameMessage]() {
                LuigiNameMessage->setActive(true);
                MessageBus::publish("SelectedLuigi");
            },
            std::make_shared<sf::Sprite>(texholder.get(TexType::luigichoose)),
            sf::Color::White, /*setCenter = */true
            );

        auto optdrawElement = std::make_shared<DrawableElement>();
        auto optInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), optdrawElement);
        std::shared_ptr<OptionContainer> CharOptContainer = std::make_shared<OptionContainer>(optInteractUI, /*mustHaveOp=*/true);
        CharOptContainer->setActive(true);
        
        CharOptContainer->addComponent(RedMarioBtn);
        CharOptContainer->addComponent(GreenMarioBtn);
        
        auto msgdrawElement = std::make_shared<DrawableElement>();
        auto msgInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), msgdrawElement);
        std::shared_ptr<OptionContainer> msgOptContainer = std::make_shared<OptionContainer>(msgInteractUI, /*mustHaveOp=*/true);
        msgOptContainer->setActive(true);
        
        msgOptContainer->addComponent(MarioNameMessage);
        msgOptContainer->addComponent(LuigiNameMessage);
        
        

        
        auto dummydrawElement = std::make_shared<DrawableElement>();
        auto dummyInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), dummydrawElement);
        std::shared_ptr<UIContainer> dummyContainer = std::make_shared<UIContainer>(dummyInteractUI);
        dummyContainer->setActive(true);
        dummyContainer->addComponent(msgOptContainer);
    
        dummyContainer->addComponent(CharOptContainer);

        uiRoot = dummyContainer;

}

void LevelChosenState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
}

std::shared_ptr<LevelState> LevelChosenState::getNewState(GameManager *gameManager)
{
    if (LevelManager::instance().getStatus() == std::string("intro"))
    {
        LevelManager::instance().setSkipUpdate(true);
        gameManager->setLives(5);
        CoinManager::instance().reset();
        ScoreManager::instance().reset();
        LevelManager::instance().reset();
    }
    return nullptr;
}

void LevelChosenState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering LevelChosenState" << std::endl;
    gameManager->draw(window, level);
}

bool LevelChosenState::shouldReturnToMenu() const
{
    return false;
}