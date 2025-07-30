#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct PiranhaPatrol : Component
{
    PiranhaPatrol(float height, float phaseDuration, float delay) : phaseDuration(phaseDuration), 
                                                                    delay(delay), 
                                                                    velocity(sf::Vector2f(0, -height / phaseDuration)) {}
    sf::Vector2f velocity;
    float phaseDuration;
    float delay;
    float timer = 0;
};