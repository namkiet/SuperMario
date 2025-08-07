#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/EnemyBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <memory>


struct EnemyTag : public Component 
{
    EnemyTag() : state(nullptr), behaviour(nullptr) {}
    EnemyTag(std::shared_ptr<EnemyState> state, std::shared_ptr<EnemyBehaviour> behaviour) : state(state), behaviour(behaviour) {}
    std::shared_ptr<EnemyState> state;
    std::shared_ptr<EnemyBehaviour> behaviour;
};

struct TowardPlayer : public Component 
{
    TowardPlayer() {}
    Direction direction = Direction::Left;
};

struct CanKillEnemyTag : public Component {};
struct NotOnPatrolYet : public Component {};

// Just for score purpose
struct ScoreAddedTag : public Component {};