#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <stdexcept>

class Sprite2D : public Component
{
public:
    Sprite2D(const sf::Sprite& sprite) : sprite(sprite) {}

    Sprite2D() = default;

    void registerSprite(const std::string& name, const sf::Texture& texture)
    {
        if (spriteMap.find(name) != spriteMap.end())
        {
            throw std::runtime_error("Sprite " + name + "has already been registered.");
        }

        sf::Sprite newSprite(texture);
        spriteMap[name] = newSprite;
    }

    void setSprite(const std::string& name)
    {
        if (spriteMap.find(name) == spriteMap.end())
        {
            throw std::runtime_error("Cannot find sprite: " + name);
        }
        sprite = spriteMap[name];
    }

    sf::Sprite& getSprite()
    {
        return sprite;
    }
    
    sf::Sprite sprite;

private:
    std::unordered_map<std::string, sf::Sprite> spriteMap;
};