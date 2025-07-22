#pragma once
#include <unordered_map>

// Forward Declaration
class Animation;

class AnimationManager
{
public:
    static void registerAnimation(const std::string& name, const Animation& anim);
    static Animation load(const std::string& name);

private:
    static std::unordered_map<std::string, Animation> animMap;
};