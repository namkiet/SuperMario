#include <iostream>
#include <raylib.h>
#include "player.h"
#include "block.h"
using namespace std;

const float Player::WIDTH = 16.0f;
const float Player::HEIGHT = 16.0f;

Player::Player(float x, float y, int index, int scale, Handler *handler, UI *ui)
    : GameObject(x, y, ObjectID::Player, WIDTH, HEIGHT, scale),
      handler(handler), ui(ui), index(index), playerWalkL(), playerWalkS()
{
    if (handler == nullptr)
    {
        cerr << "Handler is null in Player constructor!" << endl;
        return;
    }

    if (ui == nullptr)
    {
        cerr << "UI is null in Player constructor!" << endl;
        return;
    }

    playerTexturesLarge = ui->getMarioLarge();
    playerTexturesSmall = ui->getMarioSmall();

    if (playerTexturesLarge.empty() || playerTexturesSmall.empty())
    {
        cerr << "Player textures not loaded correctly!" << endl;
    }

    // Temporary vectors to hold textures for animations
    for (int i = 1; i < 4; ++i)
    {
        largeTemp.push_back(playerTexturesLarge[i]);
        smallTemp.push_back(playerTexturesSmall[i]);
    }

    // Initialize animations with the temporary texture vectors
    playerWalkL = Animation(5, largeTemp);
    playerWalkS = Animation(5, smallTemp);

    // Set the initial animation
    state = PlayerState::Small;                  // Start with large player
    currentPlayerTextures = playerTexturesSmall; // Start with small player textures
    currentAnimation = playerWalkS;              // Start with small player animation

    // Player forward direction
    forward = true;
}

void Player::tick()
{
    // finishedCollisionChecking = false;
    // cout<<"In Player::tick()" << endl;
    applyGravity();
    if (!isPlayingDeath)
        collision();

    setX(getX() + getVelX());
    setY(getY() + getVelY());

    currentAnimation.runAnimation();
}

