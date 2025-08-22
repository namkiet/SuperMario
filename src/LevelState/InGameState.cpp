#include <LevelState/InGameState.hpp>
#include <LevelState/GameOverState.hpp>
#include <LevelState/GameWinState.hpp>
#include <LevelState/TimeUpState.hpp>
#include <LevelState/IntroState.hpp>
#include <iostream>
#include <memory>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>
#include <UI/KeyBinding.hpp>
#include <UI/CommonUIPool.hpp>
#include <Core/MessageBus.hpp>
#include <string>

// InGameState::InGameState()
// {
//     scoreUI = new ScoreUI();
//     ScoreManager::instance().addObserver(scoreUI);

//     levelUI = new LevelUI();
//     LevelManager::instance().addObserver(levelUI);

//     coinUI = new CoinUI();
//     CoinManager::instance().addObserver(coinUI);

//     timeUI = new TimeUI();
//     TimeManager::instance().addObserver(timeUI);
// }

InGameState::InGameState(std::shared_ptr<Game> game) : LevelState(game)
{
    scoreUI = new ScoreUI();
    ScoreManager::instance().addObserver(scoreUI);

    levelUI = new LevelUI();
    LevelManager::instance().addObserver(levelUI);

    coinUI = new CoinUI();
    CoinManager::instance().addObserver(coinUI);

    timeUI = new TimeUI();
    TimeManager::instance().addObserver(timeUI);
    uiRoot = nullptr;
    setupButton();
}

