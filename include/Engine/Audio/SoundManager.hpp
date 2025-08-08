#pragma once
#include <SFML/Audio.hpp>
#include <string>

class SoundManager
{
public:
    static sf::SoundBuffer& load(const std::string& fileName)
    {
        auto found = soundMap.find(fileName);
        if (found != soundMap.end())
        {
            return found->second;
        }

        sf::SoundBuffer sound;
        if (!sound.loadFromFile(fileName))
        {
            throw std::runtime_error("Cannot load Sound: " + fileName);
        }

        soundMap[fileName] = std::move(sound);
        return soundMap[fileName];
    }

private:
    static inline std::unordered_map<std::string, sf::SoundBuffer> soundMap;
};