#pragma once
#include <ECS/Component.hpp>
#include <SFML/Audio.hpp>

struct SoundComponent : public Component
{
    SoundComponent(const sf::SoundBuffer* buffer = nullptr, bool loop = false) 
        : buffer(buffer), shouldPlay(true), loop(loop) {}

    sf::Sound sound;
    const sf::SoundBuffer* buffer;
    bool shouldPlay;
    bool loop;
};