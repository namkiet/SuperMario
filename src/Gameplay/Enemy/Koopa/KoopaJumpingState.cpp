#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumpingState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumpingBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <iostream>

void KoopaJumpingState::onEnter(Entity* entity)
{
    // no-op
}


std::shared_ptr<EnemyState> KoopaJumpingState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
        entity->removeComponent<KoopaJumpingTag>();
        entity->removeComponent<ChangeToKoopaNormalTag>();
        return std::make_shared<KoopaNormalState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<KoopaJumpingTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}