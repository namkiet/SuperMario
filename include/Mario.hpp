#pragma once

#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>
#include <Core/TextureManager.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y)
    {
        addComponent<Animation>(Animation(16, 16, 4, 0.1));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(100.f, 100.f)));
        // addComponent<Gravity>(Gravity(90.f));
        addComponent<Input>();
        addComponent<RigidBody>(RigidBody(0, 0));
        addComponent<Transform>(Transform(x, y, sf::Vector2f(100, 100)));
        
        Sprite2D marioSprites;
        marioSprites.registerSprite("Idling", TextureManager::load("assets/hero_idle.png"));
        marioSprites.registerSprite("Running", TextureManager::load("assets/hero_run.png"));
        marioSprites.setSprite("Idling");
        addComponent<Sprite2D>(marioSprites);
    }

private:
    sf::Texture texture;
};