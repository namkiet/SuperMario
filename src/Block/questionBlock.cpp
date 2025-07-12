#include <iostream>
#include "questionBlock.h"
using namespace std;

QuestionBlock::QuestionBlock(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window, QuestionBlockType type)
    : Block(x, y, scale, ui, window, BlockType::Question), originalY(y * scale), type(type), handler(handler), mushroom(nullptr),
      coin(nullptr), flower(nullptr), star(nullptr)
{
    if (getUI() == nullptr)
    {
        cerr << "UI is null in QuestionBlock constructor!" << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in QuestionBlock constructor!" << endl;
        return;
    }

    // cout << "In QuestionBlock constructor" << endl;
    // Load question block textures from UI
    for (int i = 24; i < 28; ++i)
    {
        questionBlockTextures.push_back(ui->getTile1()[i]);
    }

    // Temporary vectors to hold textures for animations
    std::vector<sf::Texture> normalQuestionBlockTextures;
    for (int i = 0; i < 3; ++i)
    {
        normalQuestionBlockTextures.push_back(questionBlockTextures[i]);
    }

    // Initialize animations
    normalQuestionBlock = new Animation(15, normalQuestionBlockTextures, window);

    // Set the initial state and animation
    state = QuestionBlockState::BeforeHit;
    currentAnimation = normalQuestionBlock;
}

void QuestionBlock::tick()
{
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
            coin = new Coin(getX() / getScale(), (getY() - getHeight() - getHeight() / 4) / getScale(),
                            getScale(), getUI(), getWindow());
        }
        else if (type == QuestionBlockType::Mushroom)
        {
            mushroom = new Mushroom(getX() / getScale(), getY() / getScale(), getScale(),
                                    handler, getUI(), getWindow(), MushroomType::Normal);
            handler->addObject(mushroom);
        }
        else if (type == QuestionBlockType::Flower)
        {
            if (handler->getPlayer()->isSmallMario())
            {
                mushroom = new Mushroom(getX() / getScale(), getY() / getScale(), getScale(),
                                        handler, getUI(), getWindow(), MushroomType::Normal);
                handler->addObject(mushroom);
            }
            else
            {
                flower = new Flower(getX() / getScale(), (originalY - getHeight()) / getScale(),
                                    getScale(), getUI(), getWindow());
                handler->addObject(flower);
            }
        }
        else if (type == QuestionBlockType::Star)
        {
            star = new Star(getX() / getScale(), getY() / getScale(), getScale(),
                            handler, getUI(), getWindow());
            handler->addObject(star);
        }
    }

    if (isHit())
    {
        state = QuestionBlockState::AfterHit;
        if (type == QuestionBlockType::Coin)
        {
            coin->tick();
        }
    }
    currentAnimation->runAnimation();
}

void QuestionBlock::render()
{
    if (state == QuestionBlockState::BeforeHit)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
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
            if (flower)
                flower->render();
        }
        else if (type == QuestionBlockType::Star)
        {
            if (star)
                star->render();
        }
        sf::Sprite sprite;
        sprite.setTexture(questionBlockTextures[3]);
        sprite.setPosition(getX(), getY());
        float scaleX = getWidth() / questionBlockTextures[3].getSize().x;
        float scaleY = getHeight() / questionBlockTextures[3].getSize().y;
        sprite.setScale(scaleX, scaleY); // Set the scale of the sprite

        getWindow().draw(sprite); // Draw the question block texture after hit
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

GameObject *QuestionBlock::getMushroom()
{
    return mushroom;
}

GameObject *QuestionBlock::getFlower()
{
    return flower;
}

void QuestionBlock::setMushroom()
{
    mushroom = nullptr;
}

void QuestionBlock::setFlower()
{
    flower = nullptr;
}

QuestionBlock::~QuestionBlock()
{
    if (coin)
        delete coin;
    if (mushroom)
        delete mushroom;
    if (flower)
        delete flower;
    if (star)
        delete star;

    if (currentAnimation && currentAnimation != normalQuestionBlock)
    {
        delete currentAnimation;
        currentAnimation = nullptr; // Avoid dangling pointer
    }
    if (normalQuestionBlock)
    {
        delete normalQuestionBlock;
        normalQuestionBlock = nullptr; // Avoid dangling pointer
    }

    currentAnimation = nullptr;
    normalQuestionBlock = nullptr;
}