#pragma once

// Forward Declaration
class World;

class System 
{
public:
    virtual ~System() = default;
    virtual void update(World&, float) = 0;
};