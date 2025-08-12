#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <NewUI/Composite1.hpp>
#include <memory>
class MenuState : public GameState
{
private:
    sf::Font font;
    sf::Text playText;
    std::shared_ptr<sf::Texture> bgTex_;
    std::shared_ptr<sf::Texture> settingsTex_;
    
    std::shared_ptr<Panel> menuPanel_;
    std::shared_ptr<Button> playBtn_;
    std::shared_ptr<Button> quitBtn_;

    std::shared_ptr<UIComponent> uiRoot;
public:
    MenuState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf:: RenderWindow&window) override;
};