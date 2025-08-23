#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Lakitu/LakituFlippedBehaviour.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Lakitu/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>

void LakituFlippedBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void LakituFlippedBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void LakituFlippedBehaviour::patrol(Entity* entity, float dt, World& world)
{
    // no-op
}