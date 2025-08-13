#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>

class PipeFactory
{
private:
    std::unordered_map<std::string, std::string> pipeTypeToFolder;

public:
    PipeFactory(int theme)
    {
        pipeTypeToFolder["pipe1"] = "assets/Pipe/Pipe" + std::to_string(theme) + "_0.png";
        pipeTypeToFolder["pipe2"] = "assets/Pipe/Pipe" + std::to_string(theme) + "_1.png";
        pipeTypeToFolder["pipe3"] = "assets/Pipe/Pipe" + std::to_string(theme) + "_2.png";
    }

    const sf::Texture &getPipeTexture(const std::string &pipeType) const
    {
        auto it = pipeTypeToFolder.find(pipeType);
        if (it != pipeTypeToFolder.end())
        {
            return TextureManager::load(it->second);
        }
        return TextureManager::load("assets/Item/Pipe/Pipe_default.png"); // Fallback texture
    }
};