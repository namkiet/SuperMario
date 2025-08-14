#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Prefabs/Debris.hpp>
#include <Prefabs/Mario.hpp>

void HitSpecialBlockSystem::HitNormalBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;
    int currentLevel = Mario::currentLevel;

    world.createEntity<SmallDebris1>(pos.x, pos.y, 24.0f, 24.0f, currentLevel);
    world.createEntity<SmallDebris2>(pos.x, pos.y, 24.0f, 24.0f, currentLevel);
    world.createEntity<SmallDebris3>(pos.x, pos.y, 24.0f, 24.0f, currentLevel);
    world.createEntity<SmallDebris4>(pos.x, pos.y, 24.0f, 24.0f, currentLevel);
}