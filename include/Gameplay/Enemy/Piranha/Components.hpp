#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct PiranhaPatrol : Component
{
    PiranhaPatrol(float origin, float height, float phaseDuration, float delay) : phaseDuration(phaseDuration), 
                                                                    delay(delay), 
                                                                    velocity(sf::Vector2f(0, -height / phaseDuration)),
                                                                    minHeight(origin - height), 
                                                                    maxHeight(origin) {}
    sf::Vector2f velocity;
    float maxHeight;
    float minHeight;
    float phaseDuration;
    float delay;
    float timer = 0;
};