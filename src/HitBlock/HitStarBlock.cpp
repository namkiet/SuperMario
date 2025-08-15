#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Prefabs/Star.hpp>

void HitSpecialBlockSystem::HitStarBlock(World &world, float dt, Entity *block)
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

    // Create a Star entity
    auto star = world.createEntity<Star>(pos.x, pos.y, 48.0f, 48.0f, ItemFactory(themeComponent.currentTheme));
    ItemEmerging emerging;
    emerging.finalY = pos.y - 48;
    star->addComponent<ItemEmerging>(emerging);
}