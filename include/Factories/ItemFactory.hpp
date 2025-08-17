#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <ThemeManager.hpp>

class ItemFactory
{
private:
    static std::unordered_map<std::string, std::string> itemTypeToFolder;

public:
    ItemFactory(int theme)
    {
        setTheme();
    }

    static const sf::Texture &getItemTexture(const std::string &itemType)
    {
        setTheme();
        auto it = itemTypeToFolder.find(itemType);
        if (it != itemTypeToFolder.end())
        {
            std::string path = it->second;
            if (itemType == "mushroom1" || itemType == "bridge1")
            {
                path += "_0.png";
            }
            else if (itemType == "mushroom2" || itemType == "bridge2")
            {
                path += "_1.png";
            }
            return TextureManager::load(path);
        }
        return TextureManager::load("assets/Item/Default.png"); // Fallback texture
    }

    static std::vector<const sf::Texture *> getItemTextures(const std::string &itemType)
    {
        setTheme();
        auto it = itemTypeToFolder.find(itemType);
        if (it != itemTypeToFolder.end())
        {
            if (itemType != "coin3" && itemType != "bell")
                return {
                    &TextureManager::load(it->second + "_0.png"),
                    &TextureManager::load(it->second + "_1.png"),
                    &TextureManager::load(it->second + "_2.png"),
                    &TextureManager::load(it->second + "_3.png")};
            else
            {
                return {
                    &TextureManager::load(it->second + "_0.png"),
                    &TextureManager::load(it->second + "_1.png"),
                    &TextureManager::load(it->second + "_2.png")};
            }
        }
        return {&TextureManager::load("assets/Item/Default.png")}; // Fallback texture
    }

    static std::vector<const sf::Texture*> getCoin2Textures()
    {
        return 
        {
            &TextureManager::load("assets/Item/Coin/Coin2/Coin" + std::to_string(ThemeManager::getCoin2Theme()) + "_0.png"),
            &TextureManager::load("assets/Item/Coin/Coin2/Coin" + std::to_string(ThemeManager::getCoin2Theme()) + "_1.png"),
            &TextureManager::load("assets/Item/Coin/Coin2/Coin" + std::to_string(ThemeManager::getCoin2Theme()) + "_2.png"),
            &TextureManager::load("assets/Item/Coin/Coin2/Coin" + std::to_string(ThemeManager::getCoin2Theme()) + "_3.png")
        };
    }

    static void setTheme()
    {
        int theme = ThemeManager::getTheme();

        itemTypeToFolder["flower"] = "assets/Item/Flower/Flower" + std::to_string(theme);
        itemTypeToFolder["coin1"] = "assets/Item/Coin/Coin1/Coin" + std::to_string(theme);
        itemTypeToFolder["coin2"] = "assets/Item/Coin/Coin2/Coin" + std::to_string(theme);
        itemTypeToFolder["coin3"] = "assets/Item/Coin/Coin3/SmallCoin" + std::to_string(theme);
        itemTypeToFolder["star"] = "assets/Item/Star/Star" + std::to_string(theme);
        itemTypeToFolder["mushroom1"] = "assets/Item/Mushroom/Mushroom" + std::to_string(theme);
        itemTypeToFolder["mushroom2"] = "assets/Item/Mushroom/Mushroom" + std::to_string(theme);
        itemTypeToFolder["bridge1"] = "assets/Item/Bridge/Bridge";
        itemTypeToFolder["bridge2"] = "assets/Item/Bridge/Bridge";
        itemTypeToFolder["bell"] = "assets/Item/Bridge/Bell";
        itemTypeToFolder["debris1"] = "assets/Debris/Debris" + std::to_string(theme) + "_0.png";
        itemTypeToFolder["debris2"] = "assets/Debris/Debris" + std::to_string(theme) + "_1.png";
        itemTypeToFolder["debris3"] = "assets/Debris/Debris" + std::to_string(theme) + "_2.png";
        itemTypeToFolder["debris4"] = "assets/Debris/Debris" + std::to_string(theme) + "_3.png";
        itemTypeToFolder["elevator1"] = "assets/Item/Elevator/Elevator1.png";
        itemTypeToFolder["elevator2"] = "assets/Item/Elevator/Elevator2.png";
        itemTypeToFolder["elevator3"] = "assets/Item/Elevator/Elevator3.png";
        itemTypeToFolder["smallFireBar"] = "assets/Item/FireBar/smallFireBar.png";
        itemTypeToFolder["largeFireBar"] = "assets/Item/FireBar/largeFireBar.png";
        itemTypeToFolder["fireBullet"] = "assets/Item/FireBullet/FireBullet";
        itemTypeToFolder["fireworks"] = "assets/Item/FireBullet/FireBullet_4.png";
    }
};
