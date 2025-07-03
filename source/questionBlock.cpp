#include <iostream>
#include "questionBlock.h"
using namespace std;

QuestionBlock::QuestionBlock(float x, float y, int width, int height, int index, int scale, UI *ui)
    : Block(x, y, width, height, index, scale, ui, BlockType::Question), originalY(y * scale)
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

    // Initialize animations
    normalQuestionBlock = Animation(15, normalQuestionBlockTextures);

    // Set the initial state and animation
    state = QuestionBlockState::BeforeHit;
    currentAnimation = normalQuestionBlock;
}

void QuestionBlock::tick()
{
    // Block::tick();
    if (timeCount > 0)
    {
        --timeCount;
        if (timeCount == 0)
        {
            setY(originalY);
        }
    }
    if (isHit())
    {
        state = QuestionBlockState::AfterHit;
    }
    currentAnimation.runAnimation();
}

void QuestionBlock::render()
{
    if (state == QuestionBlockState::BeforeHit)
    {
        currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == QuestionBlockState::AfterHit)
    {
        DrawTexturePro(questionBlockTextures[3],
                       {0.0f, 0.0f, (float)questionBlockTextures[3].width, (float)questionBlockTextures[3].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE); // Draw the hit question block texture
    }
}

void QuestionBlock::playerCollision(GameObject *object)
{
    if (state == QuestionBlockState::BeforeHit)
    {
        setY(originalY - getHeight() / 4);
        timeCount = 10;
    }
}