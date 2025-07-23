#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Prefabs/Debris.hpp>

void HitSpecialBlockSystem::HitNormalBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    world.createEntity<SmallDebris1>(pos.x, pos.y, 24, 24);
    world.createEntity<SmallDebris2>(pos.x, pos.y, 24, 24);
    world.createEntity<SmallDebris3>(pos.x, pos.y, 24, 24);
    world.createEntity<SmallDebris4>(pos.x, pos.y, 24, 24);
}