void Player::render()
{
    if (isPlayingDeath)
    {
        DrawTexturePro(currentPlayerTextures[6],
                       {0.0f, 0.0f, (float)currentPlayerTextures[6].width, (float)currentPlayerTextures[6].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture}
        ++timeCount;
    }
    else if (jumped)
    {
        if (forward)
        {
            DrawTexturePro(currentPlayerTextures[5],
                           {0.0f, 0.0f, (float)currentPlayerTextures[5].width, (float)currentPlayerTextures[5].height},
                           {getX(), getY(), getWidth(), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture
        }
        else
        {
            DrawTexturePro(currentPlayerTextures[5],
                           {(float)currentPlayerTextures[5].width, 0.0f, -(float)currentPlayerTextures[5].width, (float)currentPlayerTextures[5].height},
                           {getX(), getY(), (getWidth()), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture
        }
    }
    else if (getVelX() > 0)
    {
        currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        forward = true;
    }
    else if (getVelX() < 0)
    {
        currentAnimation.drawAnimation(getX(), getY(), (float)(-getWidth()), (float)getHeight());
        forward = false;
    }
    else
    {
        if (forward)
        {
            DrawTexturePro(currentPlayerTextures[0],
                           {0.0f, 0.0f, (float)currentPlayerTextures[0].width, (float)currentPlayerTextures[0].height},
                           {getX(), getY(), getWidth(), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture}
        }
        else
        {
            DrawTexturePro(currentPlayerTextures[0],
                           {(float)currentPlayerTextures[0].width, 0.0f, -(float)currentPlayerTextures[0].width, (float)currentPlayerTextures[0].height},
                           {getX(), getY(), (getWidth()), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture
        }
    }
}
Rectangle Player::getBounds()
{
    // cout << "In Player::getBounds()" << endl;
    Rectangle bounds{
        getX() + getWidth() / 2 - getWidth() / 4,
        getY() + getHeight() / 2 + getHeight() / 4,
        getWidth() / 2,
        getHeight() / 4};
    return bounds;
}

Rectangle Player::getBoundsTop()
{
    // cout << "In Player::getBoundsTop()" << endl;
    Rectangle boundsTop{getX() + getWidth() / 2 - getWidth() / 4,
                        getY(),
                        getWidth() / 2,
                        getHeight() / 2};
    return boundsTop;
}

Rectangle Player::getBoundsRight()
{
    // cout << "In Player::getBoundsRight()" << endl;
    Rectangle boundsRight{getX() + getWidth() - 5,
                          getY() + 5,
                          5,
                          getHeight() - 10};
    return boundsRight;
}

Rectangle Player::getBoundsLeft()
{
    // cout << "In Player::getBoundsLeft()" << endl;
    Rectangle boundsLeft{getX(),
                         getY() + 5,
                         8,
                         getHeight() - 10};
    return boundsLeft;
}

void Player::showBounds()
{
    // cout << "In Player::showBounds()" << endl;
    Color color = {255, 0, 0, 255}; // Semi-transparent red color
    // DrawRectangleLines(getBounds().x, getBounds().y, getBounds().width, getBounds().height, color);
    // DrawRectangleLines(getBoundsTop().x, getBoundsTop().y, getBoundsTop().width, getBoundsTop().height, color);
    // DrawRectangleLines(getBoundsRight().x, getBoundsRight().y, getBoundsRight().width, getBoundsRight().height, color);
    // DrawRectangleLines(getBoundsLeft().x, getBoundsLeft().y, getBoundsLeft().width, getBoundsLeft().height, color);
    // DrawRectangleRec(getBounds(), color);      // Draw the main bounds rectangle
    // DrawRectangleRec(getBoundsTop(), color);   // Draw the top bounds rectangle
    // DrawRectangleRec(getBoundsRight(), color); // Draw the right bounds rectangle
    // DrawRectangleRec(getBoundsLeft(), color);  // Draw the left bounds rectangle
}

bool Player::hasJumped()
{
    // cout << "In Player::hasJumped()" << endl;
    return jumped;
}

void Player::setJump(bool jump)
{
    // cout << "In Player::setJump()" << endl;
    this->jumped = jump;
}

void Player::collision()
{
    const auto &gameObjects = handler->getGameObjects();

    for (const auto &object : gameObjects)
    {
        ObjectID id = object->getID();

        if (id == ObjectID::Player)
        {
            // Skip collision detection with the player itself
            continue;
        }

        if (id == ObjectID::Block)
        {
            blockCollision(object);
        }

        if (id == ObjectID::Pipe)
        {
            pipeCollision(object);
        }

        if (id == ObjectID::Enemy)
        {
            enemyCollision(object);
        }
    }
}

std::vector<GameObject *> Player::getAndResetRemovedBlocks()
{
    // Return the removed blocks and reset the vector
    std::vector<GameObject *> temp;

    for (auto &block : removedBlocks)
    {
        Block *removeBlock = dynamic_cast<Block *>(block);
        if (removeBlock == nullptr || !removeBlock->shouldRemoveBlock())
        {
            continue; // Skip to the next block if it should not be removed
        }

        temp.push_back(block);
        auto it = std::find(removedBlocks.begin(), removedBlocks.end(), block);
        if (it != removedBlocks.end())
        {
            it = removedBlocks.erase(it); // Remove the block from the removedBlocks vector
        }
    }
    return temp;
}

void Player::blockCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    auto it = std::find(removedBlocks.begin(), removedBlocks.end(), object);
    if (it != removedBlocks.end())
    {
        // If the object is in the removed blocks list, skip collision detection
        return;
    }

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    Block *block = dynamic_cast<Block *>(object);

    if (CheckCollisionRecs(boundsTop, objectBoundsBottom) && getVelY() < 0 && jumped)
    {
        // cout << "Address of the pointer: " << object << endl;
        // DrawText("Player hits the block from the top!", 10, 10, 20, RED);
        setY(object->getY() + object->getHeight());
        setVelY(0);

        if (block != nullptr)
        {
            // cout << "Block hit detected!" << endl;
            block->setHit(); // Safely call setHit() on the Block object
        }
        else
        {
            cerr << "Error: Object is not a Block!" << endl;
        }

        if (block != nullptr && block->getBlockID() == BlockType::Question)
        {
            block->playerCollision(this); // Handle question block collision
        }
        else if (block != nullptr && block->getBlockID() == BlockType::Normal)
        {
            if (state == PlayerState::Small)
            {
                // cout << "Here" << endl;
                block->playerCollision(this);
            }
            else if (state == PlayerState::Large)
            {
                // cout << "Here 2" << endl;
                removedBlocks.push_back(object); // Add to removed blocks}
            }
        }
        else if (block != nullptr && block->getBlockID() == BlockType::Coin)
        {
            // cout << "Coin block hit detected!" << endl;
            block->playerCollision(this);
        }
        else if (block != nullptr && block->getBlockID() == BlockType::Star)
        {
            // cout << "Star block hit detected!" << endl;
            block->playerCollision(this);
        }
        else
        {
            removedBlocks.push_back(object); // Add to removed blocks
        }

        // Reset the jump state
        // jumped = false;
    }
    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        // Check for collision with the bottom bounds of the block
        // DrawText("Player hits the block from the bottom!", 10, 10, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0);

        jumped = false;
    }
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft) && getVelX() > 0)
    {
        // Check for collision with the right bounds of the block
        // DrawText("Player hits the block from the right!", 10, 10, 20, RED);
        setX(object->getX() - getWidth());
    }
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight) && getVelX() < 0)
    {
        // Check for collision with the left bounds of the block
        // DrawText("Player hits the block from the left!", 10, 10, 20, RED);
        setX(object->getX() + object->getWidth());
    }
}

void Player::pipeCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    if (CheckCollisionRecs(boundsTop, objectBoundsBottom))
    {
        // DrawText("Player hits the pipe from the bottom", 10, 30, 20, RED);
        setY(object->getY() + object->getHeight());
        setVelY(0);
        // jumped = false;
    }

    // Check for collision with the top bounds of the object
    if (CheckCollisionRecs(boundsBottom, objectBoundsTop) && getVelY() > 0)
    {
        // DrawText("Player hits the pipe from the top!", 10, 50, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0);
        jumped = false;
    }

    // Check for collision with the right bounds of the object
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft) && getVelX() > 0)
    {
        // DrawText("Player hits the pipe from the right!", 10, 70, 20, RED);
        // DrawText("Right collision detected!", 10, 70, 20, RED);
        setX(object->getX() - getWidth());
    }

    // Check for collision with the left bounds of the object
    if (CheckCollisionRecs(getBoundsLeft(), object->getBoundsRight()) && getVelX() < 0)
    {
        // DrawText("Player hits the pipe from the left!", 10, 10, 20, RED);
        setX(object->getX() + object->getWidth());
    }
}

