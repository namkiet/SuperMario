#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>
#include <Engine/Core/Transform.hpp>
#include <SFML/Graphics.hpp>
#include <Core/Variables.hpp>

class CameraSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        auto target = world.findFirst<FollowByCameraTag>();
        if (!target) return;

        if (!target->hasComponent<Transform>()) return;
        auto& tf = target->getComponent<Transform>();

        if (!world.findFirst<Camera>()) return;
        auto& camera = world.findFirst<Camera>()->getComponent<Camera>();

        // target pos
        const float targetCenterX = tf.position.x + 0.5f * tf.size.x;
        // cur pos
        float& camX = camera.target.x;

        // Define trap zone (dead zone margins from screen center)
        const float trapHalfWidth = 100.0f;
        const float screenCenterX = camX;

        float trapLeft = screenCenterX - trapHalfWidth;
        float trapRight = screenCenterX + trapHalfWidth;

        // Move camera only if target exits trap zone
        if (targetCenterX < trapLeft)
        {
            camX = targetCenterX + trapHalfWidth;
        }
        else if (targetCenterX > trapRight)
        {
            camX = targetCenterX - trapHalfWidth;
        }

        // Keep Y fixed (side-scroller style)
        camera.target.y = 0.5f * SIZE::SCREEN.y;
    }
};
