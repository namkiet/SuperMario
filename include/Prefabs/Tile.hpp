#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Tile : public Entity
{
public:
    Tile(float x, float y, const std::string& img)
    {
        addComponent<Animation>(Animation(TextureManager::load(img)));
        addComponent<BoxCollider2D>(SIZE::GRID);
        addComponent<BlockTag>();
        addComponent<Transform>(Transform(sf::Vector2f(x, y), SIZE::GRID));
    }
};