void Player::enemyCollision(GameObject *object)
{
    // For update the mode

    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    Enemy *enemy = dynamic_cast<Enemy *>(object);

    if ((CheckCollisionRecs(boundsRight, objectBoundsLeft) || CheckCollisionRecs(boundsLeft, objectBoundsRight)) && !object->isDead() && !object->isStomped())
    {
        if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Goomba)
        {
            isPlayingDeath = true; // Player is dead
            setY(getY() - getHeight());
            setVelY(0);
        }
        else if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa)
        {
            if (!enemy->isShell())
            {
                isPlayingDeath = true; // Player is dead
                setY(getY() - getHeight());
                setVelY(0);
            }
            else
            {
            }
        }
    }
    else if (CheckCollisionRecs(boundsBottom, objectBoundsTop) && getVelY() > 0 && !isPlayingDeath)
    {
        // Set the player on the ground
        Enemy *enemy = dynamic_cast<Enemy *>(object);

        // Goomba
        if (enemy->getEnemyID() == EnemyCharacter::Goomba)
        {
            setY(object->getY() + object->getHeight() - getHeight());
            setVelY(0);
        }

        // Koopa
        else if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa)
        {
            if (!object->isStomped())
            {
                cout << "The order that i expected: 2" << endl;
                setY(object->getY() - getHeight() - getHeight() / 4);
                setVelY(-8.0f);

                // Freeze the Koopa shell
                // object->setVelX(0.0f);
                // object->setVelY(0.0f);

                // Allow enemy to update collision
                finishedCollisionChecking = true;
            }
            else
            {
                cout << "The order that i expected: 4. It should only be when the Koopa shell is hit!" << endl;
                setY(object->getY() + object->getHeight() / 2 - getHeight());
            }
        }

        object->collision();

        // Find and push to the removedEnemies vector if not already present
        if (std::find(removedEnemies.begin(), removedEnemies.end(), object) == removedEnemies.end())
        {
            removedEnemies.push_back(object);
        }

        // Make the player not jump anymore
        jumped = false;
    }
}

std::vector<GameObject *> Player::getAndResetRemovedEnemies()
{
    // Return the removed enemies and reset the vector
    std::vector<GameObject *> temp;

    for (auto &enemy : removedEnemies)
    {
        Enemy *removedEnemyPointer = dynamic_cast<Enemy *>(enemy);
        if (removedEnemyPointer == nullptr || !removedEnemyPointer->shouldRemove())
        {
            continue;
        }
        // cout << "In Player::getAndResetRemovedEnemies()" << endl;
        temp.push_back(enemy);
        auto it = std::find(removedEnemies.begin(), removedEnemies.end(), enemy);
        if (it != removedEnemies.end())
        {
            it = removedEnemies.erase(it); // Remove the enemy from the removedEnemies vector
        }
    }
    return temp;
}

bool Player::isDead()
{
    if (isPlayingDeath && timeCount > 20)
        return true;
    return false;
}

bool Player::isStomped()
{
    // This method is used to synchronize with the GameObject class
    return isPlayingDeath;
}

bool Player::playerFinishedCollisionChecking()
{
    // cout << "In Player::playerFinishedCollisionChecking()" << endl;
    return finishedCollisionChecking;
}

void Player::setPlayerFinishedCollisionChecking(bool finished)
{
    // cout << "In Player::setPlayerFinishedCollisionChecking()" << endl;
    finishedCollisionChecking = finished;
}

bool Player::isSmallMario()
{
    // cout << "In Player::isSmallMario()" << endl;
    return state == PlayerState::Small;
}