#include <Editor/EntityInspector.hpp>
#include <imgui.h>

EntityInspector::EntityInspector()
{
    basicFields.insert("Transform");
    basicFields.insert("BoxCollider2D");
    basicFields.insert("Animation");
}

void EntityInspector::draw(json& j) {
    updated = false; // reset update flag

    ImGui::Separator();
    ImGui::Text("Entity Properties:");

    // --- Basic fields ---
    for (auto& [key, value] : j.items()) {
        if (basicFields.count(key)) {
            drawJson(value, key);
        }
    }

    // --- Advanced fields ---
    if (ImGui::CollapsingHeader("Advanced")) {
        for (auto& [key, value] : j.items()) {
            if (!basicFields.count(key)) {
                drawJson(value, key);
            }
        }
    }
}

void EntityInspector::drawJson(json& value, const std::string& key) {
    if (key == "name") return;

    if (value.is_object()) {
        if (ImGui::TreeNode(key.c_str())) {
            for (auto& [subKey, subValue] : value.items()) {
                drawJson(subValue, subKey);
            }
            ImGui::TreePop();
        }
    }
    else if (value.is_array()) {
        if (ImGui::TreeNode((key + " [array]").c_str())) {
            int index = 0;
            for (auto& item : value) {
                drawJson(item, key + "[" + std::to_string(index++) + "]");
            }
            ImGui::TreePop();
        }
    }
    else if (value.is_boolean()) {
        bool v = value.get<bool>();
        if (ImGui::Checkbox(key.c_str(), &v)) {
            value = v;
            updated = true;
        }
    }
    else if (value.is_number_integer()) {
        int v = value.get<int>();
        if (ImGui::InputInt(key.c_str(), &v)) {
            value = v;
            updated = true;
        }
    }
    else if (value.is_number_float()) {
        float v = value.get<float>();
        if (ImGui::InputFloat(key.c_str(), &v, 0.1f, 1.0f, "%.3f")) {
            value = v;
            updated = true;
        }
    }
    else if (value.is_string()) {
        std::string v = value.get<std::string>();
        char buf[256];
        std::strncpy(buf, v.c_str(), sizeof(buf));
        buf[sizeof(buf) - 1] = '\0';

        ImGui::PushID(key.c_str()); // unique ID in case of duplicate keys

        // Input field
        if (ImGui::InputText("##edit", buf, sizeof(buf), ImGuiInputTextFlags_EnterReturnsTrue)) {
            value = std::string(buf);
            updated = true;
        }

        ImGui::SameLine();

        // Explicit "Apply" button
        if (ImGui::Button("Apply")) {
            value = std::string(buf);
            updated = true;
        }

        ImGui::PopID();
    }

    else {
        ImGui::Text("%s: %s", key.c_str(), value.dump().c_str());
    }
}

bool EntityInspector::hasUpdated() const {
    return updated;
}
