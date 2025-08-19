#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Audio/Components.hpp>
#include <SFML/Audio.hpp>

class SoundSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<SoundComponent>())
        {
            auto& soundComponent = entity->getComponent<SoundComponent>();
            
            if (soundComponent.shouldPlay)
            {
                soundComponent.sound.setBuffer(*soundComponent.buffer);
                soundComponent.sound.setVolume(SOUND::shouldPlayMusic? 100: 0);
                soundComponent.sound.play();
                soundComponent.sound.setLoop(soundComponent.loop);
                soundComponent.shouldPlay = false;
            }

            if (soundComponent.sound.getStatus() == sf::Sound::Stopped && !soundComponent.loop) 
            {
                entity->removeComponent<SoundComponent>();
            }

        }
    }
};