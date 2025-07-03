#include <iostream>
#include "questionBlock.h"
using namespace std;

QuestionBlock::QuestionBlock(float x, float y, int scale, Handler *handler, UI *ui, QuestionBlockType type)
    : Block(x, y, scale, ui, BlockType::Question), originalY(y * scale), type(type),
      handler(handler), ui(ui), mushroom(nullptr), coin(nullptr)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in QuestionBlock constructor!" << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in QuestionBlock constructor!" << endl;
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
    if (state == QuestionBlockState::BeforeHit && isHit())
    {
        if (type == QuestionBlockType ::Coin)
        {
            coin = new Coin(getX(), getY() - getHeight() - getHeight() / 4, getScale(), ui);
        }
        else if (type == QuestionBlockType::Mushroom)
        {
            mushroom = new Mushroom(getX() / getScale(), getY() / getScale(), getScale(), handler, ui);
            handler->addObject(mushroom);
        }
        else if (type == QuestionBlockType::Flower)
        {
            // flower = new Flower(getX(), getY(), getScale(), ui);
        }
        else if (type == QuestionBlockType::Star)
        {
            // star = new Star(getX(), getY(), getScale(), ui);
        }
    }
    if (isHit())
    {
        state = QuestionBlockState::AfterHit;
        if (type==QuestionBlockType::Coin)
        {
            coin->tick();
        }
        
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
        if (type == QuestionBlockType::Coin)
        {
            if (coin)
                coin->render();
        }
        else if (type == QuestionBlockType::Mushroom)
        {
            if (mushroom)
                mushroom->render();
        }
        else if (type == QuestionBlockType::Flower)
        {
            // flower->render();
        }
        else if (type == QuestionBlockType::Star)
        {
            // star->render();
        }
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