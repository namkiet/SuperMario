// TextureHolder.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

enum class TexType {
    background,
    close,
    settingpanel,
    home,
    soundOn,
    soundOff,
    playPanel,
    sound,
    music,
    save,
    turnback,
    marioidling,
    mariochoose,
    marionotchoose,
    luigichoose,
    luiginotchoose,
    keybutton,
    pause
};

using TextureHolder = ResourceHolder<sf::Texture, TexType>;
