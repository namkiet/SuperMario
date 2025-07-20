#pragma once
#include <SFML/Graphics.hpp>

void resizeSprite(sf::Sprite& sprite, const sf::Vector2f& targetSize)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    float scaleX = targetSize.x / bounds.width;
    float scaleY = targetSize.y / bounds.height;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);
}