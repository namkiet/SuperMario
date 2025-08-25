// #include <Game.hpp>
// #include <States/MenuState.hpp>
// #include <States/KeySettingState.hpp>
// // #include <UI/KeyBinding.hpp>
// #include <assert.h>
// #include <Engine/Rendering/Utility.hpp>
// // #include <UI/Button.hpp>
// // #include <UI/KeyBinding.hpp>
// #include <iostream>

// KeySettingState::KeySettingState(Game* game): GameState(game)
// {
//         font.loadFromFile("arial.ttf");
//         if (!backgroundTexture.loadFromFile("assets/Background/MenuBackground.png"))
//         {
//             assert(!"Can not load menuBackground");
//         }

//         // Set the texture to the sprite
//         background.setTexture(backgroundTexture);

//         // set background
//         background.setPosition(0.f, 0.f);
//         sf::Vector2u windowSize = game->getWindow().getSize();
//         sf::Vector2f windowSizeF(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
//         resizeSprite(background, windowSizeF);
        
//         // set up constant
//         auto& keybinding = KeyBinding::Instance();
//         StateColor colorSetting;
//         float shapeSize = 60.f;
//         int characterSize = 20;
//         int descSize = 40;
        
//         // set up helper func
//             // add description for button
//         auto addDesc = [&, descSize](std::shared_ptr<sf::Shape> shape, const std::string& desc) {
//             sf::Text txt;
//             txt.setFont(font);
//             txt.setString(desc);
//             txt.setCharacterSize(descSize);
//             txt.setFillColor(sf::Color::Yellow);
//             sf::FloatRect bounds = shape->getGlobalBounds();
//             txt.setPosition(bounds.left + bounds.width + 200.f, bounds.top);
//             textList.push_back(txt);
//         };
//             // add makeRectShape
//         auto makeRectShape = [shapeSize](sf::Vector2f position) {
//             auto rectShape = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
//             setShapeCenter(*rectShape, position);
//             return rectShape;
//         };
//             // add make Text
//         auto makeText = [&, characterSize](KeyBinding::Action action) {
//             sf::Text text;
//             text.setFont(font);
//             text.setString(keyToString(keybinding.getKey(action)));
//             text.setCharacterSize(characterSize);
//             text.setFillColor(sf::Color::White);
//             return text;
//         };

//         // === Move Up ===
//         auto rectShapeUp = makeRectShape( sf::Vector2f(250.f, 150.f) + sf::Vector2f(0, -shapeSize - 10.f));
//         sf::Text upText = makeText(KeyBinding::Action::MoveUp);
//         auto upButton = std::make_shared<Button>(upText, rectShapeUp, colorSetting);
//         upButton->setFunc([]() { std::cout << "Button pressed!\n"; });
//         buttonContainer.add(upButton, KeyBinding::Action::MoveUp);
        
//         // === Move Down ===
//         auto rectShapeDown = makeRectShape(sf::Vector2f(250.f, 150.f) + sf::Vector2f(0, 0.f));
//         sf::Text downText = makeText(KeyBinding::Action::MoveDown);
//         auto downButton = std::make_shared<Button>(downText, rectShapeDown, colorSetting);
//         downButton->setFunc([]() { std::cout << "Move Down pressed!\n"; });
//         buttonContainer.add(downButton, KeyBinding::Action::MoveDown);

//         // === Move Left ===
//         auto rectShapeLeft = makeRectShape(sf::Vector2f(250.f, 150.f) + sf::Vector2f(-shapeSize - 10.f, 0.f));
//         sf::Text leftText = makeText(KeyBinding::Action::MoveLeft);
//         auto leftButton = std::make_shared<Button>(leftText, rectShapeLeft, colorSetting);
//         leftButton->setFunc([]() { std::cout << "Move Left pressed!\n"; });
//         buttonContainer.add(leftButton, KeyBinding::Action::MoveLeft);

//         // === Move Right ===
//         auto rectShapeRight = makeRectShape(sf::Vector2f(250.f, 150.f) + sf::Vector2f(shapeSize + 10.f, 0.f));
//         sf::Text rightText = makeText(KeyBinding::Action::MoveRight);
//         auto rightButton = std::make_shared<Button>(rightText, rectShapeRight, colorSetting);
//         rightButton->setFunc([]() { std::cout << "Move Right pressed!\n"; });
//         buttonContainer.add(rightButton, KeyBinding::Action::MoveRight);

//         // === Sit ===
//         auto rectShapeSit = makeRectShape(sf::Vector2f(250.f, 150.f) + sf::Vector2f(0.f, 140.f));
//         sf::Text sitText = makeText(KeyBinding::Action::Sit);
//         auto sitButton = std::make_shared<Button>(sitText, rectShapeSit, colorSetting);
//         sitButton->setFunc([]() { std::cout << "Sit pressed!\n"; });
//         buttonContainer.add(sitButton, KeyBinding::Action::Sit);


//         // === Shoot ===
//         auto rectShapeShoot = makeRectShape(sf::Vector2f(250.f, 150.f) + sf::Vector2f(0.f, 280.f));
//         sf::Text shootText = makeText(KeyBinding::Action::Shoot);
//         auto shootButton = std::make_shared<Button>(shootText, rectShapeShoot, colorSetting);
//         shootButton->setFunc([]() { std::cout << "Shoot pressed!\n"; });
//         buttonContainer.add(shootButton, KeyBinding::Action::Shoot);

//         // Add description text for Move, Sit, Shoot
//         addDesc(rectShapeDown, "Move");
//         addDesc(rectShapeSit, "Sit");
//         addDesc(rectShapeShoot, "Shoot");

// }

// void KeySettingState::handleEvent(const sf::Event &event)
// {
//     if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//         game->popState();  // return to PlayGameState
//         return;
//     }
//     buttonContainer.handleEvent(event);
    
// }
// void KeySettingState::update(float dt)
// {
    
// }
// void KeySettingState::render(sf::RenderWindow &window)
// {
//     window.draw(background);
//     buttonContainer.draw(window);
//     for (auto& text: textList)
//     {
//         window.draw(text);
//     }
// }