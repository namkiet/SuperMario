#pragma once
#include <SFML/Graphics.hpp>
#include <string>

void resizeSprite(sf::Sprite &sprite, const sf::Vector2f &targetSize, bool shouldRepeat = false);

sf::Text textRender(std::string text, float x, float y, const sf::Font &font, float size);

void setShapeCenter(sf::Shape& shape, const sf::Vector2f& position);
std::string keyToString(sf::Keyboard::Key key);
