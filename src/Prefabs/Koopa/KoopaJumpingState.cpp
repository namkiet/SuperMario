#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/Koopa/Components.hpp>
#include <Prefabs/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaNormalState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaShellState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaSlideState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaJumpingState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaJumpingBehaviour.hpp>
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