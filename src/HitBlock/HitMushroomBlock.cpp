#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Prefabs/Mushroom.hpp>
#include <iostream>

void HitSpecialBlockSystem::HitMushroomBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;
    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    Entity *gameSession = world.findFirst<ThemeComponent>();
    if (!gameSession)
        return;
    auto &themeComponent = gameSession->getComponent<ThemeComponent>();
    auto mushroom = world.createEntity<Mushroom1>(pos.x, pos.y - 20, 48, 48, ItemFactory(themeComponent.currentTheme));
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    mushroom->addComponent<ItemEmerging>(emerging);
}