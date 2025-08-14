
#pragma once
#include <World.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <Engine/Rendering/ZIndex.hpp>
#include <SFML/Graphics.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Gameplay/Obstacles/Components.hpp>

class RenderSystem : public System
{
private:
    sf::Font font;
    void backgroundRender(sf::RenderWindow &window, int level) const;
    void textComponentRender(const World &world, sf::RenderWindow &window) const;

    static int getZIndex(Entity* entity)
    {
        if (!entity->hasComponent<ZIndex>()) return 0;
        return entity->getComponent<ZIndex>().value;
    }

public:
    RenderSystem()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void update(World &, float) override
    {
        // no-op
    }

    void draw(const World &world, sf::RenderWindow &window, int level) const
    {
        if (world.findFirst<Camera>())
        {
            auto &cam = world.findFirst<Camera>()->getComponent<Camera>();
            auto size = window.getSize();
            sf::View view(cam.target, sf::Vector2f(size.x, size.y));
            window.setView(view);
        }
        backgroundRender(window, level);
        textComponentRender(world, window);

        std::vector<Entity*> entities = world.findAll<Transform, Animation>();
        std::sort(entities.begin(), entities.end(), [](Entity* a, Entity* b) {
            return getZIndex(a) < getZIndex(b);
        });

        for (Entity *entity : entities)
        {
            if (entity->hasComponent<SmallCoinTag>())
            {
                continue; //
            }

            auto &tf = entity->getComponent<Transform>();
            auto &anim = entity->getComponent<Animation>();
            auto &sp = anim.sprite;

            // Resize sprite uniformly to fit target size
            resizeSprite(sp, tf.size);

            sp.setPosition(tf.position);

            // Flip horizontally if needed
            sf::Vector2f scale = sp.getScale();
            if (entity->hasComponent<FlipXTag>())
            {
                sp.setOrigin(sp.getLocalBounds().width, 0);
                scale.x = -std::abs(scale.x); // flip horizontally
            }
            else
            {
                sp.setOrigin(0, 0);
                scale.x = std::abs(scale.x); // ensure it's normal if not flipped
            }
            sp.setScale(scale);

            // Set origin to center (important for correct flipping)
            // sp.setOrigin(sp.getLocalBounds().width / 2.f, sp.getLocalBounds().height / 2.f);

            // // Position sprite centered within the tf area
            // sf::Vector2f center;
            // center.x = tf.position.x + 0.5f * tf.size.x;
            // center.y = tf.position.y + tf.size.y - 0.5f * sp.getGlobalBounds().height;

            // sp.setPosition(center);

            if (entity->hasComponent<FireBarComponent>())
            {
                auto &fireBar = entity->getComponent<FireBarComponent>();
                sp.setRotation(fireBar.angle);

                sp.setOrigin(sp.getLocalBounds().width / 2, 12);
                sp.setPosition(tf.position.x + tf.size.x / 2, tf.position.y + 12);
            }
            window.draw(sp);
        }
    }
};