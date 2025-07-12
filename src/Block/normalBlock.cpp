#include <iostream>
#include "normalBlock.h"
#include "player.h"
using namespace std;

NormalBlock::NormalBlock(float x, float y, int scale, UI *ui, sf::RenderWindow &window)
    : Block(x, y, scale, ui, window, BlockType::Normal), originalY(y * scale), debris(nullptr)
{
    if (getUI() == nullptr)
    {
        cerr << "UI is null in NormalBlock constructor!" << endl;
        return;
    }

    textures.push_back(getUI()->getTile1()[1]); // Load the texture for the normal block

    state = NormalBlockState::BeforeHit; // Initialize the state to BeforeHit
}

void NormalBlock::tick()
{
    if (timeCount > 0)
    {
        --timeCount;
        if (timeCount == 0)
        {
            setY(originalY);
        }
    }
    if (isHit() && notBroken) // Small Mario
    {
        state = NormalBlockState::AfterHit;
    }
    else if (isHit() && !notBroken && state == NormalBlockState::BeforeHit) // Large Mario
    {
        state = NormalBlockState::AfterHit;

        // Create debris when the block is hit
        debris = new Debris(getX(), getY(), getWidth(), getHeight(), getScale(), getUI(), getWindow());
    }

    if (isHit() && !notBroken && debris)
    {
        debris->tick();
    }
}

void NormalBlock::render()
{
    if (state == NormalBlockState::BeforeHit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[0]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale()); // Set the scale of the sprite
        getWindow().draw(sprite);
    }
    else if (state == NormalBlockState::AfterHit)
    {
        if (notBroken)
        {
            sf::Sprite sprite;
            sprite.setTexture(textures[0]);
            sprite.setPosition(getX(), getY());

            // Set the scale of the sprite
            sprite.setScale(getScale(), getScale());
            getWindow().draw(sprite); // Draw the normal block texture after hit
        }
        else if (!notBroken && debris)
        {
            debris->draw();
        }
    }
}

void NormalBlock::playerCollision(GameObject *object)
{
    // Only call this function in player class

    // Cast to player
    Player *player = dynamic_cast<Player *>(object);

    if (player != nullptr && player->isSmallMario())
    {
        notBroken = true;

        // Not break the block but make it a bit higher and back to normal
        setY(originalY - getHeight() / 4);
        timeCount = 10;
    }
    else if (player != nullptr && !player->isSmallMario())
    {
        notBroken = false;
    }
}

bool NormalBlock::shouldRemoveBlock()
{
    if (debris && debris->shouldRemove())
    {
        // cout<< "Debris should be removed." << endl;
        return true; // Remove the block if it has been hit and debris should be removed
    }
    return false; // Keep the block if it is not hit or debris is still visible
}

NormalBlock::~NormalBlock()
{
    if (debris != nullptr)
    {
        delete debris; // Clean up the debris object
        debris = nullptr;
    }
}