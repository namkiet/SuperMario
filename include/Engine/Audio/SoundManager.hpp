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

    static std::string getPath(const sf::SoundBuffer* buffer)
    {
        for (const auto& pair : soundMap)
        {
            if (&pair.second == buffer)
            {
                return pair.first;
            }
        }

        throw std::runtime_error("Sound pointer not found in SoundManager");
    }

private:
    static inline std::unordered_map<std::string, sf::SoundBuffer> soundMap;
};