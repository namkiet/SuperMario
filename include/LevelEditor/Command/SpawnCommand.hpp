#pragma once
#include <LevelEditor/Command/ICommand.hpp>
#include <LevelEditor/Model.hpp>
#include <LevelEditor/PrefabStorage.hpp>

class SpawnCommand : public ICommand
{
public:
    SpawnCommand(Model& model, Prefab* prefab, sf::Vector2f mousePos) : model(model), prefab(prefab), mousePos(mousePos) {}

    bool execute() override
    {
        if (prefab)
        {
            sf::Vector2f spawnPos = mousePos - 0.5f * prefab->size;
            model.addEntity(std::move(prefab->creator(spawnPos.x, spawnPos.y)));
        }
        return true;
    }


private:
    Model& model;
    Prefab* prefab;
    sf::Vector2f mousePos;

    Entity* entity = nullptr;
};
