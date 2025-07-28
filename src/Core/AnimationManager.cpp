#include <Core/AnimationManager.hpp>
#include <Engine/Animation/Animation.hpp>
#include <stdexcept>

std::unordered_map<std::string, Animation> AnimationManager::animMap;

void AnimationManager::registerAnimation(const std::string& name, const Animation& anim)
{
    animMap[name] = anim;
}

Animation AnimationManager::load(const std::string& name)
{
    auto found = animMap.find(name);
    if (found == animMap.end())
    {
        throw std::runtime_error("Cannot load Animation: " + name);
    }
    return found->second;
}