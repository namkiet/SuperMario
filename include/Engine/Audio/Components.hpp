#pragma once
#include <ECS/Component.hpp>
#include <SFML/Audio.hpp>
#include <cassert>
#include <iostream>

struct SoundComponent : public Component
{
    SoundComponent(const sf::SoundBuffer* buffer = nullptr, bool loop = false, bool blockMusic = false, sf::Time blockMusicTimeAfterSound = sf::Time::Zero) 
        : buffer(buffer), shouldPlay(true), loop(loop), blockMusicTimeAfterSound(blockMusicTimeAfterSound), blockMusic(blockMusic) {}

    sf::Sound sound;
    const sf::SoundBuffer* buffer;
    bool shouldPlay;
    bool loop;

    bool blockMusic;
    sf::Time blockMusicTimeAfterSound;
};

struct MusicSource: public Component
{

    std::string path;

    sf::Vector2f soundSource;

    MusicSource(const std::string& path = "", sf::Vector2f pos = sf::Vector2f(-2000, -2000))
        : path(path), soundSource(pos)
    {
        std::cout << "path = " << path << std::endl;
        std::cout << "pos =" << pos.y << " " << pos.y << std::endl;
    }
};

        // if (!path.empty()) {
        //     music.openFromFile(path);
        // }

struct MusicPlayer: public Component
{
    sf::Music music;
    std::string curPath;
    MusicPlayer(): curPath("") {}
    void setMusic(const std::string& path = "")
    {
        if (!path.empty()) {
            if (!music.openFromFile(path)) assert(false);
            curPath = path;
        }
    }
};