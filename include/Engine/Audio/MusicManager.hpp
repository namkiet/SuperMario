#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

class MusicManager {
public:
    bool load(const std::string& filename) {
        if (!music.openFromFile(filename))
            return false;
        music.setLoop(true);
        music.setVolume(50.f); // default volume
        return true;
    }

    void play() {
        if (music.getStatus() != sf::Music::Playing)
            music.play();
    }

    void stop() {
        music.stop();
    }

    void pause() {
        music.pause();
    }

    void setVolume(float volume) {
        music.setVolume(volume); // 0 - 100
    }

    void enable(bool enable) {
        if (enable)
            play();
        else
            stop();
    }

    bool isPlaying() const {
        return music.getStatus() == sf::Music::Playing;
    }

private:
    sf::Music music;
};
