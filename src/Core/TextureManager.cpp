// #include <Core/TextureManager.hpp>
// #include <SFML/Graphics.hpp>
// #include <string>

// std::unordered_map<std::string, sf::Texture> TextureManager::textureMap;

// std::string TextureManager::getPath(const sf::Texture* texture)
// {
//     for (const Texture& tex : textureMap)
//     {
//         if (tex == *texture)
//         {

//         }
//     }
// }

// sf::Texture& TextureManager::load(const std::string& fileName)
// {
//     auto found = textureMap.find(fileName);
//     if (found != textureMap.end())
//     {
//         return found->second;
//     }

//     sf::Texture texture;
//     if (!texture.loadFromFile(fileName))
//     {
//         throw std::runtime_error("Cannot load Texture: " + fileName);
//     }

//     textureMap[fileName] = std::move(texture);
//     return textureMap[fileName];
// }