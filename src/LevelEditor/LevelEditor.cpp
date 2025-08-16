#include <LevelEditor/LevelEditor.hpp>
#include <LevelEditor/Helper.hpp>
#include <LevelEditor/Command/PanCommand.hpp>
#include <LevelEditor/Command/SpawnCommand.hpp>
#include <LevelEditor/Command/DragCommand.hpp>
#include <LevelEditor/Command/DeleteCommand.hpp>
#include <Engine/Animation/Animation.hpp>
#include <imgui.h>

LevelEditor::LevelEditor(World& world)
    : model(world.entityManager, world.componentRegistry)
    , prefabs(world.entityManager, world.componentRegistry) {}

void LevelEditor::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)) + model.getCameraCenter() - 0.5f * sf::Vector2f(window.getSize().x, window.getSize().y);

    if (ImGui::GetIO().WantCaptureMouse) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // selectedEntity = nullptr;
        if (selectedPrefab) 
        {
            setCommand<SpawnCommand>(model, selectedPrefab, mousePos);
            selectedPrefab = nullptr;
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
        setCommand<DeleteCommand>(model, mousePos);
    }

    // Execute and finalize
    if (currentCommand && currentCommand->execute())
    {
        // pushUndo(std::move(currentCommand));
        currentCommand = nullptr;
    }
}

void LevelEditor::display(sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (selectedPrefab)
    {
        sf::Sprite sprite = selectedPrefab->animation.sprite;
        resizeSprite(sprite, selectedPrefab->size);
        sprite.setPosition(mousePos - 0.5f * selectedPrefab->size);
        sf::Color color = sprite.getColor();
        color.a = 150;
        sprite.setColor(color);
        window.draw(sprite);
    }
}

void LevelEditor::drawUI()
{
    ImGui::Begin("Prefab Options");
    ImGui::Text("Prefabs");
    ImGui::Separator();

    int columns = 4;
    ImGui::Columns(columns, nullptr, false);

    for (auto& prefab : prefabs.getAll()) {
        updateAnimation(prefab.animation, 1.0f / 90); // update at constant 90 FPS

        auto btn = getAnimationButtonInfo(prefab.animation, 24.f);
        if (ImGui::ImageButton(btn.textureID, btn.size, btn.uv0, btn.uv1)) {
            selectedPrefab = &prefab;
        }

        ImGui::TextWrapped("%s", prefab.name.c_str());
        ImGui::NextColumn();
    }

    ImGui::End();
}