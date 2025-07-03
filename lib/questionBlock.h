#pragma once
#include "block.h"
#include "animation.h"

enum class QuestionBlockState
{
    BeforeHit,
    AfterHit
};
class QuestionBlock : public Block
{
private:
    // For animation
    QuestionBlockState state;
    Animation normalQuestionBlock;
    Animation hitQuestionBlock;
    Animation currentAnimation;

    // Question block textures
    std::vector<Texture2D> questionBlockTextures;

    // For player texture animation
    int index = 0;

public:
    // Constructor
    QuestionBlock(float x = 0, float y = 0, int width = 0, int height = 0, int index = 0, int scale = 0, UI *ui = nullptr);

    // For updating
    void tick();
    void render();

    
};