#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>

class BlockFactory
{
private:
    std::string themeFolder;

public:
    BlockFactory(int theme)
        : themeFolder("assets/Tile/Tile" + std::to_string(theme) + "/Tile" + std::to_string(theme))
    {
    }
    const sf::Texture &getBlockTexture(int index) const
    {
        std::string path = themeFolder + "_" + std::to_string(index) + ".png";
        return TextureManager::load(path);
    }
    std::vector<const sf::Texture *> getQuestionBlockTextures() const
    {
        return {
            &TextureManager::load(themeFolder + "_24.png"), // Coin Question Block
            &TextureManager::load(themeFolder + "_25.png"), // Mushroom Question Block
            &TextureManager::load(themeFolder + "_26.png"), // Flower Question Block
        };
    }
};
