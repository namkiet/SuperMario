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

struct FireBulletTag : public Component
{
    // This tag is used to identify the fire bullet item
};

struct SmallCoinTag : public Component
{
    // This tag is used to identify the small coin item
};