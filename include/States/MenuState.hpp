#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <UI/Composite.hpp>
#include <memory>
#include <unordered_map>
#include <string.h>
#include <UI/ButtonContainer.hpp>
#include <UI/TextureHolder.hpp>
class MenuState : public GameState
{
public:
    // enum class TexType
    // {
    //     background,
    //     close,
    //     settingpanel,
    //     home,
    //     soundOn,
    //     soundOff,
    //     playPanel,
    //     sound,
    //     music,
    //     save,
    //     turnback
    // };
private:
    sf::Font font;

    std::unordered_map<TexType, std::shared_ptr<sf::Texture>> texPool;
    // std::unordered_map<TexType, std::shared_ptr<UIComponent>> UIComponentPool;
    // std::unordered_map<TexType, std::shared_ptr<sf::Sprite>> spritePool;
    // co phai la 1-1 mapping khong
    ButtonContainer buttonContainer;

    // giu tat ca component
    std::shared_ptr<UIComponent> uiRoot;
public:
    MenuState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf:: RenderWindow&window) override;
private:
    // void loadTexture(TexType type, const std::string &filePath);
    void drawBackgroundPanel();
    void drawPlayComponent();
    std::shared_ptr<Button> makeButton(
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
        bool toggle,
        unsigned int textSize,
        std::function<void()> onClick = nullptr,
        std::shared_ptr<sf::Sprite> sprite = nullptr,
        sf::Color textColor = sf::Color::White
    );
    std::shared_ptr<StaticComponent> makeText(
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        const StateColor& colorSetting
    );
};