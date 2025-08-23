
#pragma once
#include <Framework/World.hpp>
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
            sf::View view(sf::Vector2f(std::round(cam.target.x), std::round(cam.target.y)), sf::Vector2f(size.x, size.y));
            window.setView(view);
        }
        backgroundRender(window, level);

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
            resizeSprite(sp, sf::Vector2f(std::round(tf.size.x), std::round(tf.size.y)), anim.shouldRepeat);

            sp.setPosition(sf::Vector2f(std::round(tf.position.x), std::round(tf.position.y)));

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