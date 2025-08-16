#include <LevelEditor/ComponentEditor.hpp>
#include <Framework/EntityManager.hpp>
#include <cstring>
#include <string>

ComponentEditor::ComponentEditor(EntityManager& em, ComponentRegistry& cr, json& sceneData)
    : entityManager(em), componentRegistry(cr), sceneData(sceneData) {}

void ComponentEditor::display(const std::string& selectedEntityId) {
    ImGui::BeginChild("InspectorPanel", ImVec2(0,0), true, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::Text("Inspector");
    ImGui::Separator();

    if (!selectedEntityId.empty()) {
        json& selectedEntity = sceneData[selectedEntityId];
        for (auto& [componentName, componentData] : selectedEntity.items()) {
            drawJsonNode(componentData, componentName);
        }
        forceCollapseHeaders = false;
    } else {
        ImGui::Text("Select an entity.");
    }

    if (ImGui::Button("\xF0\x9F\x92\xBE Save")) {
        std::istringstream iss(selectedEntityId);
        std::string name; int id;
        iss >> name >> id;

        componentRegistry.loadComponents(sceneData, entityManager);
    }

    ImGui::EndChild();
}

void ComponentEditor::drawJsonNode(json& node, const std::string& name) {
    std::string label = name.empty() ? "##unnamed" : name;

    if (node.is_object()) {
        if (forceCollapseHeaders) ImGui::SetNextItemOpen(false, ImGuiCond_Always);
        if (ImGui::CollapsingHeader(label.c_str())) {
            ImGui::Indent();
            for (auto& [key, value] : node.items()) {
                drawJsonNode(value, key);
            }
            ImGui::Unindent();
        }
    } else if (node.is_array()) {
        if (ImGui::TreeNode(label.c_str())) {
            ImGui::Indent();
            int i = 0;
            for (auto& item : node) drawJsonNode(item, "[" + std::to_string(i++) + "]");
            ImGui::Unindent();
            ImGui::TreePop();
        }
    } else {
        ImGui::PushID(label.c_str());
        if (node.is_string()) {
            char buf[256];
            strncpy(buf, node.get<std::string>().c_str(), sizeof(buf));
            buf[sizeof(buf)-1] = 0;
            if (ImGui::InputText("##value", buf, sizeof(buf))) node = std::string(buf);
        } else if (node.is_number_integer()) {
            int value = node.get<int>();
            if (ImGui::InputInt("##value", &value)) node = value;
        } else if (node.is_number_float()) {
            float value = node.get<float>();
            if (ImGui::InputFloat("##value", &value)) node = value;
        } else if (node.is_boolean()) {
            bool value = node.get<bool>();
            if (ImGui::Checkbox("##value", &value)) node = value;
        } else {
            ImGui::Text("%s: %s", label.c_str(), node.dump().c_str());
        }
        ImGui::PopID();
    }
}
