#include <Engine/Rendering/Utility.hpp>

void resizeSprite(sf::Sprite &sprite, const sf::Vector2f &targetSize)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    float scaleX = targetSize.x / bounds.width;
    float scaleY = targetSize.y / bounds.height;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);
}

sf::Text textRender(std::string text, float x, float y, const sf::Font &font, float size)
{
    sf::Text Text;
    Text.setFont(font);
    Text.setString(text);
    Text.setCharacterSize(size);
    Text.setPosition(x, y);
    Text.setFillColor(sf::Color::White);
    return Text;
}
void setShapeCenter(sf::Shape& shape, const sf::Vector2f& position)
{
    // Set the origin of the shape to its center
    shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);

    // Set the position of the shape to the desired center position
    shape.setPosition(position);
}