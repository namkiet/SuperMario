#pragma once
#include <World.hpp>
#include <Components/Camera.hpp>
#include <Components/Transform.hpp>
#include <SFML/Graphics.hpp>

class CameraSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        auto& camera = world.findFirst<Camera>()->getComponent<Camera>();
        auto playerPos = world.findFirst<Transform>()->getComponent<Transform>().getPosition();
        camera.target = playerPos;
        // camera.update(dt);
    }
};
