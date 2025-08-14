#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>

#include <Prefabs/Mushroom.hpp>

void HitSpecialBlockSystem::HitLevelBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    int newLevel = 1;

    if (block->hasComponent<Level1Block>())
    {
        newLevel = 1;
    }
    else if (block->hasComponent<Level2Block>())
        newLevel = 2;
    else if (block->hasComponent<Level3Block>())
    {
        newLevel = 3;
    }
    else if (block->hasComponent<Level4Block>())
    {
        newLevel = 4;
    }
    auto mushroom = world.createEntity<LevelMushroom>(pos.x, pos.y - 20, 48, 48, newLevel, ItemFactory(1));
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    mushroom->addComponent<ItemEmerging>(emerging);
}