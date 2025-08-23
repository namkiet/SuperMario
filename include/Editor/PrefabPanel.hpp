#pragma once
#include <Editor/PrefabStorage.hpp>

class PrefabPanel 
{
public:
    PrefabPanel(PrefabStorage& prefabs);
    void draw();
    Prefab* getSelectedPrefab();
    void drawPrefabCategory(PrefabStorage::Category category);

private:
    PrefabStorage& prefabs;
    Prefab* selectedPrefab = nullptr;
};
