#pragma once
#include <LevelEditor/Model.hpp>
#include <LevelEditor/PrefabStorage.hpp>
#include <LevelEditor/Command/ICommand.hpp>
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>

class LevelEditor 
{
public:
    LevelEditor(World& world);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void display(sf::RenderWindow& window);
    void drawUI();
    // void clear();
    
private:
    Model model;
    Entity* selectedEntity = nullptr;
    Prefab* selectedPrefab = nullptr;
    PrefabStorage prefabs;
    std::unique_ptr<ICommand> currentCommand = nullptr;

public:
    template<typename CommandType, typename... Args>
    void setCommand(Args&&... args)
    {
        // Only switch if current command is a different type
        if (!dynamic_cast<CommandType*>(currentCommand.get()))
        {
            currentCommand = std::make_unique<CommandType>(std::forward<Args>(args)...);
        }
    }
};