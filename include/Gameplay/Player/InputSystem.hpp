#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/Player/Components.hpp>
#include <SFML/Graphics.hpp>
#include <Core/KeyPressPool.hpp>

class InputSystem: public System
{
    public:
    void update(World& world, float dt) override
    {
        auto& keyPressPool = KeyPressPool::Instance();
        // clear at the start of each frame
        keyPressPool.clear();

        for (int k = 0; k < sf::Keyboard::KeyCount; ++k)
        {
            auto key = static_cast<sf::Keyboard::Key>(k);
            if (sf::Keyboard::isKeyPressed(key))
            {
                keyPressPool.addKey(key);
            }
        }
    }
};