#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <iostream>
#include <cassert>
#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>
#include <UI/CommonUIPool.hpp>

MenuState::MenuState(std::shared_ptr<Game> game) : GameState(game)
{
    font.loadFromFile("BalooBhai2-ExtraBold.ttf");

    auto& texholder = game->getTexHolder();
    using namespace UIConstant;
    auto& keybinding = KeyBinding::Instance();
    //============== set up constant=========================


    // create lambda function to make button, text... more easily
    auto makeButtonUtil = [this](
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
                        font, onClick, sprite, textColor, setCenter);
        };
    auto makeTextUtil = [this](
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        const StateColor& colorSetting,
        bool setCenter = false)
        {
            return helperBuilder::makeText(content, pos, charSize, font, colorSetting, setCenter);
        };

    // === Background Panel (root) ===
    // const auto ws = game->getWindow().getSize();
    std::shared_ptr<sf::Sprite> bgSprite = std::make_shared<sf::Sprite>(texholder.get(::TexType::background));
    resizeSprite(*bgSprite, sf::Vector2f((float)UIConstant::ws.x, (float)UIConstant::ws.y));
    bgSprite->setPosition(0.f, 0.f);

    auto bgDE = std::make_shared<DrawableElement>(bgSprite);

    Interact panelInter(StateColor(), /*toggle=*/true);
    panelInter.setActive(true); // root panel always active
    auto panelIU = std::make_shared<InteractUI>(panelInter, bgDE);

    uiRoot = std::make_shared<Panel>(panelIU);
    auto root = std::static_pointer_cast<UIContainer>(uiRoot);


    // ================= Super Mario Title===================
    auto GameStartMessage = makeTextUtil("Super Mario Bros", sf::Vector2f(UIConstant::ws.x / 2,UIConstant::ws.y / 3.5),
                    40, textColorSetting, /*setCenter=*/true);
    root->addComponent(GameStartMessage);
    // ================ quit button============================
    auto quitBtn = makeButtonUtil(
        sf::Vector2f((float)UIConstant::ws.x * 0.5f, (float)UIConstant::ws.y * 0.5f + 190.f),
        std::make_shared<RoundedRectangleShape>(btnSize, 15.f),
        "Quit", 
        mainBtnColor,
        false,
        25, 
        [this]() {
            this->game->getWindow().close(); 
        }
        , nullptr, sf::Color::White, /*setCenter=*/true
    );
     root->addComponent(quitBtn);

     
    // ================== Play Panel==========================
    // std::shared_ptr<sf::Sprite> pPanelSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::playPanel));
    // resizeSprite(*pPanelSprite, panelSize);
    // pPanelSprite->setPosition(panelPos);
    // auto playPanelDE = std::make_shared<DrawableElement>(pPanelSprite);
    // Interact playPanelInter(StateColor(), /*toggle=*/true);
    // playPanelInter.setActive(false); // initially hidden
    // auto playPanelIU = std::make_shared<InteractUI>(playPanelInter, playPanelDE);
    // auto playPanel = std::make_shared<Panel>(playPanelIU);
    // =================== Play button =======================
    auto roundedRectShape = std::make_shared<RoundedRectangleShape>(btnSize, 15.f);
    sf::Vector2f playPos((float)UIConstant::ws.x * 0.5f, (float)UIConstant::ws.y * 0.5f - 80.f);

    auto playBtn = makeButtonUtil(
        playPos,
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Play",
        mainBtnColor,
        false, 
        25,
        [this, game]() {
                auto playState = game->getRegistry().getState("play");
                if (playState)
                {
                    std::static_pointer_cast<PlayingState>(playState)->reset();
                    game->pushState("play");
                }
            }
        , nullptr, sf::Color::White, /*setCenter=*/true
    );
    root->addComponent(playBtn);
    // root->addComponent(playPanel);

    // ========================== Setting Panel =====================================
    // Create Settings Panel
    
    auto settingsPanelShape = std::make_shared<RoundedRectangleShape>(panelSize, 20.f);
    settingsPanelShape->setPosition(panelPos);
    settingsPanelShape->setFillColor(mainBtnColor.normal);

    auto settingsDE = std::make_shared<DrawableElement>(settingsPanelShape);


    Interact settingsInter(StateColor(mainBtnColor.normal, mainBtnColor.normal), /*toggle=*/true);
    settingsInter.setActive(false); 
    auto settingsIU = std::make_shared<InteractUI>(settingsInter, settingsDE);

    auto settingsPanel = std::make_shared<Panel>(settingsIU);

    // settingComponent = settingsPanel;
    
    // ======================= Settings button============================
    auto settingsPos = sf::Vector2f((float)UIConstant::ws.x * 0.5f, (float)UIConstant::ws.y * 0.5f + 100.f);

    auto settingroundedRectShape = std::make_shared<RoundedRectangleShape>(sf::Vector2f(220.f, 56.f), 20.f); 

    auto settingsBtn = makeButtonUtil(
        settingsPos,
        std::static_pointer_cast<sf::Shape>(settingroundedRectShape),
        "Settings",
        mainBtnColor,
        true,
        25,
        [settingsPanel]() { settingsPanel->setActive(true); }
        , nullptr, sf::Color::White, /*setCenter=*/true
    );

    root->addComponent(settingsBtn);
    root->addComponent(settingsPanel);

    // ====================== Load game button=============================
        auto LoadBtn = makeButtonUtil(
        sf::Vector2f((float)UIConstant::ws.x * 0.5f, (float)UIConstant::ws.y * 0.5f + 10.f),
        std::make_shared<RoundedRectangleShape>(btnSize, 15.f),
        "Load", 
        mainBtnColor,
        false,
        25, 
        [this]() {
            std::cout << "Load game" << std::endl;
        }
        , nullptr, sf::Color::White, /*setCenter=*/true
    );
     root->addComponent(LoadBtn);


    // ========== Close button in settingsPanel =================================

    std::shared_ptr<sf::Sprite> turnbackSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::turnback));
    auto homeBtn = makeButtonUtil(
        sf::Vector2f(40.f, 40.f), 
        std::make_shared<sf::CircleShape>(30.f),
        "",
        backButtonColor,
        false,
        0,
        [settingsPanel, settingsBtn]() { 
            settingsPanel->setActive(false);
            settingsBtn->setHover(false);
            settingsBtn->setActive(false);
        },
        turnbackSprite
    );
    settingsPanel->addComponent(homeBtn);

    // =============Sound button =======================================
        auto soundBtn = makeButtonUtil(
        panelPos + sf::Vector2f(panelSize.x - 120.f, 30.f), 
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
        "",
        soundButtonColor,
        true,
        0,
        []() {
            SOUND::shouldPlayMusic = true;
         },
        std::make_shared<sf::Sprite>(texholder.get(TexType::sound))
    );
    soundBtn->setDeactiveFunc([](){
        SOUND::shouldPlayMusic = false;
    });
    soundBtn->setActive(SOUND::shouldPlayMusic);

    settingsPanel->addComponent(soundBtn);
    //============Music Button========================
        auto musicBtn = makeButtonUtil(
        panelPos + sf::Vector2f(panelSize.x - 120.f, 140.f), 
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
        "",
        soundButtonColor,
        true,
        0,
        []() { },
        std::make_shared<sf::Sprite>(texholder.get(TexType::music))
    );
    settingsPanel->addComponent(musicBtn);
    
    // add setting panel to pool for later reference
    CommonUIPool::getInstance().add("settingPanel", settingsPanel);
    
    // //============Save Button========================
    //     auto saveBtn = makeButtonUtil(
    //     panelPos + sf::Vector2f(panelSize.x - 120.f, 250.f), 
    //     std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
    //     "",
    //     soundButtonColor,
    //     true,
    //     0,
    //     [settingsPanel]() { },
    //     std::make_shared<sf::Sprite>(texholder.get(TexType::save))
    // );
    // settingsPanel->addComponent(saveBtn);
    //==========================

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
        std::make_shared<sf::Sprite>(texholder.get(::TexType::keybutton)), sf::Color::Black
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
        std::make_shared<sf::Sprite>(texholder.get(::TexType::keybutton)), sf::Color::Black
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
        std::make_shared<sf::Sprite>(texholder.get(::TexType::keybutton)), sf::Color::Black
    );
    auto moveLeftMessage = makeTextUtil("Move left", moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);



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
        std::make_shared<sf::Sprite>(texholder.get(::TexType::keybutton)), sf::Color::Black
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
        std::make_shared<sf::Sprite>(texholder.get(::TexType::keybutton)), sf::Color::Black
    );
    auto moveDownMessage = makeTextUtil("Move down", moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);
    // create Option Container to wrap 4 button
    auto optdrawElement = std::make_shared<DrawableElement>();
    auto optInteractUI = std::make_shared<InteractUI>(Interact(StateColor()), optdrawElement);
    std::shared_ptr<OptionContainer> keyOptContainer = std::make_shared<OptionContainer>(optInteractUI);
    keyOptContainer->setActive(true); // always true to display all button

    keyOptContainer->addComponent(moveUpBtn); 
    keyOptContainer->addComponent(moveRightBtn);
    keyOptContainer->addComponent(moveLeftBtn);
    keyOptContainer->addComponent(shootBtn);
    keyOptContainer->addComponent(moveDownBtn);

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
            if (key == sf::Keyboard::Unknown) return;
            
            auto activeAction = ButtonToAction.at(activeButton);
            keybinding.setKey(activeAction, key);
        }
        for (auto& pair: ButtonToAction)
        {
            std::string content = keyToString(keybinding.getKey(pair.second));
            pair.first->setText(content);
        }
    });

    


    // ==================== KeySetting title===========================
    auto KeySettingMessage = makeTextUtil("Key Settings", sf::Vector2f(UIConstant::ws.x / 2, UIConstant::ws.y / 6),
                    40, textColorSetting, /*setCenter=*/true);

    // Add button and text to panel

    settingsPanel->addComponent(keyOptContainer);

    settingsPanel->addComponent(moveUpMessage);
    settingsPanel->addComponent(moveRightMessage);
    settingsPanel->addComponent(moveLeftMessage);
    settingsPanel->addComponent(ShootMessage);
    settingsPanel->addComponent(moveDownMessage);
    settingsPanel->addComponent(KeySettingMessage);
        
    // =============== playHomeButton ==============================

    // auto playhomeBtn = makeButtonUtil(
    //     sf::Vector2f(40.f, 40.f), 
    //     std::make_shared<sf::CircleShape>(30.f),
    //     "",
    //     backButtonColor,
    //     false,
    //     0,
    //     [playPanel, playBtn]() { 
    //         playPanel->setActive(false);
    //         playBtn->setHover(false);
    //         playBtn->setActive(false);
    //     },
    //     std::make_shared<sf::Sprite>(texholder.get(TexType::turnback))
    // );
    // playPanel->addComponent(playhomeBtn);
        // ============== Level Buttons ===============
    // std::vector<std::string> levelNames = {"Level 1", "Level 2", "Level 3", "Level 4"};
    // for (int i = 0; i < 4; ++i) {
    //     auto levelBtn = makeButtonUtil(
    //         sf::Vector2f(panelPos.x + (panelSize.x - btnSize.x) / 2, panelPos.y + 50.f + i * buttonOffset),
    //         std::make_shared<RoundedRectangleShape>(btnSize, 15.f),
    //         levelNames[i],
    //         mainBtnColor,
    //         false,
    //         25,
    //         [this, i]() {
    //             if (auto playState = this->game->getRegistry().getState("play")) {
    //                 std::static_pointer_cast<PlayingState>(playState)->setLevel(i + 1);
    //                 this->game->pushState("play");
    //             }
    //         }
    //     );
    //     playPanel->addComponent(levelBtn);
    // }
    // =================Create Map title =============================
    auto MapMessage = makeTextUtil("Choose Your World", sf::Vector2f(200.f, 100.f),
                    40, textColorSetting);
    // playPanel->addComponent(MapMessage);

}


void MenuState::handleEvent(const sf::Event &event) {
    if (uiRoot) uiRoot->handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::S)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                json j;
                std::ifstream fin("save.json");
                fin >> j;
                std::static_pointer_cast<PlayingState>(playState)->setLevel(j["level"], false, true);
                game->pushState("play");
            }
        }
    }
}

void MenuState::update(float dt) {
    // no-op
}

void MenuState::render(sf::RenderWindow &window) {
    uiRoot->draw(window);
}
