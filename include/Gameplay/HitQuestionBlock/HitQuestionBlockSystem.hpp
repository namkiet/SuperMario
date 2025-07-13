#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/HitQuestionBlock/Components.hpp>
#include <Prefabs/Coin.hpp>

class HitQuestionBlockSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        for (Entity* entity : world.findAll<BoxCollider2D, CanHitQuestionBlockTag>())
        {
            for (auto& [block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<QuestionBlockTag>()) continue;
                if (direction != Direction::Bottom) continue;
                
                block->removeComponent<QuestionBlockTag>();
                
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

                    world.createEntity<Coin>(pos.x, pos.y - sz.y);
                }
            }
        }
    }
};
