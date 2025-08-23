#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Entity/Miscellaneous/Debris.hpp>

void HitSpecialBlockSystem::HitNormalBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/Brick.wav"));

    world.createEntity<SmallDebris1>(pos.x, pos.y, 24.0f, 24.0f);
    world.createEntity<SmallDebris2>(pos.x, pos.y, 24.0f, 24.0f);
    world.createEntity<SmallDebris3>(pos.x, pos.y, 24.0f, 24.0f);
    world.createEntity<SmallDebris4>(pos.x, pos.y, 24.0f, 24.0f);
}