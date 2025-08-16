#pragma once
#include <imgui.h>
#include <nlohmann/json.hpp>
#include <Framework/ComponentRegistry.hpp>

using json = nlohmann::json;

class ComponentEditor {
public:
    ComponentEditor(EntityManager&, ComponentRegistry&, json&);

    void display(const std::string& selectedEntityId);

private:
    void drawJsonNode(json& node, const std::string& name);

    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    json& sceneData;
    bool forceCollapseHeaders = false;
};
