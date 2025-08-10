#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/KeySettingState.hpp>
#include <UI/KeyBinding.hpp>
#include <assert.h>
#include <Engine/Rendering/Utility.hpp>
#include <UI/Button.hpp>
#include <UI/KeyBinding.hpp>
#include <iostream>

KeySettingState::KeySettingState(std::shared_ptr<Game> game): GameState(game)
{
        font.loadFromFile("arial.ttf");
        if (!backgroundTexture.loadFromFile("assets/Background/MenuBackground.png"))
            {
                assert(!"Can not load menuBackground");
            }

        // Set the texture to the sprite
        background.setTexture(backgroundTexture);

        // set background
        background.setPosition(0.f, 0.f);
        sf::Vector2u windowSize = game->getWindow().getSize();
        sf::Vector2f windowSizeF(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
        resizeSprite(background, windowSizeF);
        

        auto& keybinding = KeyBinding::Instance();
        StateColor colorSetting;
        float shapeSize = 60.f;
        int characterSize = 20;
        // === Move Up ===
        auto circShapeUp = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeUp, sf::Vector2f(250.f, 150.f) + sf::Vector2f(0, -shapeSize - 10.f));

        sf::Text upText;
        upText.setFont(font);
        upText.setString(keyToString(keybinding.getKey(KeyBinding::Action::MoveUp)));
        upText.setCharacterSize(characterSize);
        upText.setFillColor(sf::Color::White);

        auto upButton = std::make_shared<Button>(upText, circShapeUp, colorSetting, true, true);
        upButton->setFunc([]() {
            std::cout << "Button pressed!\n";
        });
        buttonContainer.add(upButton, KeyBinding::Action::MoveUp);
        
        // === Move Down ===
        auto circShapeDown = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeDown, sf::Vector2f(250.f, 150.f) + sf::Vector2f(0, 0.f));

        sf::Text downText;
        downText.setFont(font);
        downText.setString(keyToString(keybinding.getKey(KeyBinding::Action::MoveDown)));
        downText.setCharacterSize(characterSize);
        downText.setFillColor(sf::Color::White);

        auto downButton = std::make_shared<Button>(downText, circShapeDown, colorSetting, true, true);
        downButton->setFunc([]() {
            std::cout << "Move Down pressed!\n";
        });
        buttonContainer.add(downButton, KeyBinding::Action::MoveDown);

        // === Move Left ===
        auto circShapeLeft = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeLeft, sf::Vector2f(250.f, 150.f) + sf::Vector2f(-shapeSize - 10.f, 0.f));

        sf::Text leftText;
        leftText.setFont(font);
        leftText.setString(keyToString(keybinding.getKey(KeyBinding::Action::MoveLeft)));
        leftText.setCharacterSize(characterSize);
        leftText.setFillColor(sf::Color::White);

        auto leftButton = std::make_shared<Button>(leftText, circShapeLeft, colorSetting, true, true);
        leftButton->setFunc([]() {
            std::cout << "Move Left pressed!\n";
        });
        buttonContainer.add(leftButton, KeyBinding::Action::MoveLeft);

        // === Move Right ===
        auto circShapeRight = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeRight, sf::Vector2f(250.f, 150.f) + sf::Vector2f(shapeSize + 10.f, 0.f));

        sf::Text rightText;
        rightText.setFont(font);
        rightText.setString(keyToString(keybinding.getKey(KeyBinding::Action::MoveRight)));
        rightText.setCharacterSize(characterSize);
        rightText.setFillColor(sf::Color::White);

        auto rightButton = std::make_shared<Button>(rightText, circShapeRight, colorSetting, true, true);
        rightButton->setFunc([]() {
            std::cout << "Move Right pressed!\n";
        });
        buttonContainer.add(rightButton, KeyBinding::Action::MoveRight);

        // === Sit ===
        auto circShapeSit = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeSit, sf::Vector2f(250.f, 150.f) + sf::Vector2f(0.f, 140.f));

        sf::Text sitText;
        sitText.setFont(font);
        sitText.setString(keyToString(keybinding.getKey(KeyBinding::Action::Sit)));
        sitText.setCharacterSize(characterSize);
        sitText.setFillColor(sf::Color::White);

        auto sitButton = std::make_shared<Button>(sitText, circShapeSit, colorSetting, true, true);
        sitButton->setFunc([]() {
            std::cout << "Sit pressed!\n";
        });
        buttonContainer.add(sitButton, KeyBinding::Action::Sit);

        // === Shoot ===
        auto circShapeShoot = std::shared_ptr<sf::Shape>(std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeSize, shapeSize)));
        setShapeCenter(*circShapeShoot, sf::Vector2f(250.f, 150.f) + sf::Vector2f(0.f, 280.f));

        sf::Text shootText;
        shootText.setFont(font);
        shootText.setString(keyToString(keybinding.getKey(KeyBinding::Action::Shoot)));
        shootText.setCharacterSize(characterSize);
        shootText.setFillColor(sf::Color::White);

        auto shootButton = std::make_shared<Button>(shootText, circShapeShoot, colorSetting, true, true);
        shootButton->setFunc([]() {
            std::cout << "Shoot pressed!\n";
        });
        buttonContainer.add(shootButton, KeyBinding::Action::Shoot);

}

void KeySettingState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        game->popState();  // return to PlayGameState
        return;
    }
    buttonContainer.handleEvent(event);
    
}
void KeySettingState::update(float dt)
{
    
}
void KeySettingState::render(sf::RenderWindow &window)
{
    window.draw(background);
    buttonContainer.draw(window);

}