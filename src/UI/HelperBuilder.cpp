#include "UI/HelperBuilder.hpp"

namespace helperBuilder
{
    std::shared_ptr<Button> makeButton(
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
        bool toggle,
        unsigned int textSize,
        sf::Font& font,
        std::function<void()> onClick,
        std::shared_ptr<sf::Sprite> sprite,
        sf::Color textColor,
        bool setCenter
    )
    {
        if (setCenter) {
            sf::FloatRect shapeBounds = shape->getGlobalBounds();
            shape->setPosition(
                pos.x - shapeBounds.width / 2,
                pos.y - shapeBounds.height / 2
            );
        } else {
            shape->setPosition(pos);
        }

        shape->setFillColor(colors.normal);

        auto de = std::make_shared<DrawableElement>(shape);
        if (sprite) {
            de->setSprite(sprite);
        }
        sf::Text t;
        t.setFont(font);
        t.setString(label);
        t.setCharacterSize(textSize);
        t.setFillColor(textColor);
        auto tb = t.getLocalBounds();
        sf::Vector2f size = sf::Vector2f(shape->getGlobalBounds().width, shape->getGlobalBounds().height);
        t.setPosition(
            shape->getPosition().x + (size.x - tb.width) * 0.5f - tb.left,
            shape->getPosition().y + (size.y - tb.height) * 0.5f - tb.top
        );
        de->setText(t);

        Interact inter(colors, toggle);
        auto iu = std::make_shared<InteractUI>(inter, de);

        auto btn = std::make_shared<Button>(iu);
        btn->setFunc(std::move(onClick));
        return btn;
    }

    std::shared_ptr<StaticComponent> makeText(
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        sf::Font& font,
        const StateColor& colorSetting,
        bool setCenter
    )
    {
        Interact inter(colorSetting);
        inter.setCanActive(false);
        inter.setCanHover(false);

        sf::Text txt;
        txt.setFont(font);
        txt.setCharacterSize(charSize);
        txt.setFillColor(colorSetting.normalText);
        txt.setString(content);

        if (setCenter)
        {
            sf::FloatRect textBounds = txt.getLocalBounds();
            txt.setOrigin(textBounds.width / 2, textBounds.height / 2);
            txt.setPosition(pos);
        }

        DrawableElement drawEle;
        drawEle.setText(txt);

        InteractUI interactui(inter, std::make_shared<DrawableElement>(drawEle));
        interactui.setTextPos(pos);

        return std::make_shared<StaticComponent>(std::make_shared<InteractUI>(interactui));
    }
    std::shared_ptr<StaticComponent> makeSprite(
    sf::Vector2f pos,
    std::shared_ptr<sf::Sprite> sprite,
    const StateColor& colorSetting,
    bool setCenter
    )
    {
        Interact inter(colorSetting);
        inter.setCanActive(false);
        inter.setCanHover(false);

        if (setCenter)
        {
            sf::FloatRect spriteBounds = sprite->getLocalBounds();
            sprite->setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
        }


        sprite->setPosition(pos);

        auto de = std::make_shared<DrawableElement>(sprite);

        InteractUI interactui(inter, de);
        // interactui.setSpritePos(pos);

        return std::make_shared<StaticComponent>(std::make_shared<InteractUI>(interactui));
    }

    std::shared_ptr<StaticComponent> makeRectShape(
        sf::Vector2f pos,
        sf::Vector2f size,  // Kích thước (Width, Height hoặc Radius nếu là Circle)
        sf::Color color,
        bool setCenter
    )
    {
        // Tạo một hình chữ nhật (hoặc có thể thay đổi để hỗ trợ nhiều loại shape khác)
        sf::RectangleShape shape(size); // Sử dụng sf::RectangleShape ở đây, có thể thay đổi thành sf::CircleShape nếu cần
        
        // Nếu setCenter là true, căn giữa shape tại pos
        if (setCenter)
        {
            shape.setOrigin(size.x / 2, size.y / 2); // Căn giữa hình chữ nhật
        }

        // Đặt màu sắc cho shape
        shape.setFillColor(color);

        // Đặt vị trí của shape
        shape.setPosition(pos);

        // Tạo Interact với canActive và canHover là false
        Interact inter(StateColor(), /*toggle=*/false);
        inter.setCanActive(false);  // Không thể kích hoạt (click)
        inter.setCanHover(false);   // Không thể hover (di chuột qua)

        // Tạo DrawableElement từ shape
        auto de = std::make_shared<DrawableElement>(std::make_shared<sf::RectangleShape>(shape));

        // Tạo InteractUI và StaticComponent từ DrawableElement
        InteractUI interactui(inter, de);
        return std::make_shared<StaticComponent>(std::make_shared<InteractUI>(interactui));
    }

    std::shared_ptr<StaticComponent> makeCanActiveText(
        const std::string& content,
        sf::Vector2f pos,
        int charSize,
        sf::Font& font,
        const StateColor& colorSetting,
        bool setCenter
    )
    {
        Interact inter(colorSetting);
        inter.setCanActive(true); 
        inter.setCanHover(false);
        inter.setActive(false);

        sf::Text txt;
        txt.setFont(font);
        txt.setCharacterSize(charSize);
        txt.setFillColor(colorSetting.normal);
        txt.setString(content);

        if (setCenter)
        {
            sf::FloatRect textBounds = txt.getLocalBounds();
            txt.setOrigin(textBounds.width / 2, textBounds.height / 2);
            txt.setPosition(pos);
        }

        DrawableElement drawEle;
        drawEle.setText(txt);

        InteractUI interactui(inter, std::make_shared<DrawableElement>(drawEle));
        // interactui.setTextPos(pos);

        return std::make_shared<StaticComponent>(std::make_shared<InteractUI>(interactui));
    }

}

