#pragma once
#include <unordered_map>
#include <stdexcept>

// Forward Declaration
namespace sf
{
    class Texture;
}

class TextureManager
{
public:
    static sf::Texture& load(const std::string& fileName);

private:
    static std::unordered_map<std::string, sf::Texture> textureMap;
};