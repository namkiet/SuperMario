#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlyingState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlyingBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <iostream>
#include <Gameplay/GameProperties/Components.hpp>

void KoopaFlyingState::onEnter(Entity* entity)
{
    // no-op
}


std::shared_ptr<EnemyState> KoopaFlyingState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
        entity->removeComponent<KoopaFlyingTag>();
        entity->removeComponent<KoopaFlyingPatrol>();
        entity->removeComponent<ChangeToKoopaNormalTag>();

        // Add score tag to notify the score system
        entity->addComponent<ShouldUpdateScore>(400);

        return std::make_shared<KoopaNormalState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<KoopaFlyingTag>();
        entity->removeComponent<KoopaFlyingPatrol>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}