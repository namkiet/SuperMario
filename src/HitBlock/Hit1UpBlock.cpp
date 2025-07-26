#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Prefabs/Mushroom.hpp>

void HitSpecialBlockSystem::Hit1UpBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    auto mushroom = world.createEntityAtFront<Mushroom2>(pos.x, pos.y - 20, 48, 48);
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    mushroom->addComponent<ItemEmerging>(emerging);
}