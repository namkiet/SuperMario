#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>
#include <Engine/Core/Transform.hpp>
#include <SFML/Graphics.hpp>
#include <Core/Variables.hpp>

class CameraSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        if (!world.findFirst<Camera>()) return;
        auto &camera = world.findFirst<Camera>()->getComponent<Camera>();

        auto target = world.findFirst<FollowByCameraTag>();
        if (!target) return;
        if (!target->hasComponent<Transform>()) return;

        auto &tf = target->getComponent<Transform>();

        // target pos
        const float targetCenterX = tf.position.x + 0.5f * tf.size.x;

        // cur pos
        float& camX = camera.target.x;
        
        float trapLeft  = camX - camera.trapHalfWidth;
        float trapRight = camX + camera.trapHalfWidth;

        float desiredCamX = camX; // start with current

        if (targetCenterX < trapLeft)
            desiredCamX = targetCenterX + camera.trapHalfWidth;
        else if (targetCenterX > trapRight)
            desiredCamX = targetCenterX - camera.trapHalfWidth;

        // Interpolate toward desired
        camX += (desiredCamX - camX) * std::min(dt * camera.smoothing, 1.0f);

        camX = std::fmax(camX, 0.5f * SIZE::SCREEN.x);

        // Keep Y fixed (side-scroller style)
        camera.target.y = 0.5f * SIZE::SCREEN.y;
    }
};
