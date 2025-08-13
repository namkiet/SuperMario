#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Prefabs/Coin.hpp>
#include <Factories/BlockFactory.hpp>

void HitSpecialBlockSystem::CoinBlockUpdate(World &world, float dt, Entity *block)
{
    auto &coinBlockComponent = block->getComponent<CoinBlockComponent>();

    if (!coinBlockComponent.firstTime)
        return;
    coinBlockComponent.timer += dt;

    if (coinBlockComponent.timer >= coinBlockComponent.waitingTime)
    {
        coinBlockComponent.hitCount = 1;
    }
    if (coinBlockComponent.isCollected)
    {
        block->removeComponent<CoinBlock>();
        block->removeComponent<CoinBlockComponent>();
        block->removeComponent<Animation>();
        Entity* gameSession = world.findFirst<ThemeComponent>();
        if (!gameSession)
            return;
        auto &themeComponent = gameSession->getComponent<ThemeComponent>();
        BlockFactory blockFactory(themeComponent.currentTheme);
        block->addComponent<Animation>(blockFactory.getBlockTexture(27));
    }
}

void HitSpecialBlockSystem::HitCoinBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &collected = block->getComponent<CoinBlockComponent>().isCollected;
    auto &coinBlockComponent = block->getComponent<CoinBlockComponent>();

    if (!coinBlockComponent.firstTime)
        coinBlockComponent.firstTime = true;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    if (coinBlockComponent.hitCount > 0)
    {
        Entity *gameSession = world.findFirst<ThemeComponent>();
        if (!gameSession)
            return;
        auto &themeComponent = gameSession->getComponent<ThemeComponent>();
        auto coin = world.createEntity<Coin1>(pos.x, pos.y - sz.y - sz.y / 4, 48, 48, ItemFactory(themeComponent.currentTheme));

        coinBlockComponent.timer = 0.0f;
        --coinBlockComponent.hitCount;
        // std::cout << "Coin create" << std::endl;
        // std::cout << "CoinBlockComponent hitCount: " << coinBlockComponent.hitCount << std::endl;
        if (coinBlockComponent.hitCount <= 0)
        {
            collected = true;
        }
    }
}