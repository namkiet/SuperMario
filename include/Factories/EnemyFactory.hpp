#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>

class EnemyFactory
{
private:


public:
    static const sf::Texture &getEnemyTexture(const std::string &enemyType)
    {
        size_t pos = enemyType.find('_');
        std::string folder = enemyType.substr(0, pos);
        folder[0] = std::toupper(folder[0]); // Capitalize first letter

        std::string texturePath = enemyFolder + folder + "/" + enemyType + ".png";
        return TextureManager::load(texturePath);
    }
    static std::string enemyFolder;
};

