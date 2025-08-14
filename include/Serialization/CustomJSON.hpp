#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <Framework/EntityManager.hpp>

inline void to_json(json& j, const Entity* entity)
{
    j = entity ? entity->getID() : -1;
}

inline void from_json(const json& j, Entity*& entity)
{
    entity = EntityManager::getEntityByID(j.get<int>());
}

#include <Engine/Physics/BoxCollider2D.hpp>

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CollisionInfo, collider, direction, overlap)