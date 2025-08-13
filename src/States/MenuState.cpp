#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <iostream>

MenuState::MenuState(std::shared_ptr<Game> game) : GameState(game)
{
    font.loadFromFile("MarioFont.ttf");

    // === Load textures into texPool ===
    texPool[TexType::background] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::background]->loadFromFile("assets/Background/MenuBackground.png")) {
        std::cout << "Cannot load menu background\n";
        assert(false);
    }
    texPool[TexType::close] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::close]->loadFromFile("assets/UI/close.png")) {
        std::cout << "Cannot load close button image\n";
        assert(false);
    }

    texPool[TexType::settingpanel] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::settingpanel]->loadFromFile("assets/Background/MenuBackground.png")) {
        std::cout << "Cannot load settings panel background\n";
        assert(false);
    }
    texPool[TexType::home] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::home]->loadFromFile("assets/UI/home.png")) {
        std::cout << "Cannot load home button image\n";
        assert(false);
    }
    texPool[TexType::soundOn] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::soundOn]->loadFromFile("assets/UI/soundOn.png")) {
        std::cout << "Cannot load sound on button image\n";
        assert(false);
    }
    texPool[TexType::soundOff] = std::make_shared<sf::Texture>();
    if (!texPool[TexType::soundOff]->loadFromFile("assets/UI/soundOff.png")) {
        std::cout << "Cannot load sound ff button image\n";
        assert(false);
    }
    texPool[TexType::playPanel]= std::make_shared<sf::Texture>();
    if (!texPool[TexType::playPanel]->loadFromFile("assets/Background/MenuBackground.png")) {
        std::cout << "Cannot load panel background\n";
        assert(false);
    }

    // === Create sprites from textures ===
    std::shared_ptr<sf::Sprite> backgroundSprite = std::make_shared<sf::Sprite>(*texPool[TexType::background]);
    std::shared_ptr<sf::Sprite> closeSprite = std::make_shared<sf::Sprite>(*texPool[TexType::close]);
    std::shared_ptr<sf::Sprite> settingPanelSprite = std::make_shared<sf::Sprite>(*texPool[TexType::settingpanel]);
    std::shared_ptr<sf::Sprite> homeSprite = std::make_shared<sf::Sprite>(*texPool[TexType::home]);
    std::shared_ptr<sf::Sprite> soundOnSprite = std::make_shared<sf::Sprite>(*texPool[TexType::soundOn]);
    std::shared_ptr<sf::Sprite> soundOffSprite = std::make_shared<sf::Sprite>(*texPool[TexType::soundOff]);
    std::shared_ptr<sf::Sprite> playPanelSprite = std::make_shared<sf::Sprite>(*texPool[TexType::playPanel]);
    // === Background Panel (root) ===
    const auto ws = game->getWindow().getSize();
    resizeSprite(*backgroundSprite, sf::Vector2f((float)ws.x, (float)ws.y));
    backgroundSprite->setPosition(0.f, 0.f);

    auto bgDE = std::make_shared<DrawableElement>(backgroundSprite);

    Interact panelInter(StateColor(), /*toggle=*/true);
    panelInter.setActive(true); // root panel always active
    auto panelIU = std::make_shared<InteractUI>(panelInter, bgDE);

    uiRoot = std::make_shared<Panel>(panelIU);
    auto root = std::static_pointer_cast<UIContainer>(uiRoot);

    // helper func to make button
     auto makeButton = [&](sf::Vector2f pos,
                            std::shared_ptr<sf::Shape> shape,
                          const std::string& label,
                          const StateColor& colors, 
                          bool toggle,
                            unsigned int textSize,
                          std::function<void()> onClick = nullptr,
                          std::shared_ptr<sf::Sprite> sprite = nullptr) -> std::shared_ptr<Button>
    {
        shape->setPosition(pos);
        shape->setFillColor(colors.normal);

        auto de = std::make_shared<DrawableElement>(shape);
        if (sprite) {
            de->setSprite(sprite);
        }
        sf::Text t;
        t.setFont(font);
        t.setString(label);
        t.setCharacterSize(textSize);
        t.setFillColor(sf::Color::White);
        auto tb = t.getLocalBounds();
        sf::Vector2f size = sf::Vector2f(shape->getGlobalBounds().width, shape->getGlobalBounds().height);
        t.setPosition(
            pos.x + (size.x - tb.width) * 0.5f - tb.left,
            pos.y + (size.y - tb.height) * 0.5f - tb.top
        );
        de->setText(t);

        Interact inter(colors, toggle);
        auto iu = std::make_shared<InteractUI>(inter, de);

        auto btn = std::make_shared<Button>(iu);
        btn->setFunc(std::move(onClick));
        return btn;
    };

