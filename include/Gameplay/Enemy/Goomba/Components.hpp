#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct ChangeToGoombaNormalTag : public Component {};
struct ChangeToGoombaFlippedTag : public Component {};
struct ChangeToGoombaStompedTag : public Component {};

struct GoombaPatrol : Component
{
    GoombaPatrol() : velocity(sf::Vector2f(0, 0)) {}
    GoombaPatrol(sf::Vector2f velocity) : velocity(velocity) {}
    sf::Vector2f velocity;
};