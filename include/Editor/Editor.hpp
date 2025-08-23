#pragma once
#include <Editor/Model.hpp>
#include <Editor/PrefabStorage.hpp>
#include <Editor/EntityInspector.hpp>
#include <Editor/PrefabPanel.hpp>
#include <Editor/Command/ICommand.hpp>
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>

class Editor 
{
public:
    Editor(World& world);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void display(sf::RenderWindow& window);
    void drawUI();
    void drawGrid(sf::RenderWindow& window, const sf::FloatRect& viewBounds, float cellSize = 48.f);
    
private:
    Model model;
    PrefabStorage prefabs;
    EntityInspector inspector;
    PrefabPanel panel;

private:
    Entity* selectedEntity = nullptr;
    Prefab* selectedPrefab = nullptr;
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