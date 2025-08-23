#pragma once
#include <ECS/Component.hpp>

struct CoinBlockTag : public Component {};

struct GroundBlockTag : public Component {};

struct LevelUpBlockTag : public Component {};

struct NormalBlockTag : public Component {};

struct StairsBlockTag : public Component {};

struct StarBlockTag : public Component {};

struct CoinQuestionBlockTag : public Component {};

struct FlowerQuestionBlockTag : public Component {};

struct MushroomQuestionBlockTag : public Component {};

struct StarQuestionBlockTag : public Component {};

struct FlagBlockTag : public Component {};

struct QuestionBlockTag : public Component {};

struct CoinBlockComponent : public Component
{
    float waitingTime = 2.0f; // Time between coin spawns
    float timer = 0.0f;
    int hitCount = 12;
    bool isCollected = false;
    bool firstTime = false; // To ensure the first hit is handled correctly
};

struct MushroomBlockTag : public Component {};

struct Level1BlockTag : public Component {};

struct Level2BlockTag : public Component {};

struct Level3BlockTag : public Component {};

struct Level4BlockTag : public Component {};

struct LevelBlockTag : public Component {};