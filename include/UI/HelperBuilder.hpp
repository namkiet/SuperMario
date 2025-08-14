#include <UI/Composite.hpp>

// ================== helper func to create UIComponent

namespace helperBuilder
{
std::shared_ptr<Button> makeButton(
        sf::Vector2f pos,
        std::shared_ptr<sf::Shape> shape,
        const std::string& label,
        const StateColor& colors,
        bool toggle,
        unsigned int textSize,
        sf::Font font,
        std::function<void()> onClick = nullptr,
        std::shared_ptr<sf::Sprite> sprite = nullptr,
        sf::Color textColor = sf::Color::White)
{
    shape->setPosition(pos);
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
        pos.x + (size.x - tb.width) * 0.5f - tb.left,
        pos.y + (size.y - tb.height) * 0.5f - tb.top
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
    sf::Font font,
    const StateColor& colorSetting
)
{
    Interact inter(colorSetting);
    inter.setCanActive(false);
    inter.setCanHover(false);

    sf::Text txt;
    txt.setFont(font);
    txt.setCharacterSize(charSize);
    txt.setFillColor(sf::Color::White);
    txt.setString(content);

    DrawableElement drawEle;
    drawEle.setText(txt);

    InteractUI interactui(inter, std::make_shared<DrawableElement>(drawEle));
    interactui.setTextPos(pos);

    return std::make_shared<StaticComponent>(std::make_shared<InteractUI>(interactui));
}

}
