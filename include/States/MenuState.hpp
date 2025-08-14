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
private:
    sf::Font font;

    std::unordered_map<TexType, std::shared_ptr<sf::Texture>> texPool;

    // giu tat ca component
    std::shared_ptr<UIComponent> uiRoot;
public:
    MenuState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf:: RenderWindow&window) override;

};