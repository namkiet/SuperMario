#pragma once
#include <World.hpp>
#include <Components/Camera.hpp>
#include <Components/Transform.hpp>
#include <Core/Variables.hpp>
#include <SFML/Graphics.hpp>

class CameraSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        auto player = world.findFirst<PlayerTag>();
        if (!player) return;

        auto camEntity = world.findFirst<Camera>();
        if (!camEntity) return;

        auto& camera = camEntity->getComponent<Camera>();
        auto& tf = player->getComponent<Transform>();

        const float playerCenterX = tf.position.x + 0.5f * tf.size.x;
        float& camX = camera.target.x;

        // Define trap zone (dead zone margins from screen center)
        const float trapHalfWidth = 100.0f;
        const float screenCenterX = camX;

        float trapLeft = screenCenterX - trapHalfWidth;
        float trapRight = screenCenterX + trapHalfWidth;

        // Move camera only if player exits trap zone
        if (playerCenterX < trapLeft)
        {
            camX = playerCenterX + trapHalfWidth;
        }
        else if (playerCenterX > trapRight)
        {
            camX = playerCenterX - trapHalfWidth;
        }

        // Keep Y fixed (side-scroller style)
        camera.target.y = 0.5f * SIZE::SCREEN.y;
    }
};
