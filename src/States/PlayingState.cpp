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

PlayingState::PlayingState(std::shared_ptr<Game> game) : GameState(game), gameManager(nullptr)
{
   uiRoot = nullptr;
   
    std::cout << " to playstate constructor ok" << std::endl;
    setupButton();
    std::cout << "playstate constructor ok" << std::endl;
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
        gameManager->handleEvent(event);

    if (uiRoot) uiRoot->handleEvent(event);
}

void PlayingState::update(float dt)
{
    if (LevelManager::instance().getSkipUpdate())
    {
        // std::cout << "newLevel = " << newLevel << std::endl;
        setLevel(LevelManager::instance().getLevel());
        return;
    }
    else if (LevelManager::instance().getShouldLoadNextLevel())
    {
        if (level + 1 > 3)
        {
            game.popState();
            game.pushState("menu");
            return;
        }
        LevelManager::instance().setLevel(level + 1);
        // std::cout << "newLevel = " << newLevel << std::endl;
        setLevel(level + 1);
        return;
    }
    else if (currentLevelState && currentLevelState->shouldReturnToMenu())
    {
        game.popState();
        game.pushState("menu");
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
    if (uiRoot) uiRoot->draw(window);
}

void PlayingState::setupButton()
{
    std::cout << "74 ok \n";

        std::cout << "76 ok \n";
    if (!UIFont.loadFromFile("MarioFont.ttf")) assert(false);
        std::cout << "78 ok \n";
    auto& texholder = game->getTexHolder();
        std::cout << "80 ok \n";

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

        std::cout << "104 ok \n";
    if (level == 4)
    {
        float sameHeightStat = ws.y * 0.9;
        StateColor marionameColorSetting(sf::Color::White, sf::Color::White, sf::Color(153, 153, 153), sf::Color(255, 49, 49)); 
        StateColor luiginameColorSetting(sf::Color::White, sf::Color::White, sf::Color(153, 153, 153), sf::Color(102, 210, 50));
        auto MarioNameMessage = helperBuilder::makeCanActiveText("Mario", sf::Vector2f(ws.x * 0.35, sameHeightStat),
                            30, UIFont, marionameColorSetting, true);

        auto LuigiNameMessage = helperBuilder::makeCanActiveText("Luigi", sf::Vector2f(ws.x * 0.85, sameHeightStat),
                            30, UIFont, luiginameColorSetting, true);

        auto RedMarioBtn = makeButtonUtil(
            sf::Vector2f(ws.x * 0.2, sameHeightStat), 
            std::make_shared<sf::CircleShape>(60.f),
            "",
            StateColor(sf::Color(0,0,0,0), sf::Color(153,153,153, 200)),
            true,
            0,
            [MarioNameMessage]() {
                MarioNameMessage->setActive(true);
            },
            std::make_shared<sf::Sprite>(texholder.get(TexType::mariochoose)),
            sf::Color::White, /*setCenter = */true
            );

        auto GreenMarioBtn = makeButtonUtil(
            sf::Vector2f(ws.x * 0.7, sameHeightStat), 
            std::make_shared<sf::CircleShape>(60.f),
            "",
            StateColor(sf::Color(0,0,0,0), sf::Color(153,153,153, 200)),
            true,
            0,
            [LuigiNameMessage]() {
                LuigiNameMessage->setActive(true);
            },
            std::make_shared<sf::Sprite>(texholder.get(TexType::luigichoose)),
            sf::Color::White, /*setCenter = */true
            );
            std::cout << "145, level = 4 still ok " << std::endl;

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
    else
    {
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
        std::cout << "129 ok \n";

        dummyContainer->addComponent(pausePanel);

        //==========Create Pause Text======================
        auto PauseMessage = makeTextUtil("Pausing", sf::Vector2f(ws.x / 2, ws.y / 6),
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
            sf::Vector2f(50.f, -80.f)
        };
        sf::Vector2f centerPos = sf::Vector2f(ws.x / 2, ws.y / 2);
        
    // ========================== Setting Panel =====================================
    // Create Settings Panel
    auto& keybinding = KeyBinding::Instance();
    auto settingsPanelShape = std::make_shared<RoundedRectangleShape>(panelSize, 20.f);
    settingsPanelShape->setPosition(panelPos);
    settingsPanelShape->setFillColor(mainBtnColor.normal);

    auto settingsDE = std::make_shared<DrawableElement>(settingsPanelShape);


    Interact settingsInter(StateColor(mainBtnColor.normal, mainBtnColor.normal), /*toggle=*/true);
    settingsInter.setActive(false); 
    auto settingsIU = std::make_shared<InteractUI>(settingsInter, settingsDE);

    auto settingsPanel = std::make_shared<Panel>(settingsIU);

    // settingComponent = settingsPanel;

    // ========== Close button in settingsPanel =================================

    std::shared_ptr<sf::Sprite> turnbackSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::turnback));
    auto homeBtn = makeButtonUtil(
        sf::Vector2f(40.f, 40.f), 
        std::make_shared<sf::CircleShape>(30.f),
        "",
        backButtonColor,
        false,
        0,
        [settingsPanel]() { 
            settingsPanel->setActive(false);
        },
        turnbackSprite
    );
    settingsPanel->addComponent(homeBtn);
    pausePanel->addComponent(settingsPanel);

    // =============Sound button =======================================
        auto soundBtn = makeButtonUtil(
        panelPos + sf::Vector2f(panelSize.x - 120.f, 30.f), 
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
        "",
        soundButtonColor,
        true,
        0,
        [settingsPanel]() { },
        std::make_shared<sf::Sprite>(texholder.get(TexType::sound))
    );
    // soundBtn->setFunc([soundBtn, this]() {
    //     static bool soundOn = false;
    //     if (soundOn) soundBtn->setSprite(spritePool[TexType::soundOn]);
    //     else soundBtn->setSprite(spritePool[TexType::soundOff]);
    //     soundOn = !soundOn;
    // });
    settingsPanel->addComponent(soundBtn);
    //============Music Button========================
        auto musicBtn = makeButtonUtil(
        panelPos + sf::Vector2f(panelSize.x - 120.f, 140.f), 
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
        "",
        soundButtonColor,
        true,
        0,
        [settingsPanel]() { },
        std::make_shared<sf::Sprite>(texholder.get(TexType::music))
    );
    settingsPanel->addComponent(musicBtn);
    //==========================

    std::cout << "235 ok \n";
    // Create Move Up button
    auto moveUpShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveUpBtn = makeButtonUtil(
        moveUpPos,
        std::static_pointer_cast<sf::Shape>(moveUpShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveUp)),
        keybuttonColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Up button clicked!" << std::endl;
        },
        nullptr, sf::Color::Black
    );
    auto moveUpMessage = makeTextUtil("Jump", moveUpPos + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);

    // Create Move right button
    auto moveRightShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveRightBtn = makeButtonUtil(
        moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset), 
        std::static_pointer_cast<sf::Shape>(moveRightShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveRight)),
        keybuttonColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Down button clicked!" << std::endl;
        },
        nullptr, sf::Color::Black
    );
    auto moveRightMessage = makeTextUtil("Move right", moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);


    // Create Move Left button
    auto moveLeftShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveLeftBtn = makeButtonUtil(
        moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset),
        std::static_pointer_cast<sf::Shape>(moveLeftShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveLeft)),
        keybuttonColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Left button clicked!" << std::endl;
        },
        nullptr, sf::Color::Black
    );
    auto moveLeftMessage = makeTextUtil("Move left", moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);

