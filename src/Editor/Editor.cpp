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
            selectedEntity = nullptr;
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
    // Tính vùng nhìn hiện tại theo camera
    sf::Vector2f camCenter = model.getCameraCenter();
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect viewBounds(
        camCenter.x - winSize.x / 2.f,
        camCenter.y - winSize.y / 2.f,
        static_cast<float>(winSize.x),
        static_cast<float>(winSize.y)
    );

    // Vẽ grid trước
    drawGrid(window, viewBounds);
    if (selectedPrefab)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        sf::Sprite sprite = selectedPrefab->animation.sprite;
        resizeSprite(sprite, selectedPrefab->size);

        selectedPrefab->curPos.x = std::round((mousePos.x - 0.5f * selectedPrefab->size.x) / 48) * 48;
        selectedPrefab->curPos.y = std::round((mousePos.y + 0.5f * selectedPrefab->size.y) / 48) * 48 - selectedPrefab->size.y;

        sprite.setPosition(selectedPrefab->curPos);
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

void Editor::drawGrid(sf::RenderWindow& window, const sf::FloatRect& viewBounds, float cellSize)
{
    // Tạo VertexArray cho các đường ngang và dọc
    sf::VertexArray lines(sf::Lines);

    // Tọa độ bắt đầu và kết thúc
    float startX = std::floor(viewBounds.left / cellSize) * cellSize;
    float startY = std::floor(viewBounds.top / cellSize) * cellSize;
    float endX = viewBounds.left + viewBounds.width;
    float endY = viewBounds.top + viewBounds.height;

    // Các đường dọc
    for (float x = startX; x <= endX; x += cellSize) {
        lines.append(sf::Vertex(sf::Vector2f(x, startY), sf::Color(200, 200, 200, 100)));
        lines.append(sf::Vertex(sf::Vector2f(x, endY), sf::Color(200, 200, 200, 100)));
    }

    // Các đường ngang
    for (float y = startY; y <= endY; y += cellSize) {
        lines.append(sf::Vertex(sf::Vector2f(startX, y), sf::Color(200, 200, 200, 100)));
        lines.append(sf::Vertex(sf::Vector2f(endX, y), sf::Color(200, 200, 200, 100)));
    }

    window.draw(lines);
}