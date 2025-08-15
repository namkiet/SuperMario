#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Prefabs/Debris.hpp>

void HitSpecialBlockSystem::HitNormalBlock(World &world, float dt, Entity *block)
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

    world.createEntity<SmallDebris1>(pos.x, pos.y, 24.0f, 24.0f, ItemFactory(themeComponent.currentTheme));
    world.createEntity<SmallDebris2>(pos.x, pos.y, 24.0f, 24.0f, ItemFactory(themeComponent.currentTheme));
    world.createEntity<SmallDebris3>(pos.x, pos.y, 24.0f, 24.0f, ItemFactory(themeComponent.currentTheme));
    world.createEntity<SmallDebris4>(pos.x, pos.y, 24.0f, 24.0f, ItemFactory(themeComponent.currentTheme));
}