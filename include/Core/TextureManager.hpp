#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

class TextureManager
{
public:
    // Load texture từ file (nếu đã có thì dùng lại)
    static sf::Texture& load(const std::string& fileName)
    {
        auto it = textureMap.find(fileName);
        if (it != textureMap.end())
        {
            return it->second;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(fileName))
        {
            throw std::runtime_error("Failed to load texture: " + fileName);
        }

        return textureMap.emplace(fileName, std::move(texture)).first->second;
    }

    // Tìm path của texture* (chậm hơn vì duyệt map)
    static std::string getPath(const sf::Texture* texture)
    {
        for (const auto& pair : textureMap)
        {
            if (&pair.second == texture)
            {
                return pair.first;
            }
        }

        throw std::runtime_error("Texture pointer not found in TextureManager");
    }

private:
    static inline std::unordered_map<std::string, sf::Texture> textureMap;
};
