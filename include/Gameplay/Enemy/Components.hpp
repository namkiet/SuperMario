#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/EnemyBehaviour.hpp>
#include <memory>

struct EnemyTag : public Component 
{
    EnemyTag(std::shared_ptr<EnemyState> state, std::shared_ptr<EnemyBehaviour> behaviour) : state(state), behaviour(behaviour) {}
    std::shared_ptr<EnemyState> state;
    std::shared_ptr<EnemyBehaviour> behaviour;
};

struct CanKillEnemyTag : public Component {};
struct NotOnPatrolYet : public Component {};

// Just for score purpose
struct ScoreAddedTag : public Component {};
