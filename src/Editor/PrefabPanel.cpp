#include <Editor/PrefabPanel.hpp>
#include <Editor/Helper.hpp>
#include <imgui.h>

PrefabPanel::PrefabPanel(PrefabStorage& prefabs) : prefabs(prefabs) {}

void PrefabPanel::draw() {
    ImGui::Text("Prefabs");
    ImGui::Separator();

    selectedPrefab = nullptr;
    if (ImGui::BeginTabBar("PrefabTabs")) {
        // Tab Block
        if (ImGui::BeginTabItem("Block")) {
            drawPrefabCategory(PrefabStorage::Category::Block);
            ImGui::EndTabItem();
        }

        // Tab Item
        if (ImGui::BeginTabItem("Item")) {
            drawPrefabCategory(PrefabStorage::Category::Item);
            ImGui::EndTabItem();
        }

        // Tab Enemy
        if (ImGui::BeginTabItem("Enemy")) {
            drawPrefabCategory(PrefabStorage::Category::Enemy);
            ImGui::EndTabItem();
        }

        // Tab Background
        if (ImGui::BeginTabItem("Background")) {
            drawPrefabCategory(PrefabStorage::Category::Background);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}


void PrefabPanel::drawPrefabCategory(PrefabStorage::Category category) {
    int columns = 4;
    ImGui::Columns(columns, nullptr, false);

    for (auto& prefab : prefabs.getCategory(category)) {
        prefab.animation.update(1.0f / 90);

        auto btn = getAnimationButtonInfo(prefab.animation, 24.f);
        if (ImGui::ImageButton(btn.textureID, btn.size, btn.uv0, btn.uv1)) {
            selectedPrefab = &prefab;
        }

        ImGui::TextWrapped("%s", prefab.name.c_str());
        ImGui::NextColumn();
    }

    ImGui::Columns(1); // reset
}


Prefab* PrefabPanel::getSelectedPrefab()
{
    return selectedPrefab;
}