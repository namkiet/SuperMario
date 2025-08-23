#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedBehaviour.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaFlippedBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void KoopaFlippedBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void KoopaFlippedBehaviour::patrol(Entity* entity, float dt, World& world)
{
    // no-op
}