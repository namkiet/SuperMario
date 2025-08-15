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

    Entity *gameSession = world.findFirst<ThemeComponent>();
    if (!gameSession)
        return;
    auto &themeComponent = gameSession->getComponent<ThemeComponent>();
    auto mushroom = world.createEntity<Mushroom2>(pos.x, pos.y - 20, 48.0f, 48.0f, ItemFactory(themeComponent.currentTheme));
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    mushroom->addComponent<ItemEmerging>(emerging);
}