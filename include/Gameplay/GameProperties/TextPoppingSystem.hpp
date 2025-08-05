#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Engine/Core/DespawnTag.hpp>

class TextPoppingSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<TextComponent>())
        {
            auto &textComponent = entity->getComponent<TextComponent>();
            if (textComponent.startY < textComponent.finalY)
            {
                entity->addComponent<DespawnTag>();
                continue;
            }
            textComponent.startY -= textComponent.dy * dt;
        }
    }
};