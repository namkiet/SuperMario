#include <Editor/PrefabPanel.hpp>
#include <Editor/Helper.hpp>
#include <imgui.h>

PrefabPanel::PrefabPanel(PrefabStorage& prefabs) : prefabs(prefabs) {}

void PrefabPanel::draw() {
    ImGui::Text("Prefabs");
    ImGui::Separator();

    int columns = 4;
    ImGui::Columns(columns, nullptr, false);

    selectedPrefab = nullptr;
    for (auto& prefab : prefabs.getAll()) {
        prefab.animation.update(1.0f / 90); // update at constant 90 FPS

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