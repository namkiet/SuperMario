#pragma once
#include <World.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <SFML/Graphics.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <iostream>

class AnimationSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<Animation>())
        {
            auto &anim = entity->getComponent<Animation>();

            if (entity->hasComponent<TowardPlayer>())
            {
                auto &direction = entity->getComponent<TowardPlayer>().direction;
                if (direction == Direction::Left)
                {
                    entity->addComponent<FlipXTag>();
                }
                else 
                {
                    entity->removeComponent<FlipXTag>();
                }
            }
            else if (entity->hasComponent<RigidBody>())
            {
                auto &rb = entity->getComponent<RigidBody>();
                if (rb.velocity.x > 0.0f)
                {
                    entity->removeComponent<FlipXTag>();
                    // anim.flipX = false;
                }
                else if (rb.velocity.x < 0.0f)
                {
                    entity->addComponent<FlipXTag>();
                    // anim.flipX = true;
                }
            }

            // if (anim.frameCount == 1)
            //     continue;

            // if (anim.textures.empty())
            // {
            //     std::cerr << "Animation textures are empty for entity: " << entity << std::endl;
            //     continue;
            // }

            anim.timer += dt;
            if (anim.timer >= anim.frameDuration)
            {
                anim.timer -= anim.frameDuration;
                anim.currentFrame++;

                if (anim.currentFrame >= anim.frameCount)
                {
                    if (anim.loop)
                    {
                        anim.currentFrame = 0;
                    }
                    else
                    {
                        anim.currentFrame = anim.frameCount - 1;
                        anim.hasEnded = true;
                    }
                }

            }

            if (anim.textures.size() == 1)
            {
                anim.sprite.setTexture(*anim.textures[0]);
                anim.sprite.setTextureRect(sf::IntRect(
                    anim.currentFrame * anim.frameWidth,
                    anim.row * anim.frameHeight,
                    anim.frameWidth,
                    anim.frameHeight
                ));
            }
            else
            {
                anim.sprite.setTexture(*anim.textures[anim.currentFrame]);
            }
        }
    }
};