auto makeText = [&](std::string content, sf::Vector2f pos, int charSize, const StateColor& colorSetting)
{
    Interact inter(colorSetting);
    inter.setCanActive(false);
    inter.setCanHover(false);  

    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(charSize);
    txt.setFillColor(sf::Color::White);
    txt.setString(content); 

    DrawableElement drawEle;
    drawEle.setText(txt);


    InteractUI interactui(inter, std::make_shared<DrawableElement>(drawEle));
    interactui.setTextPos(pos);

    return std::make_shared<TextUIComponent>(std::make_shared<InteractUI>(interactui));
};

    // Main button color and settings button
    StateColor mainBtnColor(
        sf::Color(193, 111, 0), // hover
        sf::Color(164, 82, 4) // normal
    );

    StateColor btnColor1(
        sf::Color(162, 208, 255, 50), // hover
        sf::Color(122, 178, 255, 0)   // normal
    );
    StateColor textColorSetting(sf::Color(255, 255, 255), sf::Color(255, 255, 255));


    // =========== Play button =============================
    sf::Vector2f playPos((float)ws.x * 0.5f - 220.f * 0.5f, (float)ws.y * 0.5f - 80.f);
    sf::Vector2f btnSize(220.f, 56.f);
    
    

    // ================= Super Mario Title===================
    auto GameStartMessage = makeText("Super Mario Bros", sf::Vector2f(220.f, 100.f),
                    40, textColorSetting);
    root->addComponent(GameStartMessage);
    // ================ quit button============================
    auto quitRoundedRectShape = std::make_shared<RoundedRectangleShape>(btnSize, 15.f); 

    auto quitBtn = makeButton(
        sf::Vector2f((float)ws.x * 0.5f - 220.f * 0.5f, (float)ws.y * 0.5f + 10.f),
        std::static_pointer_cast<sf::Shape>(quitRoundedRectShape),
        "Quit", 
        mainBtnColor,
        false,
        25, 
        [this]() {
            this->game->getWindow().close(); 
        }
    );
     root->addComponent(quitBtn);

    sf::Vector2f panelSize(600.f, 400.f);
    sf::Vector2f panelPos((ws.x - panelSize.x) * 0.5f, (ws.y - panelSize.y) * 0.5f);
    // ========================== Setting Panel =====================================
    // Create Settings Panel
    
    resizeSprite(*settingPanelSprite, panelSize);
    settingPanelSprite->setPosition(panelPos);

    auto settingsDE = std::make_shared<DrawableElement>(settingPanelSprite);
    Interact settingsInter(StateColor(), /*toggle=*/true);
    settingsInter.setActive(false); // initially hidden
    auto settingsIU = std::make_shared<InteractUI>(settingsInter, settingsDE);
    auto settingsPanel = std::make_shared<Panel>(settingsIU);
    
    // ================== Play Panel==========================
    resizeSprite(*playPanelSprite, panelSize);
    playPanelSprite->setPosition(panelPos);

    auto playPanelDE = std::make_shared<DrawableElement>(playPanelSprite);
    Interact playPanelInter(StateColor(), /*toggle=*/true);
    playPanelInter.setActive(false); // initially hidden
    auto playPanelIU = std::make_shared<InteractUI>(playPanelInter, playPanelDE);
    auto playPanel = std::make_shared<Panel>(playPanelIU);

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
            // if (auto playState = this->game->getRegistry().getState("play")) {
            //     std::static_pointer_cast<PlayingState>(playState)->setLevel(1);
            //     this->game->pushState("play");
            // }
            playPanel->setActive(true);
        }
    );
    root->addComponent(playBtn);
    root->addComponent(playPanel);
    root->addComponent(settingsBtn);
    root->addComponent(settingsPanel);

    // ========== Close button in settingsPanel =================================
    auto homeBtn = makeButton(
        sf::Vector2f(40.f, 40.f), 
        std::make_shared<sf::CircleShape>(30.f),
        "",
        btnColor1,
        false,
        0,
        [settingsPanel]() { 
            settingsPanel->setActive(false);
        },
        homeSprite
    );

    // Thêm nút Home vào settingsPanel
    settingsPanel->addComponent(homeBtn);
    // add Sound button 
        auto soundBtn = makeButton(
        panelPos + sf::Vector2f(panelSize.x - 150.f, 70.f), 
        std::make_shared<sf::CircleShape>(50.f),
        "",
        btnColor1,
        false,
        0,
        [settingsPanel]() { },
        soundOnSprite
    );
    soundBtn->setFunc([soundBtn, soundOffSprite, soundOnSprite]() {
        static bool soundOn = false;
        if (soundOn) soundBtn->setSprite(soundOnSprite);
        else soundBtn->setSprite(soundOffSprite);
        soundOn = !soundOn;
    });
    // soundBtn->setSprite(soundOffSprite);
    settingsPanel->addComponent(soundBtn);
    // set up constant
    int characterSize = 20;
    auto& keybinding = KeyBinding::Instance();

    //============== set up constant=========================
    sf::Vector2f moveUpPos = sf::Vector2f(50.f, 30.f) + panelPos;
    float buttonOffset = 80.f;
    sf::Vector2f buttonShape = sf::Vector2f(80.f, 50.f);
    int charSize = 20;

    //==========================
    // Create Move Up button
    auto moveUpShape = std::make_shared<RoundedRectangleShape>(buttonShape, 15.f);  // Bán kính bo góc
    auto moveUpBtn = makeButton(
        moveUpPos, // Đặt nút Move Up ở đầu tiên
        std::static_pointer_cast<sf::Shape>(moveUpShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveUp)),
        mainBtnColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Up button clicked!" << std::endl;
        }
    );
    auto moveUpMessage = makeText("Jump", moveUpPos + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);

    // Create Move Down button
    auto moveRightShape = std::make_shared<RoundedRectangleShape>(buttonShape, 15.f);
    auto moveRightBtn = makeButton(
        moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset), 
        std::static_pointer_cast<sf::Shape>(moveRightShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveRight)),
        mainBtnColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Down button clicked!" << std::endl;
        }
    );
    auto moveRightMessage = makeText("Move right", moveUpPos + sf::Vector2f(0.f, 1 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);


    // Create Move Left button
    auto moveLeftShape = std::make_shared<RoundedRectangleShape>(buttonShape, 15.f);
    auto moveLeftBtn = makeButton(
        moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset),
        std::static_pointer_cast<sf::Shape>(moveLeftShape),
        keyToString(keybinding.getKey(KeyBinding::Action::MoveLeft)),
        mainBtnColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Move Left button clicked!" << std::endl;
        }
    );
    auto moveLeftMessage = makeText("Move left", moveUpPos + sf::Vector2f(0.f, 2 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);



    // Create shoot button
    auto shootShape = std::make_shared<RoundedRectangleShape>(buttonShape, 15.f);
    auto shootBtn = makeButton(
        moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset),
        std::static_pointer_cast<sf::Shape>(shootShape),
        keyToString(keybinding.getKey(KeyBinding::Action::Shoot)),
        mainBtnColor,
        true,
        charSize,
        [this]() { 
            std::cout << "Shoot button clicked!" << std::endl;
        }
    );
    auto ShootMessage = makeText("Shoot", moveUpPos + sf::Vector2f(0.f, 3 * buttonOffset) + sf::Vector2f(150.f,15.f),
                            charSize, textColorSetting);

    // Create KeySetting title
    auto KeySettingMessage = makeText("Key Settings", sf::Vector2f(300.f, 100.f),
                    40, textColorSetting);

    // Add button and text to panel
    settingsPanel->addComponent(moveUpBtn);
    settingsPanel->addComponent(moveRightBtn);
    settingsPanel->addComponent(moveLeftBtn);
    settingsPanel->addComponent(shootBtn);
    settingsPanel->addComponent(moveUpMessage);
    settingsPanel->addComponent(moveRightMessage);
    settingsPanel->addComponent(moveLeftMessage);
    settingsPanel->addComponent(ShootMessage);
    settingsPanel->addComponent(KeySettingMessage);
        

    // Connect button to buttonContainer in order to manage keyBinding
    buttonContainer.add(moveUpBtn, KeyBinding::Action::MoveUp);
    buttonContainer.add(moveRightBtn, KeyBinding::Action::MoveRight);
    buttonContainer.add(moveLeftBtn, KeyBinding::Action::MoveLeft);
    buttonContainer.add(shootBtn, KeyBinding::Action::Shoot);


    auto playhomeBtn = makeButton(
        sf::Vector2f(40.f, 40.f), 
        std::make_shared<sf::CircleShape>(30.f),
        "",
        btnColor1,
        false,
        0,
        [playPanel]() { 
            playPanel->setActive(false);
        },
        homeSprite
    );
        // === Level Buttons ===
    buttonShape = sf::Vector2f(220.f, 56.f);

    std::vector<std::string> levelNames = {"Level 1", "Level 2", "Level 3", "Level 4"};
    for (int i = 0; i < 4; ++i) {
        auto roundedRectShape = std::make_shared<RoundedRectangleShape>(buttonShape, 15.f);
        auto levelBtn = makeButton(
            sf::Vector2f(panelPos.x + (panelSize.x - buttonShape.x) / 2, panelPos.y + 50.f + i * buttonOffset),
            std::static_pointer_cast<sf::Shape>(roundedRectShape),
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
    // Create Map title
    auto MapMessage = makeText("Choose Your World", sf::Vector2f(200.f, 100.f),
                    40, textColorSetting);

    // add home button
    playPanel->addComponent(MapMessage);
    playPanel->addComponent(playhomeBtn);
}

void MenuState::handleEvent(const sf::Event &event) {
    uiRoot->handleEvent(event);
    buttonContainer.handleEvent(event);
}

void MenuState::update(float dt) {
    // no-op
}

void MenuState::render(sf::RenderWindow &window) {
    uiRoot->draw(window);
}
