#pragma once
#include <Editor/PrefabStorage.hpp>

class PrefabPanel 
{
public:
    PrefabPanel(PrefabStorage& prefabs);
    void draw();
    Prefab* getSelectedPrefab();

private:
    PrefabStorage& prefabs;
    Prefab* selectedPrefab = nullptr;
};
