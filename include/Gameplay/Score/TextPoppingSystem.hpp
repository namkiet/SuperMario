#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Score/Components.hpp>
#include <Engine/Core/DespawnTag.hpp>

class TextPoppingSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<TextComponent>())
        {
            auto &textComponent = entity->getComponent<TextComponent>();
            ++textComponent.timer;
            if (textComponent.timer > textComponent.dt)
            {
                entity->addComponent<DespawnTag>();
                continue;
            }
            textComponent.y -= textComponent.dy;
        }
    }
};