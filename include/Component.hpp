#pragma once

class Component
{
public:
    virtual ~Component() = default;
};

class PlayerTag : public Component {};
class EnemyTag : public Component {};

class Solid : public Component {};