#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Prefabs/Mushroom.hpp>
#include <Prefabs/Star.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Flower.hpp>

void HitSpecialBlockSystem::HitQuestionBlock(World &world, float dt, Entity *block)
{
    if (!block->hasComponent<Transform>())
        return;

    auto &tf = block->getComponent<Transform>();
    auto &pos = tf.position;
    auto &sz = tf.size;

    // Spawn a coin entity on top of it
    if (block->hasComponent<FlowerQuestionBlock>())
    {
        // Remove FlowerQuestionBlock component
        block->removeComponent<FlowerQuestionBlock>();

        auto flower = world.createEntity<Flower>(pos.x, pos.y - sz.y, 48, 48);
        flower->addComponent<CollectableTag>();
    }
    else if (block->hasComponent<MushroomQuestionBlock>())
    {
        // Remove MushroomQuestionBlock component
        block->removeComponent<MushroomQuestionBlock>();

        auto mushroom = world.createEntity<Mushroom1>(pos.x, pos.y, 48, 48);
        ItemEmerging emerging;
        emerging.finalY = pos.y - 48;
        mushroom->addComponent<ItemEmerging>(emerging);
    }
    else if (block->hasComponent<CoinQuestionBlock>())
    {
        // Remove CoinQuestionBlock component
        block->removeComponent<CoinQuestionBlock>();

        world.createEntity<Coin1>(pos.x, pos.y - sz.y, 48, 48);
    }

    else if (block->hasComponent<StarQuestionBlock>())
    {
        // Remove StarQuestionBlock component
        block->removeComponent<StarQuestionBlock>();

        auto star = world.createEntity<Star>(pos.x, pos.y, 48, 48);
        ItemEmerging emerging;
        emerging.finalY = pos.y - 48;
        star->addComponent<ItemEmerging>(emerging);
    }
}