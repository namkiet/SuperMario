#pragma once
#include <UI/Composite.hpp>
#include <Core/Variables.hpp>
// UIConstant.hpp

#include <SFML/Graphics.hpp>

namespace UIConstant
{
    inline sf::Vector2f ws = SIZE::SCREEN;
    // Main button color and settings button
    inline const StateColor mainBtnColor(
        sf::Color(193, 111, 0), // hover
        sf::Color(164, 82, 4)   // normal
    );

    inline const StateColor backButtonColor(
        sf::Color(162, 208, 255, 50), // hover
        sf::Color(122, 178, 255, 0)   // normal
    );

    inline const StateColor keybuttonColor(
        sf::Color(255, 165, 0),
        sf::Color(255, 255, 255, 50),
        sf::Color::Black, sf::Color::Black); // key button color in setting state

    inline const StateColor textColorSetting(sf::Color(255, 255, 255), sf::Color(255, 255, 255));

    inline const sf::Vector2f btnSize(220.f, 56.f);
    inline const sf::Vector2f panelSize(531.f, 450.f);
    inline const sf::Vector2f settingPanelSize(520.f, 410.f);
    inline const sf::Vector2f panelPos((ws.x - panelSize.x) * 0.5f, (ws.y - panelSize.y) * 0.7f);

    inline const StateColor soundButtonColor(sf::Color(255, 255, 255, 50), sf::Color(255, 49, 49, 200));                   // colorSetting of sound button
    inline const sf::Vector2f moveUpPos = sf::Vector2f(panelPos.x + panelSize.x * 0.5f, panelPos.y + panelSize.y * 0.05f); // moveUpPos in setting only
    inline const sf::Vector2f controlbtnSize = sf::Vector2f(56.f, 56.f);                                                   // control btn in setting only
    inline const float buttonOffset = controlbtnSize.y * 1.5f;                                                             // distance between key button in setting only
    inline const int charSize = 30;

    inline const sf::Vector2f pauseButtonShape(200.f, 50.f); // button in pause
};
