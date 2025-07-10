#pragma once
#include <ECS/Component.hpp>
#include <string>

struct BlockTag : public Component 
{
    BlockTag(const std::string& type = "Floor") : type(type) {}
    std::string type;
};