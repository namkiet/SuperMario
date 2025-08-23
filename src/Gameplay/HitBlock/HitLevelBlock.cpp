#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>

#include <Entity/Item/Mushroom.hpp>

void HitSpecialBlockSystem::HitLevelBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    int newLevel = 1;

    if (block->hasComponent<Level1BlockTag>())
    {
        newLevel = 1;
    }
    else if (block->hasComponent<Level2BlockTag>())
        newLevel = 2;
    else if (block->hasComponent<Level3BlockTag>())
    {
        newLevel = 3;
    }
    else if (block->hasComponent<Level4BlockTag>())
    {
        newLevel = 4;
    }
    world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/item.wav"));
    auto mushroom = world.createEntity<LevelMushroom>(pos.x, pos.y - 20, 48.0f, 48.0f, newLevel);
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    mushroom->addComponent<ItemEmerging>(emerging);
}