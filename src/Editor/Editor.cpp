#include <Editor/Editor.hpp>
#include <Editor/Helper.hpp>
#include <Editor/Command/PanCommand.hpp>
#include <Editor/Command/SpawnCommand.hpp>
#include <Editor/Command/DragCommand.hpp>
#include <Editor/Command/DeleteCommand.hpp>
#include <Engine/Animation/Animation.hpp>
#include <imgui.h>
#include <fstream>

Editor::Editor(World& world)
    : model(world.entityManager, world.componentRegistry)
    , prefabs(world.entityManager, world.componentRegistry)
    , panel(prefabs) {}

void Editor::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)) + model.getCameraCenter() - 0.5f * sf::Vector2f(window.getSize().x, window.getSize().y);

    if (ImGui::GetIO().WantCaptureMouse) return;

    if (!currentCommand)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            selectedEntity = nullptr;
            if (selectedPrefab) 
            {
                setCommand<SpawnCommand>(model, selectedPrefab, mousePos, window);
                // selectedPrefab = nullptr;
            }
            else if (auto draggedEntity = model.getEntityAt(mousePos.x, mousePos.y))
            {
                setCommand<DragCommand>(draggedEntity, window);
                selectedEntity = draggedEntity;
            }
            else
            {
                setCommand<PanCommand>(window, model.getCameraCenter());
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (selectedPrefab)
            {
                selectedPrefab = nullptr;
            }
            else
            {
                setCommand<DeleteCommand>(model, mousePos);
            }
        }
    }

    // Execute and finalize
    if (currentCommand && currentCommand->execute())
    {
        currentCommand = nullptr;
    }
}

void Editor::display(sf::RenderWindow& window)
{
    if (selectedPrefab)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        sf::Sprite sprite = selectedPrefab->animation.sprite;
        resizeSprite(sprite, selectedPrefab->size);
        sprite.setPosition(mousePos - 0.5f * selectedPrefab->size);
        sf::Color color = sprite.getColor();
        color.a = 200;
        sprite.setColor(color);
        window.draw(sprite);
    }
}

void Editor::drawUI()
{
    ImGui::Begin("Prefab Options");

    panel.draw();

    // Prefab browser
    if (auto chosen = panel.getSelectedPrefab()) {
        selectedPrefab = chosen;
    }

    // Entity inspector
    if (selectedEntity) {
        json j = model.getEntityInfo(selectedEntity);
        inspector.draw(j);

        if (inspector.hasUpdated())
        {
            model.updateEntityInfo(selectedEntity, j);
        }
    }

    ImGui::End();
}