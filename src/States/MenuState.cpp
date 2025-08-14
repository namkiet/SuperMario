#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <iostream>
#include <cassert>
#include <UI/HelperBuilder.hpp>

MenuState::MenuState(std::shared_ptr<Game> game) : GameState(game)
{
    font.loadFromFile("MarioFont.ttf");

    auto& texholder = game->getTexHolder();
    // set up constant
    const auto ws = game->getWindow().getSize();
    // Main button color and settings button
    StateColor mainBtnColor(
        sf::Color(193, 111, 0), // hover
        sf::Color(164, 82, 4) // normal
    );

    StateColor backButtonColor(
        sf::Color(162, 208, 255, 50), // hover
        sf::Color(122, 178, 255, 0)   // normal
    );
    StateColor keybuttonColor(
    sf::Color(255, 165, 0),
    sf::Color(255, 255, 255)
);
    StateColor textColorSetting(sf::Color(255, 255, 255), sf::Color(255, 255, 255));
    StateColor soundButtonColor(sf::Color(255,49,49, 100), sf::Color(255, 255, 255, 50));

    sf::Vector2f playPos((float)ws.x * 0.5f - 220.f * 0.5f, (float)ws.y * 0.5f - 80.f);
    sf::Vector2f btnSize(220.f, 56.f);
    sf::Vector2f panelSize(600.f, 400.f); sf::Vector2f settingPanelSize(450.f, 380.f);
    sf::Vector2f panelPos((ws.x - panelSize.x) * 0.5f, (ws.y - panelSize.y) * 0.5f);

    int characterSize = 20;
    auto& keybinding = KeyBinding::Instance();

    //============== set up constant=========================
    sf::Vector2f moveUpPos = sf::Vector2f(50.f, 30.f) + panelPos;
    float buttonOffset = 60.f;
    sf::Vector2f controlbtnSize = sf::Vector2f(80.f, 50.f);
    int charSize = 20;

    // create lambda function to make button, text... more easily
    auto makeButton =[this](
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
        bool toggle,
        unsigned int textSize,
        std::function<void()> onClick = nullptr,
        std::shared_ptr<sf::Sprite> sprite = nullptr,
        sf::Color textColor = sf::Color::White)
        {
            return helperBuilder::makeButton(pos, shape, label, colors, toggle, textSize,
                        font, onClick, sprite, textColor);
        };
    auto makeText = [this](
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        const StateColor& colorSetting)
        {
            return helperBuilder::makeText(content, pos, charSize, font, colorSetting);
        };

    // === Background Panel (root) ===
    // const auto ws = game->getWindow().getSize();
    std::shared_ptr<sf::Sprite> bgSprite = std::make_shared<sf::Sprite>(texholder.get(::TexType::background));
    resizeSprite(*bgSprite, sf::Vector2f((float)ws.x, (float)ws.y));
    bgSprite->setPosition(0.f, 0.f);

    auto bgDE = std::make_shared<DrawableElement>(bgSprite);

    Interact panelInter(StateColor(), /*toggle=*/true);
    panelInter.setActive(true); // root panel always active
    auto panelIU = std::make_shared<InteractUI>(panelInter, bgDE);

    uiRoot = std::make_shared<Panel>(panelIU);
    auto root = std::static_pointer_cast<UIContainer>(uiRoot);


    // ================= Super Mario Title===================
    auto GameStartMessage = makeText("Super Mario Bros", sf::Vector2f(220.f, 100.f),
                    40, textColorSetting);
    root->addComponent(GameStartMessage);
    // ================ quit button============================
    auto quitBtn = makeButton(
        sf::Vector2f((float)ws.x * 0.5f - 220.f * 0.5f, (float)ws.y * 0.5f + 10.f),
        std::make_shared<RoundedRectangleShape>(btnSize, 15.f),
        "Quit", 
        mainBtnColor,
        false,
        25, 
        [this]() {
            this->game->getWindow().close(); 
        }
    );
     root->addComponent(quitBtn);

     
    // ================== Play Panel==========================
    std::shared_ptr<sf::Sprite> pPanelSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::playPanel));
    resizeSprite(*pPanelSprite, panelSize);
    pPanelSprite->setPosition(panelPos);
    auto playPanelDE = std::make_shared<DrawableElement>(pPanelSprite);
    Interact playPanelInter(StateColor(), /*toggle=*/true);
    playPanelInter.setActive(false); // initially hidden
    auto playPanelIU = std::make_shared<InteractUI>(playPanelInter, playPanelDE);
    auto playPanel = std::make_shared<Panel>(playPanelIU);
    // =================== Play button =======================
    auto roundedRectShape = std::make_shared<RoundedRectangleShape>(btnSize, 15.f);

    auto playBtn = makeButton(
        playPos,
        std::static_pointer_cast<sf::Shape>(roundedRectShape),
        "Play",
        mainBtnColor,
        true, 
        25,
        [playPanel]() {
            playPanel->setActive(true);
        }
    );
    root->addComponent(playBtn);
    root->addComponent(playPanel);

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
    
    // ======================= Settings button============================
    auto settingsPos = sf::Vector2f((float)ws.x * 0.5f - 220.f * 0.5f, (float)ws.y * 0.5f + 100.f);

    auto settingroundedRectShape = std::make_shared<RoundedRectangleShape>(sf::Vector2f(220.f, 56.f), 20.f); 

    auto settingsBtn = makeButton(
        settingsPos,
        std::static_pointer_cast<sf::Shape>(settingroundedRectShape),
        "Settings",
        mainBtnColor,
        true,
        25,
        [settingsPanel]() { settingsPanel->setActive(true); }
    );

    root->addComponent(settingsBtn);
    root->addComponent(settingsPanel);


    // ========== Close button in settingsPanel =================================

    std::shared_ptr<sf::Sprite> turnbackSprite = std::make_shared<sf::Sprite>(texholder.get(TexType::turnback));
    auto homeBtn = makeButton(
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
        auto soundBtn = makeButton(
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
        auto musicBtn = makeButton(
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
    //============Save Button========================
        auto saveBtn = makeButton(
        panelPos + sf::Vector2f(panelSize.x - 120.f, 250.f), 
        std::make_shared<RoundedRectangleShape>(sf::Vector2f(70.f, 70.f), 10.f),
        "",
        soundButtonColor,
        true,
        0,
        [settingsPanel]() { },
        std::make_shared<sf::Sprite>(texholder.get(TexType::save))
    );
    settingsPanel->addComponent(saveBtn);
    //==========================

    // Create Move Up button
    auto moveUpShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveUpBtn = makeButton(
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
    auto moveUpMessage = makeText("Jump", moveUpPos + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);

    // Create Move right button
    auto moveRightShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveRightBtn = makeButton(
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
    auto moveRightMessage = makeText("Move right", moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);


    // Create Move Left button
    auto moveLeftShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveLeftBtn = makeButton(
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
    auto moveLeftMessage = makeText("Move left", moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);



    // ===================shoot button================================
    auto shootShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto shootBtn = makeButton(
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
    auto ShootMessage = makeText("Shoot", moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);
    
    // Create Move down button
    auto MoveDownShape = std::make_shared<RoundedRectangleShape>(controlbtnSize, 15.f);
    auto moveDownBtn = makeButton(
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
    auto moveDownMessage = makeText("Move down", moveUpPos + sf::Vector2f(0.f, 4 * buttonOffset) + sf::Vector2f(150.f,15.f),
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

    


    // ==================== KeySetting title===========================
    auto KeySettingMessage = makeText("Key Settings", sf::Vector2f(300.f, 100.f),
                    40, textColorSetting);

    // Add button and text to panel
    // settingsPanel->addComponent(moveUpBtn);
    // settingsPanel->addComponent(moveRightBtn);
    // settingsPanel->addComponent(moveLeftBtn);
    // settingsPanel->addComponent(shootBtn);
    // settingsPanel->addComponent(moveDownBtn);
    settingsPanel->addComponent(keyOptContainer);

    settingsPanel->addComponent(moveUpMessage);
    settingsPanel->addComponent(moveRightMessage);
    settingsPanel->addComponent(moveLeftMessage);
    settingsPanel->addComponent(ShootMessage);
    settingsPanel->addComponent(moveDownMessage);
    settingsPanel->addComponent(KeySettingMessage);
        
    // =============== playHomeButton ==============================

    auto playhomeBtn = makeButton(
        sf::Vector2f(40.f, 40.f), 
        std::make_shared<sf::CircleShape>(30.f),
        "",
        backButtonColor,
        false,
        0,
        [playPanel, playBtn]() { 
            playPanel->setActive(false);
            playBtn->setHover(false);
            playBtn->setActive(false);
        },
        std::make_shared<sf::Sprite>(texholder.get(TexType::turnback))
    );
    playPanel->addComponent(playhomeBtn);
        // ============== Level Buttons ===============
    std::vector<std::string> levelNames = {"Level 1", "Level 2", "Level 3", "Level 4"};
    for (int i = 0; i < 4; ++i) {
        auto levelBtn = makeButton(
            sf::Vector2f(panelPos.x + (panelSize.x - btnSize.x) / 2, panelPos.y + 50.f + i * buttonOffset),
            std::make_shared<RoundedRectangleShape>(btnSize, 15.f),
            levelNames[i],
            mainBtnColor,
            false,
            25,
            [this, i]() {
                if (auto playState = this->game->getRegistry().getState("play")) {
                    std::static_pointer_cast<PlayingState>(playState)->setLevel(i + 1);
                    this->game->pushState("play");
                }
            }
        );
        playPanel->addComponent(levelBtn);
    }
    // =================Create Map title =============================
    auto MapMessage = makeText("Choose Your World", sf::Vector2f(200.f, 100.f),
                    40, textColorSetting);
    playPanel->addComponent(MapMessage);

}


void MenuState::handleEvent(const sf::Event &event) {
    uiRoot->handleEvent(event);
}

void MenuState::update(float dt) {
    // no-op
}

void MenuState::render(sf::RenderWindow &window) {
    uiRoot->draw(window);
}
