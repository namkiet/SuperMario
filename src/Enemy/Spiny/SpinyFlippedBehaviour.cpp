#include <World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>

void SpinyFlippedBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}

void SpinyFlippedBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}

void SpinyFlippedBehaviour::patrol(Entity* entity, float dt, World& world)
{
    // no-op
}