void InGameState::setupButton()
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
    // assert(LevelManager::instance().getLevel() != 0);

    // create Dummy uiROot
    auto dummydrawElement = std::make_shared<DrawableElement>();
    auto dummyInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), dummydrawElement);
    std::shared_ptr<UIContainer> dummyContainer = std::make_shared<UIContainer>(dummyInteractUI);
    dummyContainer->setActive(true);
    // ========Create Pause panel and assign it to root=================
    auto PauseShape = std::make_shared<RoundedRectangleShape>(panelSize, 20.f);
    PauseShape->setPosition(panelPos);
    PauseShape->setFillColor(mainBtnColor.normal);

    auto pauseDE = std::make_shared<DrawableElement>(PauseShape);

    Interact PauseInter(StateColor(mainBtnColor.normal, mainBtnColor.normal), /*toggle=*/true);
    PauseInter.setActive(false);
    auto pauseIU = std::make_shared<InteractUI>(PauseInter, pauseDE);

    auto pausePanel = std::make_shared<Panel>(pauseIU);

    pausePanel->setActiveKey(sf::Keyboard::Z); // press Z to open pause

    dummyContainer->addComponent(pausePanel);

    //==========Create Pause Text======================
    auto PauseMessage = makeTextUtil("Pausing", sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 6),
                                     40, textColorSetting, /*setCenter=*/true);
    pausePanel->addComponent(PauseMessage);

    // ==== set up constant in pause
    std::vector<sf::Vector2f> offsetList = {
        sf::Vector2f(-100.f, 0.f),
        sf::Vector2f(100.f, 0.f),
        sf::Vector2f(-100.f, 50.f),
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(0.f, 100.f),
        sf::Vector2f(-50.f, -80.f),
        sf::Vector2f(0.f, -90.f),
        sf::Vector2f(50.f, -87.f)};
    sf::Vector2f centerPos = sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 2);

    // // ========================== Setting Panel =====================================
    // // Create Settings Panel
    // auto& keybinding = KeyBinding::Instance();
    // auto settingsPanelShape = std::make_shared<RoundedRectangleShape>(panelSize, 20.f);
    // settingsPanelShape->setPosition(panelPos);
    // settingsPanelShape->setFillColor(mainBtnColor.normal);

    // auto settingsDE = std::make_shared<DrawableElement>(settingsPanelShape);

    // Interact settingsInter(StateColor(mainBtnColor.normal, mainBtnColor.normal), /*toggle=*/true);
    // settingsInter.setActive(false);
    // auto settingsIU = std::make_shared<InteractUI>(settingsInter, settingsDE);

    // auto settingsPanel = std::make_shared<Panel>(settingsIU);

    // // settingComponent = settingsPanel;

    // ========== Close button in settingsPanel =================================

    // std::shared_ptr<sf::Sprite> turnbackSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::turnback));
    // auto homeBtn = makeButtonUtil(
    //     sf::Vector2f(40.f, 40.f),
    //     std::make_shared<sf::CircleShape>(30.f),
    //     "",
    //     backButtonColor,
    //     false,
    //     0,
    //     [settingsPanel]() {
    //         settingsPanel->setActive(false);
    //     },
    //     turnbackSprite
    // );
    // settingsPanel->addComponent(homeBtn);
    pausePanel->addComponent(CommonUIPool::getInstance().get("settingPanel"));

    // // =============Sound button =======================================
    //     auto soundBtn = makeButtonUtil(
    //     panelPos + sf::Vector2f(panelSize.x - 120.f, 30.f),
    //     std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
    //     "",
    //     soundButtonColor,
    //     true,
    //     0,
    //     []() {
    //         SOUND::shouldPlayMusic = !SOUND::shouldPlayMusic;
    //      },
    //     std::make_shared<sf::Sprite>(texholder.get(TexType::sound))
    // );
    // soundBtn->setActive(SOUND::shouldPlayMusic);
    // // soundBtn->setFunc([soundBtn, this]() {
    // //     static bool soundOn = false;
    // //     if (soundOn) soundBtn->setSprite(spritePool[TexType::soundOn]);
    // //     else soundBtn->setSprite(spritePool[TexType::soundOff]);
    // //     soundOn = !soundOn;
    // // });
    // settingsPanel->addComponent(soundBtn);
    // //============Music Button========================
    //     auto musicBtn = makeButtonUtil(
    //     panelPos + sf::Vector2f(panelSize.x - 120.f, 140.f),
    //     std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
    //     "",
    //     soundButtonColor,
    //     true,
    //     0,
    //     [settingsPanel]() { },
    //     std::make_shared<sf::Sprite>(texholder.get(TexType::music))
    // );
    // settingsPanel->addComponent(musicBtn);
    // //==========================
    // //  setFunc for setting panel so that  sound and music is set to correct state
    // // settingsPanel->setFunc([musicBtn, soundBtn](){
    // //     musicBtn->setActive(SOUND::shouldPlayMusic);
    // //     soundBtn->setActive(SOUND::shouldPlayMusic);
    // // });

    // // Create Move Up button
    // auto moveUpShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    // auto moveUpBtn = makeButtonUtil(
    //     moveUpPos,
    //     std::static_pointer_cast<sf::Shape>(moveUpShape),
    //     keyToString(keybinding.getKey(KeyBinding::Action::MoveUp)),
    //     keybuttonColor,
    //     true,
    //     charSize,
    //     [this]() {
    //         std::cout << "Move Up button clicked!" << std::endl;
    //     },
    //     nullptr, sf::Color::Black
    // );
    // auto moveUpMessage = makeTextUtil("Jump", moveUpPos + sf::Vector2f(150.f,15.f),
    //                         charSize, textColorSetting);

    // // Create Move right button
    // auto moveRightShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    // auto moveRightBtn = makeButtonUtil(
    //     moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset),
    //     std::static_pointer_cast<sf::Shape>(moveRightShape),
    //     keyToString(keybinding.getKey(KeyBinding::Action::MoveRight)),
    //     keybuttonColor,
    //     true,
    //     charSize,
    //     [this]() {
    //         std::cout << "Move Down button clicked!" << std::endl;
    //     },
    //     nullptr, sf::Color::Black
    // );
    // auto moveRightMessage = makeTextUtil("Move right", moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset) + sf::Vector2f(150.f,15.f),
    //                         charSize, textColorSetting);

    // // Create Move Left button
    // auto moveLeftShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    // auto moveLeftBtn = makeButtonUtil(
    //     moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset),
    //     std::static_pointer_cast<sf::Shape>(moveLeftShape),
    //     keyToString(keybinding.getKey(KeyBinding::Action::MoveLeft)),
    //     keybuttonColor,
    //     true,
    //     charSize,
    //     [this]() {
    //         std::cout << "Move Left button clicked!" << std::endl;
    //     },
    //     nullptr, sf::Color::Black
    // );
    // auto moveLeftMessage = makeTextUtil("Move left", moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset) + sf::Vector2f(150.f,15.f),
    //                         charSize, textColorSetting);

    // // ===================shoot button================================
    // auto shootShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    // auto shootBtn = makeButtonUtil(
    //     moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset),
    //     std::static_pointer_cast<sf::Shape>(shootShape),
    //     keyToString(keybinding.getKey(KeyBinding::Action::Shoot)),
    //     keybuttonColor,
    //     true,
    //     charSize,
    //     [this]() {
    //         std::cout << "Shoot button clicked!" << std::endl;
    //     },
    //     nullptr, sf::Color::Black
    // );
    // auto ShootMessage = makeTextUtil("Shoot", moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset) + sf::Vector2f(150.f,15.f),
    //                         charSize, textColorSetting);

    // // Create Move down button
    // auto MoveDownShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    // auto moveDownBtn = makeButtonUtil(
    //     moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset),
    //     std::static_pointer_cast<sf::Shape>(MoveDownShape),
    //     keyToString(keybinding.getKey(KeyBinding::Action::MoveDown)),
    //     keybuttonColor,
    //     true,
    //     charSize,
    //     [this]() {
    //         std::cout << "Move Down button clicked!" << std::endl;
    //     },
    //     nullptr, sf::Color::Black
    // );
    // auto moveDownMessage = makeTextUtil("Move down", moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset) + sf::Vector2f(150.f,15.f),
    //                         charSize, textColorSetting);
    // // create Option Container to wrap 4 button
    // auto optdrawElement = std::make_shared<DrawableElement>();
    // auto optInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), optdrawElement);
    // std::shared_ptr<OptionContainer> keyOptContainer = std::make_shared<OptionContainer>(optInteractUI);
    // keyOptContainer->setActive(true); // always true to display all button

    // keyOptContainer->addComponent(moveUpBtn);
    // keyOptContainer->addComponent(moveDownBtn);
    // keyOptContainer->addComponent(moveLeftBtn);
    // keyOptContainer->addComponent(moveRightBtn);
    // keyOptContainer->addComponent(shootBtn);

    // std::unordered_map<std::shared_ptr<UIComponent>, KeyBinding::Action> ButtonToAction;
    // ButtonToAction[moveUpBtn] = KeyBinding::Action::MoveUp;
    // ButtonToAction[moveDownBtn] = KeyBinding::Action::MoveDown;
    // ButtonToAction[moveLeftBtn] = KeyBinding::Action::MoveLeft;
    // ButtonToAction[moveRightBtn] = KeyBinding::Action::MoveRight;
    // ButtonToAction[shootBtn] = KeyBinding::Action::Shoot;

    // keyOptContainer->setFunc([ButtonToAction, keyOptContainer](const sf::Event& event)
    // {
    //     auto& keybinding = KeyBinding::Instance();
    //     std::shared_ptr<UIComponent> activeButton = keyOptContainer->getActiveComponent();
    //     assert(activeButton);
    //     if (event.type == sf::Event::KeyPressed)
    //     {
    //         sf::Keyboard::Key key = event.key.code;

    //         auto activeAction = ButtonToAction.at(activeButton);
    //         keybinding.setKey(activeAction, key);
    //     }
    //     for (auto& pair: ButtonToAction)
    //     {
    //         std::string content = keyToString(keybinding.getKey(ButtonToAction.at(pair.first)));
    //         pair.first->setText(content);
    //     }
    // });

    // // ==================== KeySetting title===========================
    // auto KeySettingMessage = makeTextUtil("Key Settings", sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 6),
    //                 40, textColorSetting, /*setCenter=*/true);
    // settingsPanel->addComponent(keyOptContainer);

    // settingsPanel->addComponent(moveUpMessage);
    // settingsPanel->addComponent(moveRightMessage);
    // settingsPanel->addComponent(moveLeftMessage);
    // settingsPanel->addComponent(ShootMessage);
    // settingsPanel->addComponent(moveDownMessage);
    // settingsPanel->addComponent(KeySettingMessage);
    // ==========Create Resume Button==================
    auto roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);

    auto resumeBtn = makeButtonUtil(
        centerPos + offsetList[0],
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Resume",
        mainBtnColor,
        false,
        25,
        [pausePanel]()
        {
            MessageBus::publish("GameResumed");
            pausePanel->setActive(false);
        },
        nullptr, sf::Color::White, /*setCenter=*/true);
    pausePanel->addComponent(resumeBtn);

    roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);

    auto settingBtn = makeButtonUtil(
        centerPos + offsetList[1],
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Setting",
        mainBtnColor,
        false,
        25,
        []()
        {
            CommonUIPool::getInstance().get("settingPanel")->setActive(true);
        },
        nullptr, sf::Color::White, /*setCenter=*/true);
    settingBtn->setActive(false);
    pausePanel->addComponent(settingBtn);

    roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);

    auto restartBtn = makeButtonUtil(
        centerPos + offsetList[2],
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Restart",
        mainBtnColor,
        false,
        25,
        [this]()
        {
            shouldRestart = true;
        },
        nullptr, sf::Color::White, /*setCenter=*/true);
    pausePanel->addComponent(restartBtn);

    roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);

    auto saveBtn = makeButtonUtil(
        centerPos + offsetList[3],
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Save",
        mainBtnColor,
        false,
        25,
        []()
        {
            MessageBus::publish("GameSaved");
        },
        nullptr, sf::Color::White, /*setCenter=*/true);
    pausePanel->addComponent(saveBtn);

    std::cout << "433 ok \n";

    roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);

    auto exitBtn = makeButtonUtil(
        centerPos + offsetList[4],
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Exit",
        mainBtnColor,
        false,
        25,
        [this]()
        {
            game->popState();
            game->pushState("menu");
        },
        nullptr, sf::Color::White, /*setCenter=*/true);
    pausePanel->addComponent(exitBtn);
    // ============ mario image =========================

    std::shared_ptr<sf::Sprite> marioSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::marioidling));
    resizeSprite(*marioSprite, sf::Vector2f(50.f, 50.f));
    auto marioImage = helperBuilder::makeSprite(centerPos + offsetList[5], marioSprite, mainBtnColor, /*setCenter=*/true);
    pausePanel->addComponent(marioImage);
    // ============ multiply message =====================
    auto MultiplyMessage = makeTextUtil("x", centerPos + offsetList[6],
                                        30, textColorSetting, /*setCenter=*/true);
    pausePanel->addComponent(MultiplyMessage);
    // ============ live num =========================
    auto LiveNumMessage = makeTextUtil("3", centerPos + offsetList[7],
                                       30, textColorSetting, /*setCenter=*/true);
    pausePanel->addComponent(LiveNumMessage);
    // LiveNum = LiveNumMessage;
    // std::cout << "make button again " << std::endl;
    MessageBus::subscribe("LiveNum", LiveNumMessage.get(), [LiveNumMessage](const std::string& a){
        LiveNumMessage->setText(a);
    });

    // =============== DeathPanel=======================
    auto Deathrect = std::make_shared<sf::RectangleShape>(sf::Vector2f(UIConstant::ws.x, UIConstant::ws.y));
    Deathrect->setFillColor(sf::Color(34, 34, 34));
    auto DeathPanelDE = std::make_shared<DrawableElement>(Deathrect);
    Interact Deathpanelinteract(StateColor(sf::Color(34, 34, 34), sf::Color(34, 34, 34)));

    auto DeathIU = std::make_shared<InteractUI>(Deathpanelinteract, DeathPanelDE);
    std::shared_ptr<Panel> DeathPanel = std::make_shared<Panel>(DeathIU);
    DeathPanel->setActiveKey(sf::Keyboard::X);
    dummyContainer->addComponent(DeathPanel);

    // ================Time up Panel====================
    auto TimeUprect = std::make_shared<sf::RectangleShape>(sf::Vector2f(UIConstant::ws.x, UIConstant::ws.y));
    TimeUprect->setFillColor(sf::Color(34, 34, 34));
    auto TimeUpPanelDE = std::make_shared<DrawableElement>(TimeUprect);
    Interact panelinteract(StateColor(sf::Color(34, 34, 34), sf::Color(34, 34, 34)));

    auto TimeUpIU = std::make_shared<InteractUI>(panelinteract, TimeUpPanelDE);
    auto TimeUpPanel = std::make_shared<Panel>(TimeUpIU);
    TimeUpPanel->setActiveKey(sf::Keyboard::C);
    dummyContainer->addComponent(TimeUpPanel);

    // =========== Game Over =======================
    auto gameOverText = helperBuilder::makeText("Game Over",
                                                sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 3),
                                                40, UIFont, StateColor(sf::Color::White, sf::Color::White, sf::Color(255, 49, 49), sf::Color::White), true);
    // ============== TimeUp =========================
    auto timeUpText = helperBuilder::makeText("Time Up",
                                              sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 3),
                                              40, UIFont, StateColor(sf::Color::White, sf::Color::White, sf::Color(255, 49, 49), sf::Color::White), true);

    // ===============Restart Button===================
    auto restartBtnDeath = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.5), // Vị trí Restart
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Restart",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        25,
        [this, DeathPanel]()
        {
            shouldRestart = true;
            DeathPanel->setActive(false);
        },
        nullptr, sf::Color::White, true);

    auto restartBtnTimeUp = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.5), // Vị trí Restart
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Restart",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        25,
        [this, TimeUpPanel]()
        {
            shouldRestart = true;
            TimeUpPanel->setActive(false);
        },
        nullptr, sf::Color::White, true);
    // ==============Exit button ========================
    auto exitBtnDeath = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.6),
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Exit",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        25,
        [this]()
        {
            this->game->popState();
            this->game->pushState("menu");
        },
        nullptr, sf::Color::White, true);
    auto exitBtnTimeUp = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y * 0.6),
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f),
        "Exit",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        25,
        [this]()
        {
            this->game->popState();
            this->game->pushState("menu");
        },
        nullptr, sf::Color::White, true);
    dummyContainer->addComponent(DeathPanel);
    dummyContainer->addComponent(TimeUpPanel);
    DeathPanel->addComponent(gameOverText);
    DeathPanel->addComponent(restartBtnDeath);
    DeathPanel->addComponent(exitBtnDeath);
    TimeUpPanel->addComponent(timeUpText);
    TimeUpPanel->addComponent(restartBtnTimeUp);
    TimeUpPanel->addComponent(exitBtnTimeUp);

    // ================= Pause button =====================
    auto pauseBtnInGame = makeButtonUtil(
        sf::Vector2f(UIConstant::ws.x - 100.f, 100.f),
        std::make_shared<sf::CircleShape>(35.f),
        "",
        StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
        false,
        0,
        [this, pausePanel]()
        {
            MessageBus::publish("GamePaused");
            pausePanel->setActive(true);
        },
        std::make_shared<sf::Sprite>(texholder.get(TexType::pause)), sf::Color::White, true);
    dummyContainer->addComponent(pauseBtnInGame);

    uiRoot = dummyContainer;
    dummyContainer->setActive(true);
}

