#pragma once
#include <Editor/Command/ICommand.hpp>
#include <Editor/Model.hpp>
#include <Editor/PrefabStorage.hpp>
#include <Engine/Physics/SpatialHashGrid.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/Physics.hpp>
#include <SFML/System/Clock.hpp>

class SpawnCommand : public ICommand
{
public:
    SpawnCommand(Model& model, Prefab* prefab, sf::Vector2f mousePos, sf::RenderWindow& window) 
        : model(model), prefab(prefab), mousePos(mousePos), window(window) {}

    bool execute() override
    {
        if (!prefab) return true;

        // // anti-hold: enforce cooldown
        // sf::Time elapsed = spawnClock.getElapsedTime();
        // if (elapsed.asMilliseconds() < cooldownMs)
        //     return true; // too soon, ignore

        // spawnClock.restart();

        sf::Vector2f spawnPos = prefab->curPos;
        auto entity = prefab->creator(spawnPos.x, spawnPos.y);

        if (canPlace(entity.get()))
        {
            prefab->canBePlaced = true;
            model.addEntity(std::move(entity));
        }
        else
        {
            prefab->canBePlaced = false;
        }

        return true;
    }

    bool canPlace(Entity* entity)
    {
        auto bounds1 = Physics::GetCollisionBounds(entity);
        for (auto nearby : SpatialHashGrid::getInstance().query(bounds1))
        {
            auto bounds2 = Physics::GetCollisionBounds(nearby);
            if (!bounds1.intersects(bounds2)) continue;

            if (bounds1 == bounds2) return false;

            if ((entity->hasComponent<CanHitBlockTag>() && nearby->hasComponent<BlockTag>())|| 
                (entity->hasComponent<BlockTag>() && nearby->hasComponent<CanHitBlockTag>())) return false;
        }
        return true;
    }

private:
    Model& model;
    Prefab* prefab;

    sf::Vector2f mousePos;
    sf::RenderWindow& window;

    inline static sf::Clock spawnClock;         // shared timer for cooldown
    inline static constexpr int cooldownMs = 500; // 500ms cooldown
};
