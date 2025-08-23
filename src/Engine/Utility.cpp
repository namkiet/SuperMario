#include <Engine/Rendering/Utility.hpp>
void resizeSprite(sf::Sprite& sprite, const sf::Vector2f &targetSize, bool shouldRepeat)
{
    if (shouldRepeat)
    {
        if (sprite.getTexture())
        {
            const_cast<sf::Texture*>(sprite.getTexture())->setRepeated(true);

            // Tile gốc 16x16, muốn thành 48x48 => scale factor = 3
            int scaleFactor = 3;

            // Vì có scale, textureRect phải nhỏ hơn targetSize
            // => dùng targetSize / scaleFactor
            int texWidth  = static_cast<int>(targetSize.x / scaleFactor);
            int texHeight = static_cast<int>(targetSize.y / scaleFactor);

            sprite.setTextureRect(sf::IntRect(0, 0, texWidth, texHeight));

            // Scale sprite để 16x16 thành 48x48
            sprite.setScale((float)scaleFactor, (float)scaleFactor);
        }
    }
    else
    {
        sf::FloatRect bounds = sprite.getLocalBounds();
        float scaleX = targetSize.x / bounds.width;
        float scaleY = targetSize.y / bounds.height;
        sprite.setScale(scaleX, scaleY);
    }
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
void setShapeCenter(sf::Shape &shape, const sf::Vector2f &position)
{
    // Set the origin of the shape to its center
    shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);

    // Set the position of the shape to the desired center position
    shape.setPosition(position);
}

std::string keyToString(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Unknown)
        return "";
    using K = sf::Keyboard::Key;

    if (key >= K::A && key <= K::Z)
        return std::string(1, char('A' + (key - K::A)));
        
    return "";
}
