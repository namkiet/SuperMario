#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Audio/Components.hpp>
#include <SFML/Audio.hpp>
#include <cassert>
#include <algorithm>
class SoundSystem : public System
{
public:
    sf::Time MusicBlockBySoundTime = sf::seconds(0.f);
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<SoundComponent>())
        {
            auto& soundComponent = entity->getComponent<SoundComponent>();
            
            if (soundComponent.shouldPlay)
            {
                soundComponent.sound.setBuffer(*soundComponent.buffer);
                soundComponent.sound.setVolume(SOUND::shouldPlaySound? 100: 0);
                soundComponent.sound.play();
                soundComponent.sound.setLoop(soundComponent.loop);
                if (soundComponent.blockMusic) {
                    const sf::Time dur = soundComponent.buffer->getDuration()
                                    + soundComponent.blockMusicTimeAfterSound;
                    MusicBlockBySoundTime = std::max(MusicBlockBySoundTime, dur);
                }
                soundComponent.shouldPlay = false;
            }

            if (soundComponent.sound.getStatus() == sf::Sound::Stopped && !soundComponent.loop) 
            {
                entity->removeComponent<SoundComponent>();
            }

        }
        
        // if (!SOUND::shouldPlayMusic) return;
        bool SoundBlockMusic = MusicBlockBySoundTime > sf::Time::Zero;

        auto camera = world.findFirst<Camera>();
        auto musicPlayer = world.findFirst<MusicPlayer>(); auto& music = musicPlayer->getComponent<MusicPlayer>();
        if (SoundBlockMusic) 
        {
            // std::cout << "can not play music due to sound block\n";
            MusicBlockBySoundTime -= sf::seconds(dt);
            if (MusicBlockBySoundTime < sf::Time::Zero)
                MusicBlockBySoundTime = sf::Time::Zero;
        }

        music.music.setVolume((SoundBlockMusic || !SOUND::shouldPlayMusic)? 0: 50);
        assert (musicPlayer && camera);
        for (Entity *entity : world.findAll<MusicSource>())
        {
            auto& mu = entity->getComponent<MusicSource>();
            auto pos = mu.soundSource;
            if (!camera->getComponent<Camera>().isInScreen(pos)) {
                continue; }// out of screen, skip
            
            if (mu.path == musicPlayer->getComponent<MusicPlayer>().curPath) {
                // std::cout << mu.path << std::endl;
                break;} // already play music
            music.setMusic(mu.path);
            music.music.setVolume(SOUND::shouldPlayMusic && !SoundBlockMusic? 50: 0);
            music.music.play(); music.music.setLoop(true);
            std::cout << "set to new music source" << std::endl;
        }
    }
};

//