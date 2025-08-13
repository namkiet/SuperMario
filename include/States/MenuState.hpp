#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <NewUI/Composite1.hpp>
#include <memory>
#include <unordered_map>
#include <string.h>
#include <UI/ButtonContainer.hpp>
class MenuState : public GameState
{
public:
    enum class TexType
    {
        background,
        close,
        settingpanel,
        home,
        soundOn,
        soundOff,
        playPanel
    };
private:
    sf::Font font;

    std::unordered_map<TexType, std::shared_ptr<sf::Texture>> texPool;
    std::unordered_map<TexType, std::shared_ptr<UIComponent>> UIComponentPool;

    ButtonContainer buttonContainer;

    std::shared_ptr<UIComponent> uiRoot;
public:
    MenuState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf:: RenderWindow&window) override;
// public:
    // std::shared_ptr<sf::Texture> MenuState::loadTexture(const std::string &filePath);
    // void loadTextures();
};