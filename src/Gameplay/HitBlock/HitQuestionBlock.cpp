#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>

#include <Entity/Item/Mushroom.hpp>
#include <Entity/Item/Star.hpp>
#include <Entity/Item/Coin.hpp>
#include <Entity/Item/Flower.hpp>

void HitSpecialBlockSystem::HitQuestionBlock(World &world, float dt, Entity *block, Entity *player)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    // Spawn a coin entity on top of it
    if (block->hasComponent<FlowerQuestionBlockTag>())
    {
        // Remove FlowerQuestionBlock component
        block->removeComponent<FlowerQuestionBlockTag>();

        if (player->hasComponent<BigMarioTag>())
        {
            world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/item.wav"));
            auto flower = world.createEntity<Flower>(pos.x, pos.y - 20, 48.0f, 48.0f);
            ItemEmerging emerging;
            emerging.finalY = pos.y - 48;
            flower->addComponent<ItemEmerging>(emerging);
        }
        else
        {
            world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/item.wav"));
            auto mushroom = world.createEntity<Mushroom1>(pos.x, pos.y - 20, 48.0f, 48.0f);
            ItemEmerging emerging;
            emerging.finalY = pos.y - 48;
            mushroom->addComponent<ItemEmerging>(emerging);
        }
    }
    else if (block->hasComponent<MushroomQuestionBlockTag>())
    {
        // Remove MushroomQuestionBlock component
        block->removeComponent<MushroomQuestionBlockTag>();

        world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/item.wav"));
        auto mushroom = world.createEntity<Mushroom1>(pos.x, pos.y - 20, 48.0f, 48.0f);
        ItemEmerging emerging;
        emerging.finalY = pos.y - 48;
        mushroom->addComponent<ItemEmerging>(emerging);
    }
    else if (block->hasComponent<CoinQuestionBlockTag>())
    {
        // Remove CoinQuestionBlock component
        block->removeComponent<CoinQuestionBlockTag>();

        world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/coin.wav"));
        auto coin = world.createEntity<Coin1>(pos.x, pos.y - sz.y, 48.0f, 48.0f);

        CoinManager::instance().addCoin();
    }
    else if (block->hasComponent<StarQuestionBlockTag>())
    {
        // Remove StarQuestionBlock component
        block->removeComponent<StarQuestionBlockTag>();

        world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/item.wav"));
        auto star = world.createEntity<Star>(pos.x, pos.y, 48.0f, 48.0f);
        ItemEmerging emerging;
        emerging.finalY = pos.y - 48;
        star->addComponent<ItemEmerging>(emerging);
    }
}