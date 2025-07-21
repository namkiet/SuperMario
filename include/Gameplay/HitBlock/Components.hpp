#pragma once
#include <ECS/Component.hpp>

struct CanHitNormalBlockTag : public Component
{
    // This tag is used to identify entities that can hit normal blocks
};

struct CanHitQuestionBlockTag : public Component
{
};

struct CanHit1UpBlockTag : public Component
{
    // This tag is used to identify entities that can hit 1-Up blocks
};

struct CanHitNormalBlock : public Component
{
    // This component is used to identify entities that can hit normal blocks
};

struct CanHitStarBlockTag : public Component
{
    // This component is used to identify entities that can hit star blocks
};

struct CanHitCoinBlockTag : public Component
{
    // This component is used to identify entities that can hit coin blocks
};