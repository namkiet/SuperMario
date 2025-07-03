#include <iostream>
#include "questionBlock.h"
using namespace std;

QuestionBlock::QuestionBlock(float x, float y, int width, int height, int index, int scale, UI *ui)
    : Block(x, y, width, height, index, scale, ui, BlockType::Question)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in QuestionBlock constructor!" << endl;
        return;
    }

    // Load question block textures from UI
    for (int i = 24; i < 28; ++i)
    {
        questionBlockTextures.push_back(ui->getTile1()[i]);
    }

    // Temporary vectors to hold textures for animations
    std::vector<Texture2D> normalQuestionBlockTextures;
    for (int i = 0; i < 3; ++i)
    {
        normalQuestionBlockTextures.push_back(questionBlockTextures[i]);
    }

    // Temporary vectors to hold textures for hit animations
    std::vector<Texture2D> hitQuestionBlockTextures;
    for (int i = 3; i < 4; ++i)
    {
        hitQuestionBlockTextures.push_back(questionBlockTextures[i]);
    }

    // Initialize animations
    normalQuestionBlock = Animation(10, normalQuestionBlockTextures);
    hitQuestionBlock = Animation(10, hitQuestionBlockTextures);

    // Set the initial state and animation
    state = QuestionBlockState::BeforeHit;
    currentAnimation = normalQuestionBlock;
}

void QuestionBlock::tick()
{
    Block::tick();
    currentAnimation.runAnimation();
}

void QuestionBlock::render()
{
    currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
}