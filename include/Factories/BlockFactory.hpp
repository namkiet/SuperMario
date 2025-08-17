#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <ThemeManager.hpp>
#include <iostream>

class BlockFactory
{
private:
    static std::string themeFolder;
public:
    BlockFactory()
    {
        // std::cout << "BlockFactory themeFolder: " << themeFolder << std::endl;  
    }
    static const sf::Texture &getBlockTexture(int index)
    {
        setTheme();
        std::string path = themeFolder + "_" + std::to_string(index) + ".png";
        return TextureManager::load(path);
    }
    static std::vector<const sf::Texture *> getQuestionBlockTextures()
    {
        setTheme();
        return {
            &TextureManager::load(themeFolder + "_24.png"), // Coin Question Block
            &TextureManager::load(themeFolder + "_25.png"), // Mushroom Question Block
            &TextureManager::load(themeFolder + "_26.png"), // Flower Question Block
        };
    }
    static void setTheme()
    {
        int theme = ThemeManager::getTheme();
        themeFolder = "assets/Tile/Tile" + std::to_string(theme) + "/Tile" + std::to_string(theme);
    }
};
