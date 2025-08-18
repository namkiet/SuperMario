#pragma once
#include <ECS/Component.hpp>
using namespace std;

struct CoinBlock : public Component {};

struct GroundBlock : public Component {};

struct LevelUpBlock : public Component {};

struct NormalBlock : public Component {};

struct StairsBlock : public Component {};

struct StarBlock : public Component {};

struct CoinQuestionBlock : public Component {};

struct FlowerQuestionBlock : public Component {};

struct MushroomQuestionBlock : public Component {};

struct StarQuestionBlock : public Component {};

struct FlagBlock : public Component {};

struct QuestionBlockTag : public Component {};

struct CoinBlockComponent : public Component
{
    float waitingTime = 2.0f; // Time between coin spawns
    float timer = 0.0f;
    int hitCount = 12;
    bool isCollected = false;
    bool firstTime = false; // To ensure the first hit is handled correctly
};

struct MushroomBlock : public Component
{
};

struct Level1Block : public Component
{
};

struct Level2Block : public Component
{
};

struct Level3Block : public Component
{
};

struct Level4Block : public Component
{
};

struct LevelBlock : public Component
{
};