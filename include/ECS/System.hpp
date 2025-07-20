#pragma once

// Forward Declaration
class World;

class System 
{
public:
    virtual ~System() = default;
    virtual void preUpdate(World&, float) {};
    virtual void update(World&, float) {};
    virtual void postUpdate(World&, float) {};
};