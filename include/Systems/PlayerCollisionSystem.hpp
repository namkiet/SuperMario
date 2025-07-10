#pragma once
#include <World.hpp>
#include <Components/PlayerTag.hpp>
#include <Components/EnemyTag.hpp>
#include <Core/Physics.hpp>
#include <Coin.hpp>

class PlayerCollisionSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        // Find the player (assume that there is only 1 player)
        player = world.findFirst<PlayerTag>();
        if (!player) return;

        for (auto& [collider, direction] : player->getComponent<BoxCollider2D>().collisions)
        {
            if (collider->hasComponent<EnemyTag>())
            {
                handlePlayerCollision(collider, direction);
            }
            else if (collider->hasComponent<BlockTag>())
            {
                auto& tag = collider->getComponent<BlockTag>();
                if (tag.type == "QuestionBlock")
                {
                    tag.type = "NormalBlock";
                    handleQuestionBlockCollision(collider, world);
                }
            }
        }
    }

private:
    void handlePlayerCollision(Entity* enemy, Direction direction)
    {
        if (direction == Direction::None) return;

        if (direction == Direction::Top)
        {
            player->getComponent<RigidBody>().velocity.y = -1000.0f;
            enemy->addComponent<DeadTag>();
        }
        else
        {
            player->addComponent<DeadTag>();
        }
    }

    void handleQuestionBlockCollision(Entity* block, World& world)
    {
        // Change texture of the block after hit
        if (block->hasComponent<Animation>()) 
        {
            auto& anim = block->getComponent<Animation>();
            anim.sprite = sf::Sprite(TextureManager::load("assets/coin_hit_block.png"));
            anim.frameWidth = 16;
            anim.frameHeight = 16;
            anim.frameCount = 1;
            anim.frameDuration = 0.0f;
        }

        // Spawn a coin entity on top of it
        if (block->hasComponent<Transform>())
        {
            auto& tf = block->getComponent<Transform>();
            auto& pos = tf.position;
            auto& sz = tf.size;

            world.createEntity(std::make_unique<Coin>(pos.x, pos.y - sz.y));
        }
    }

    Entity* player = nullptr;
};
