#pragma once
#include <World.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <Engine/Animation/Animation.hpp>

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

#include <Core/TextureManager.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <Prefabs/Mario.hpp>

class DrawGameComponentSystem : public System
{
private:
    sf::Font font;

public:
    DrawGameComponentSystem()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }

    void update(World &, float) override
    {
        // no-op
    }

    void draw(const World &world, sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());
        
        for (Entity *entity : world.findAll<SmallCoinTag>())
        {
            auto &tf = entity->getComponent<Transform>();
            auto &anim = entity->getComponent<Animation>();
            auto &sp = anim.sprite;

            // Resize sprite uniformly to fit target size
            resizeSprite(sp, tf.size);

            sp.setPosition(tf.position);
            sf::Vector2f scale = sp.getScale();
            sp.setScale(scale);
            window.draw(sp);
        }
    }
};