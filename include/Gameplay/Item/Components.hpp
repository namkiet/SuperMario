#pragma once
#include <ECS/Component.hpp>

struct Coin1Tag : public Component
{
};

struct DebrisTag : public Component
{
};

struct Debris1Tag : public Component
{
    // This tag is used to identify the first type of debris
};

struct Debris2Tag : public Component
{
    // This tag is used to identify the second type of debris
};

struct Debris3Tag : public Component
{
    // This tag is used to identify the third type of debris
};

struct Debris4Tag : public Component
{
    // This tag is used to identify the fourth type of debris
};

struct StarTag : public Component
{
    // This tag is used to identify the star item
};

struct MushroomTag : public Component
{
    enum Buff { GIVE_ONE_MORE_LIFE, GROW_UP };
    Buff buff;

    MushroomTag(Buff buff) : buff(buff) {}
};

struct FlowerTag : public Component
{

};

struct FireBulletTag : public Component
{
    // This tag is used to identify the fire bullet item
};
