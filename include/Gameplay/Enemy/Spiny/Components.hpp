#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

enum class Direction;

struct ChangeToSpinyNormalTag : public Component {};
struct ChangeToSpinyFlippedTag : public Component {};

struct SpinyPatrol : Component
{
    SpinyPatrol() : velocity(sf::Vector2f(0, 0)) {}
    SpinyPatrol(sf::Vector2f velocity) : velocity(velocity) {}
    sf::Vector2f velocity;
};
