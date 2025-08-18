#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_set>

using json = nlohmann::json;

class EntityInspector {
public:
    EntityInspector();
    void draw(json& j);
    bool hasUpdated() const;

private:
    void drawJson(json& value, const std::string& key);
    bool updated = false;
    std::unordered_set<std::string> basicFields;
};