std::cout << "288 ok \n";

    // ===================shoot button================================
    auto shootShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto shootBtn = makeButtonUtil(
        moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset),
        std::static_pointer_cast<sf::Shape>(shootShape),
        keyToString(keybinding.getKey(KeyBinding::Action::Shoot)),
        keybuttonColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Shoot button clicked!" << std::endl;
        },
        nullptr, sf::Color::Black
    );
    auto ShootMessage = makeTextUtil("Shoot", moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);
    
    // Create Move down button
    auto MoveDownShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveDownBtn = makeButtonUtil(
        moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset), 
        std::static_pointer_cast<sf::Shape>(MoveDownShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveDown)),
        keybuttonColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Down button clicked!" << std::endl;
        },
        nullptr, sf::Color::Black
    );
    auto moveDownMessage = makeTextUtil("Move down", moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);
    // create Option Container to wrap 4 button
    auto optdrawElement = std::make_shared<DrawableElement>();
    auto optInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), optdrawElement);
    std::shared_ptr<OptionContainer> keyOptContainer = std::make_shared<OptionContainer>(optInteractUI);
    keyOptContainer->setActive(true); // always true to display all button

    keyOptContainer->addComponent(moveUpBtn); 
    keyOptContainer->addComponent(moveDownBtn);
    keyOptContainer->addComponent(moveLeftBtn);
    keyOptContainer->addComponent(moveRightBtn);
    keyOptContainer->addComponent(shootBtn);

    std::unordered_map<std::shared_ptr<UIComponent>, KeyBinding::Action> ButtonToAction;
    ButtonToAction[moveUpBtn] = KeyBinding::Action::MoveUp;
    ButtonToAction[moveDownBtn] = KeyBinding::Action::MoveDown;
    ButtonToAction[moveLeftBtn] = KeyBinding::Action::MoveLeft;
    ButtonToAction[moveRightBtn] = KeyBinding::Action::MoveRight;
    ButtonToAction[shootBtn] = KeyBinding::Action::Shoot;

    keyOptContainer->setFunc([ButtonToAction, keyOptContainer](const sf::Event& event)
    {
        auto& keybinding = KeyBinding::Instance();
        std::shared_ptr<UIComponent> activeButton = keyOptContainer->getActiveComponent();
        assert(activeButton);
        if (event.type == sf::Event::KeyPressed)
        {
            sf::Keyboard::Key key = event.key.code;
            
            auto activeAction = ButtonToAction.at(activeButton);
            keybinding.setKey(activeAction, key);
        }
        for (auto& pair: ButtonToAction)
        {
            std::string content = keyToString(keybinding.getKey(ButtonToAction.at(pair.first)));
            pair.first->setText(content);
        }
    });

    std::cout << "360 ok \n";
    


    // ==================== KeySetting title===========================
    auto KeySettingMessage = makeTextUtil("Key Settings", sf::Vector2f(ws.x / 2, ws.y / 6),
                    40, textColorSetting, /*setCenter=*/true);
    settingsPanel->addComponent(keyOptContainer);

    settingsPanel->addComponent(moveUpMessage);
    settingsPanel->addComponent(moveRightMessage);
    settingsPanel->addComponent(moveLeftMessage);
    settingsPanel->addComponent(ShootMessage);
    settingsPanel->addComponent(moveDownMessage);
    settingsPanel->addComponent(KeySettingMessage);
        // ==========Create Resume Button==================
        auto roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);
        
        auto resumeBtn = makeButtonUtil(
            centerPos + offsetList[0],
            std::static_pointer_cast<sf::Shape>(roundedRectShape),
            "Resume",
            mainBtnColor,
            false, 
            25,
            [pausePanel]() {
                pausePanel->setActive(false);
            },
            nullptr, sf::Color::White, /*setCenter=*/true
        );
        pausePanel->addComponent(resumeBtn);

        roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);
        
        auto settingBtn = makeButtonUtil(
            centerPos + offsetList[1],
            std::static_pointer_cast<sf::Shape>(roundedRectShape),
            "Setting",
            mainBtnColor,
            false, 
            25,
            [settingsPanel]() {
                settingsPanel->setActive(true);
            },
            nullptr, sf::Color::White, /*setCenter=*/true
        );
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
            nullptr,
            nullptr, sf::Color::White, /*setCenter=*/true
        );
        pausePanel->addComponent(restartBtn);
        
        roundedRectShape = std::make_shared<RoundedRectangleShape>(pauseButtonShape, 15.f);
        
        auto saveBtn = makeButtonUtil(
            centerPos + offsetList[3],
            std::static_pointer_cast<sf::Shape>(roundedRectShape),
            "Save",
            mainBtnColor,
            false, 
            25,
            nullptr,
            nullptr, sf::Color::White, /*setCenter=*/true
        );
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
            [this]() { 
                game->popState();
                game->pushState("menu");
            },
            nullptr, sf::Color::White, /*setCenter=*/true
        );
        pausePanel->addComponent(exitBtn);
        // ============ mario image =========================
        
        std::shared_ptr<sf::Sprite> marioSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::marioidling));
        resizeSprite(*marioSprite, sf::Vector2f(50.f, 50.f));
        auto marioImage = helperBuilder::makeSprite(centerPos + offsetList[5], marioSprite, mainBtnColor,/*setCenter=*/true);
        pausePanel->addComponent(marioImage);
        // ============ multiply message =====================
        auto MultiplyMessage = makeTextUtil("x", centerPos + offsetList[6],
                    30, textColorSetting, /*setCenter=*/true);
        pausePanel->addComponent(MultiplyMessage);
        // ============ live num =========================
        auto LiveNumMessage = makeTextUtil("3", centerPos + offsetList[7],
                    30, textColorSetting, /*setCenter=*/true);
        pausePanel->addComponent(LiveNumMessage);
        

        // =============== DeathPanel=======================
        auto Deathrect = std::make_shared<sf::RectangleShape>(sf::Vector2f(ws.x, ws.y));
        Deathrect->setFillColor(sf::Color(34, 34, 34));
        auto DeathPanelDE = std::make_shared<DrawableElement>(Deathrect);
        Interact Deathpanelinteract(StateColor(sf::Color(34,34,34), sf::Color(34,34,34)));
        
        auto DeathIU = std::make_shared<InteractUI>(Deathpanelinteract, DeathPanelDE);
        std::shared_ptr<Panel> DeathPanel = std::make_shared<Panel>(DeathIU);
        DeathPanel->setActiveKey(sf::Keyboard::X);
        dummyContainer->addComponent(DeathPanel);
        
        // ================Time up Panel====================
        auto TimeUprect = std::make_shared<sf::RectangleShape>(sf::Vector2f(ws.x, ws.y));
        TimeUprect->setFillColor(sf::Color(34, 34, 34));
        auto TimeUpPanelDE = std::make_shared<DrawableElement>(TimeUprect);
        Interact panelinteract(StateColor(sf::Color(34,34,34), sf::Color(34,34,34)));
        
        auto TimeUpIU = std::make_shared<InteractUI>(panelinteract, TimeUpPanelDE);
        auto TimeUpPanel = std::make_shared<Panel>(TimeUpIU);
        TimeUpPanel->setActiveKey(sf::Keyboard::C);
        dummyContainer->addComponent(TimeUpPanel);
        
        // =========== Game Over =======================
        auto gameOverText = helperBuilder::makeText("Game Over", 
                                               sf::Vector2f(ws.x / 2, ws.y / 3),
                                               40, UIFont, StateColor(sf::Color::White, sf::Color::White,
                                            sf::Color(255,49, 49), sf::Color::White), true);
        // ============== TimeUp =========================
        auto timeUpText = helperBuilder::makeText("Time Up", 
                                               sf::Vector2f(ws.x / 2, ws.y / 3),
                                               40, UIFont, StateColor(sf::Color::White, sf::Color::White,
                                            sf::Color(255,49, 49), sf::Color::White), true);

        // ===============Restart Button===================
        auto restartBtnDeath = makeButtonUtil(
        sf::Vector2f(ws.x / 2, ws.y * 0.5),  // Vị trí Restart
            std::make_shared<RoundedRectangleShape>(sf::Vector2f(300.f, 50.f), 20.f), 
            "Restart", 
            StateColor(sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 0)),
            false,
            25, 
            [this, DeathPanel]() { 
                // Hàm restart game
                this->game->popState(); 
                this->game->pushState("play");
                DeathPanel->setActive(false);
                
            }, nullptr, sf::Color::White, true
        );
        
        auto restartBtnTimeUp = makeButtonUtil(
        sf::Vector2f(ws.x / 2, ws.y * 0.5),  // Vị trí Restart
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
        // ==============Exit button ========================
            auto exitBtnDeath = makeButtonUtil(
                sf::Vector2f(ws.x / 2, ws.y * 0.6),
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
                auto exitBtnTimeUp = makeButtonUtil(
                sf::Vector2f(ws.x / 2, ws.y * 0.6),
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
        dummyContainer->addComponent(DeathPanel);
        dummyContainer->addComponent(TimeUpPanel);
        DeathPanel->addComponent(gameOverText);
        DeathPanel->addComponent(restartBtnDeath);
        DeathPanel->addComponent(exitBtnDeath);
        TimeUpPanel->addComponent(timeUpText);
        TimeUpPanel->addComponent(restartBtnTimeUp);
        TimeUpPanel->addComponent(exitBtnTimeUp);
        
        uiRoot = dummyContainer;
    }
}

void PlayingState::setLevel(int level)
{
    this->level = level;
    if (gameManager)
        delete gameManager;
    gameManager = new GameManager(level);
    setupButton();

    LevelManager::instance().setSkipUpdate(false);
    LevelManager::instance().setStatus("playing");
    LevelManager::instance().setShouldLoadNextLevel(false);
    
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

void PlayingState::reset()
{
    setLevel(0);
    currentLevelState = std::make_unique<LevelChosenState>();
}