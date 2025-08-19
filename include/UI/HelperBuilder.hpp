#ifndef HELPERBUILDER_HPP
#define HELPERBUILDER_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>
#include "UI/Composite.hpp"  // Thêm các thư viện liên quan

namespace helperBuilder
{
    // Khai báo hàm makeButton
    std::shared_ptr<Button> makeButton(
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
        bool toggle,
        unsigned int textSize,
        sf::Font& font,
        std::function<void()> onClick = nullptr,
        std::shared_ptr<sf::Sprite> sprite = nullptr,
        sf::Color textColor = sf::Color::White,
        bool setCenter = false
    );

    // Khai báo hàm makeText
    std::shared_ptr<StaticComponent> makeText(
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        sf::Font& font,
        const StateColor& colorSetting,
        bool setCenter = false
    );
    std::shared_ptr<StaticComponent> makeSprite(
        sf::Vector2f pos,
        std::shared_ptr<sf::Sprite> sprite,
        const StateColor& colorSetting,
        bool setCenter = false
    );
    std::shared_ptr<StaticComponent> makeRectShape(
        sf::Vector2f pos,
        sf::Vector2f size,  // Kích thước (Width, Height hoặc Radius nếu là Circle)
        sf::Color color,
        bool setCenter = false
    );
    std::shared_ptr<StaticComponent> makeCanActiveText(
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        sf::Font& font,
        const StateColor& colorSetting,
        bool setCenter = false
    );
}

#endif // HELPERBUILDER_HPP