void InGameState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
    MessageBus::publish("LiveNum", std::to_string(gameManager->getLives()));
}

std::shared_ptr<LevelState> InGameState::getNewState(GameManager *gameManager)
{
    if (LevelManager::instance().getStatus() == std::string("win"))
    {
        gameManager->setLives(gameManager->getLives() + 1);
        return std::make_shared<GameWinState>(game);
    }

    if (LevelManager::instance().getStatus() == std::string("timeup"))
        return std::make_shared<TimeUpState>(game);

    if (LevelManager::instance().getStatus() == std::string("intro"))
    {
        if (GameManager::getLives() <= 1)
        {
            // std::cout << "Game Over! Returning to main menu." << std::endl;
            gameManager->setLives(4);
            return std::make_shared<GameOverState>(game);
        }
        LevelManager::instance().setSkipUpdate(true);
        // std::cout << "Returning to intro state." << std::endl;
        return std::make_shared<IntroState>(game);
    }

    if (shouldRestart)
    {
        shouldRestart = false;
        LevelManager::instance().setSkipUpdate(true);
        LevelManager::instance().setLevel(LevelManager::instance().getLevel());
        gameManager->setLives(5);
    }
    return nullptr;
}

void InGameState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering InGameState" << std::endl;
    gameManager->draw(window, level);
    scoreUI->draw(window);
    levelUI->draw(window);
    coinUI->draw(window);
    timeUI->draw(window);
    if (uiRoot)
        uiRoot->draw(window);
    
    // LiveNum->draw(window);
}

bool InGameState::shouldReturnToMenu() const
{
    return false;
}