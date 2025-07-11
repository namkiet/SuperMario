#pragma once
#include <ECS/Component.hpp>
#include <string>

enum BlockType { NORMAL, QUESTION_BLOCK };

struct BlockTag : public Component 
{
    BlockTag(BlockType type = BlockType::NORMAL) : type(type) {}
    BlockType type;
};