#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadBehaviour.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void BowserDeadBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserDeadBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void BowserDeadBehaviour::patrol(Entity* entity, float dt, World& world)
{
    // no-op
}