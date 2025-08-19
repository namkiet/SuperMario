#include <Engine/Rendering/Utility.hpp>
void resizeSprite(sf::Sprite &sprite, const sf::Vector2f &targetSize)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    float scaleX = targetSize.x / bounds.width;
    float scaleY = targetSize.y / bounds.height;
    // float scale = std::min(scaleX, scaleY);
    sprite.setScale(scaleX, scaleY);
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

std::string keyToString(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Unknown) return "";
    using K = sf::Keyboard::Key;

    if (key >= K::A && key <= K::Z)     return std::string(1, char('A' + (key - K::A)));
    if (key >= K::Num0 && key <= K::Num9) return std::string(1, char('0' + (key - K::Num0)));
    if (key >= K::Numpad0 && key <= K::Numpad9) return "Num" + std::to_string(int(key - K::Numpad0));

    switch (key) {
        case K::Space:      return "Space";
        case K::Enter:      return "Enter";
        case K::Escape:     return "Esc";
        case K::Backspace:  return "Backspace";
        case K::Tab:        return "Tab";
        case K::LShift:     return "LShift";
        case K::RShift:     return "RShift";
        case K::LControl:   return "LControl";
        case K::RControl:   return "RControl";
        case K::LAlt:       return "LAlt";
        case K::RAlt:       return "RAlt";
        case K::LSystem:    return "LMeta";
        case K::RSystem:    return "RMeta";
        case K::Left:       return "Left";
        case K::Right:      return "Right";
        case K::Up:         return "Up";
        case K::Down:       return "Down";
        case K::PageUp:     return "PageUp";
        case K::PageDown:   return "PageDown";
        case K::Home:       return "Home";
        case K::End:        return "End";
        case K::Insert:     return "Insert";
        case K::Delete:     return "Delete";
        case K::Hyphen:     return "-";
        case K::Equal:      return "=";
        case K::LBracket:   return "[";
        case K::RBracket:   return "]";
        case K::Semicolon:  return ";";
        case K::Comma:      return ",";
        case K::Period:     return ".";
        case K::Quote:      return "'";
        case K::Slash:      return "/";
        case K::Backslash:  return "\\";
        case K::Grave:      return "`";
        default:            return "Unknown";
    }
}
