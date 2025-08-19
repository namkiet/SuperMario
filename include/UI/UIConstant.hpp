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
        sf::Color(164, 82, 4) // normal
    );

    inline const StateColor backButtonColor(
        sf::Color(162, 208, 255, 50), // hover
        sf::Color(122, 178, 255, 0)   // normal
    );

    inline const StateColor keybuttonColor(
        sf::Color(255, 165, 0),
        sf::Color(255, 255, 255, 50)
    ); // key button color in setting state

    inline const StateColor textColorSetting(sf::Color(255, 255, 255), sf::Color(255, 255, 255));

    inline const sf::Vector2f btnSize(220.f, 56.f);
    inline const sf::Vector2f panelSize(600.f, 400.f); 
    inline const sf::Vector2f settingPanelSize(450.f, 380.f);
    inline const sf::Vector2f panelPos((ws.x - panelSize.x) * 0.5f, (ws.y - panelSize.y) * 0.5f);


    inline const StateColor soundButtonColor(sf::Color(255, 49, 49, 100), sf::Color(255, 255, 255, 50)); // colorSetting of sound button
    inline const sf::Vector2f moveUpPos = sf::Vector2f(50.f, 30.f) + panelPos; // moveUpPos in setting only
    inline const float buttonOffset = 60.f; // distance between key button in setting only
    inline const sf::Vector2f controlbtnSize = sf::Vector2f(80.f, 50.f); // control btn in setting only
    inline const int charSize = 20;

    inline const sf::Vector2f pauseButtonShape(150.f, 50.f); // button in pause
};
