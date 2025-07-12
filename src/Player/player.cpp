#include <iostream>
#include "player.h"
#include "block.h"
#include "item.h"
#include "fire.h"
#include "koopa.h"
#include "background.h"
using namespace std;

const float Player::WIDTH = 16.0f;
const float Player::HEIGHT = 16.0f;

Player::Player(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window, PlayerID id,
               PlayerType type, PlayerState state)
    : GameObject(x, y, ObjectID::Player, WIDTH, HEIGHT, scale, window, ui), handler(handler), originalScale(scale), originalHeight(HEIGHT)
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

    // Load player textures from UI
    LoadPlayerTextures();
    LoadRandomTextures();

    // Set the player ID, state and type
    setPlayerID(id);
    setState(state);
    setType(type);

    // Player forward direction
    forward = true;
}

void Player::tick()
{
    --timeCountForRandomTextures;
    --timeCountForGrowingUp;
    --timeCountForFire;
    --timeCountForStar;

    // For flower item
    if (type == PlayerType::RandomBeforeFire && timeCountForRandomTextures <= 0) // For flower
    {
        setType(PlayerType::Fire);
        timeCountForRandomTextures = 0;
        isLocked = false;
    }
    // For star item
    else if (type == PlayerType::RandomBeforeStar && timeCountForRandomTextures <= 0)
    {
        isLocked = false;
        timeCountForStar = 500; // Begin the timer for star mode
        type = PlayerType::Star;
    }
    else if (type == PlayerType::Star && timeCountForStar <= 0)
    {
        setType(previousType); // Set to previous type
        timeCountForRandomTextures = 0;
    }

    // For mushroom item
    else if (state == PlayerState::GrowingUp && getHeight() < originalHeight * 2 * originalScale && timeCountForGrowingUp <= 0)
    {
        // Set the player to growing up state
        setState(PlayerState::GrowingUp); // Continue growing up
        timeCountForGrowingUp = 15;       // Reset the timer for growing up
    }
    else if (state == PlayerState::GrowingUp && getHeight() >= originalHeight * 2 * originalScale)
    {
        // Stop the power-up music
        getUI()->getPowerUpSound().stop();

        // Increase the background music
        getUI()->getOverworldBackGroundMusic().setVolume(100.0f);

        // Set the player to large state
        setState(PlayerState::Large);

        isLocked = false;
    }

    // cout << "Current vel X: " << getVelX() << endl;
    applyGravity();

    if (!isPlayingDeath)
        collision();

    setX(getX() + getVelX());
    setY(getY() + getVelY());

    currentAnimation->runAnimation();
}

void Player::render()
{
    if (isPlayingDeath)
    {
        // if Mario is large, turn to small Mario
        // if Mario is small, die
        if (state == PlayerState::Large)
        {
            setState(PlayerState::Small);
            setType(PlayerType::Normal);
            sf::Sprite sprite;
            sprite.setTexture(idleTexture);
            sprite.setPosition(getX(), getY());
            float scaleX = getWidth() / idleTexture.getSize().x;
            float scaleY = getHeight() / idleTexture.getSize().y;
            if (forward)
            {
                sprite.setOrigin(0, 0); // Top-left
                sprite.setScale(scaleX, scaleY);
            }
            else
            {
                sprite.setOrigin(idleTexture.getSize().x, 0); // Top-right
                sprite.setScale(-scaleX, scaleY);
            }
            getWindow().draw(sprite); // Draw small player texture
            isPlayingDeath = false;
        }
        else
        {
            sf::Sprite sprite;
            sprite.setTexture(deadTexture);
            sprite.setPosition(getX(), getY());
            float scaleX = getWidth() / deadTexture.getSize().x;
            float scaleY = getHeight() / deadTexture.getSize().y;
            sprite.setScale(scaleX, scaleY);
            getWindow().draw(sprite); // Draw small player texture
            ++timeCountForDeath;
        }
    }
    else if (type == PlayerType::Win)
    {
        if (previousType == PlayerType::Fire)
        {
            // cout << "Drawing fire mode win texture" << endl;
            sf::Sprite sprite;
            sprite.setTexture(currentPlayerTextures[2]);
            sprite.setPosition(getX(), getY());
            float scaleX = getWidth() / currentPlayerTextures[2].getSize().x;
            float scaleY = getHeight() / currentPlayerTextures[2].getSize().y;
            sprite.setScale(scaleX, scaleY);
            getWindow().draw(sprite); // Draw win texture
        }
        else if (previousType == PlayerType::Normal && id == PlayerID::Luigi)
        {
            // cout << "Drawing Luigi win texture" << endl;
            sf::Sprite sprite;
            sprite.setTexture(currentPlayerTextures[1]);
            sprite.setPosition(getX(), getY());
            float scaleX = getWidth() / currentPlayerTextures[1].getSize().x;
            float scaleY = getHeight() / currentPlayerTextures[1].getSize().y;
            sprite.setScale(scaleX, scaleY);
            getWindow().draw(sprite); // Draw win texture
        }
        else if (previousType == PlayerType::Normal && id == PlayerID::Mario)
        {
            sf::Sprite sprite;
            sprite.setTexture(currentPlayerTextures[0]);
            sprite.setPosition(getX(), getY());
            float scaleX = getWidth() / currentPlayerTextures[0].getSize().x;
            float scaleY = getHeight() / currentPlayerTextures[0].getSize().y;
            sprite.setScale(scaleX, scaleY);
            getWindow().draw(sprite); // Draw win texture
        }
    }
    else if (jumped)
    {
        if (forward)
        {
            if (type == PlayerType::Star)
            {
                // cout << "Drawing star mode jump texture" << endl;
                if (state == PlayerState::Large)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode large jump
                    currentAnimation = new Animation(1, starModeLargeTexturesJump, getWindow());
                    currentAnimation->reset();
                    currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
                    if (timeCountForRandomTextures > 0)
                    {
                        // Delete the previous animation if it exists
                        if (currentAnimation)
                            delete currentAnimation;

                        // Create a new animation for star mode large walk
                        currentAnimation = new Animation(1, starModeLargeTexturesWalk, getWindow()); // Reset to normal star mode textures
                    }
                }
                else if (state == PlayerState::Small)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode small jump
                    currentAnimation = new Animation(1, starModeSmallTexturesJump, getWindow());
                    currentAnimation->reset();
                    currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());

                    if (timeCountForRandomTextures > 0)
                    {
                        // Delete the previous animation if it exists
                        if (currentAnimation)
                            delete currentAnimation;

                        // Create a new animation for star mode small walk
                        currentAnimation = new Animation(1, starModeSmallTexturesWalk, getWindow()); // Reset to normal star mode textures
                    }
                }
            }
            else
            {
                sf::Sprite sprite;
                sprite.setTexture(jumpTexture);
                sprite.setPosition(getX(), getY());
                float scaleX = getWidth() / jumpTexture.getSize().x;
                float scaleY = getHeight() / jumpTexture.getSize().y;
                sprite.setScale(scaleX, scaleY);
                getWindow().draw(sprite); // Draw small player texture
            }
        }
        else
        {
            if (type == PlayerType::Star)
            {
                if (state == PlayerState::Large)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode large jump
                    currentAnimation = new Animation(1, starModeLargeTexturesJump, getWindow());
                    currentAnimation->reset();
                    currentAnimation->drawAnimation(getX(), getY(), -(float)getWidth(), (float)getHeight());

                    if (timeCountForRandomTextures > 0)
                    {
                        // Delete the previous animation if it exists
                        if (currentAnimation)
                            delete currentAnimation;

                        // Create a new animation for star mode large walk
                        currentAnimation = new Animation(1, starModeLargeTexturesWalk, getWindow()); // Reset to normal star mode textures
                    }
                }
                else if (state == PlayerState::Small)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode small jump
                    currentAnimation = new Animation(1, starModeSmallTexturesJump, getWindow());
                    currentAnimation->reset();
                    currentAnimation->drawAnimation(getX(), getY(), -(float)getWidth(), (float)getHeight());

                    if (timeCountForRandomTextures > 0)
                    {
                        // Delete the previous animation if it exists
                        if (currentAnimation)
                            delete currentAnimation;

                        // Create a new animation for star mode small walk
                        currentAnimation = new Animation(1, starModeSmallTexturesWalk, getWindow()); // Reset to normal star mode textures
                    }
                }
            }
            else
            {
                sf::Sprite sprite;
                sprite.setTexture(jumpTexture);
                sprite.setPosition(getX(), getY());
                sprite.setOrigin(jumpTexture.getSize().x, 0); // Set origin to top-right
                float scaleX = -getWidth() / jumpTexture.getSize().x;
                float scaleY = getHeight() / jumpTexture.getSize().y;
                sprite.setScale(scaleX, scaleY);
                getWindow().draw(sprite); // Draw small player texture
            }
        }
    }
    else if (getVelX() > 0)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        forward = true;
    }
    else if (getVelX() < 0)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)(-getWidth()), (float)getHeight());
        forward = false;
    }
    else if (type == PlayerType::RandomBeforeFire || type == PlayerType::RandomBeforeStar)
    {
        if (forward || getVelX() > 0)
            currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        else if (!forward || getVelX() < 0)
            currentAnimation->drawAnimation(getX(), getY(), (float)(-getWidth()), (float)getHeight());
    }
    else
    {
        if (type == PlayerType::Star)
        {
            if (state == PlayerState::Small)
            {
                // Delete the previous animation if it exists
                if (currentAnimation)
                    delete currentAnimation;

                // Create a new animation for star mode small
                currentAnimation = new Animation(1, starModeSmallTextures, getWindow());
            }
            else if (state == PlayerState::Large)
            {
                // Delete the previous animation if it exists
                if (currentAnimation)
                    delete currentAnimation;

                // Create a new animation for star mode large
                currentAnimation = new Animation(1, starModeLargeTextures, getWindow());
            }

            currentAnimation->reset();
            if (forward)
                currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
            else
                currentAnimation->drawAnimation(getX(), getY(), (float)(-getWidth()), (float)getHeight());

            if (timeCountForStar > 0)
            {
                if (state == PlayerState::Small)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode small walk
                    currentAnimation = new Animation(1, starModeSmallTexturesWalk, getWindow()); // Reset to normal star mode textures
                }
                else if (state == PlayerState::Large)
                {
                    // Delete the previous animation if it exists
                    if (currentAnimation)
                        delete currentAnimation;

                    // Create a new animation for star mode large walk
                    currentAnimation = new Animation(1, starModeLargeTexturesWalk, getWindow()); // Reset to normal star mode textures
                }
            }
        }
        else
        {
            sf::Sprite sprite;
            sprite.setTexture(idleTexture);
            float scaleX = getWidth() / idleTexture.getSize().x;
            float scaleY = getHeight() / idleTexture.getSize().y;

            if (forward)
            {
                sprite.setOrigin(0, 0); // Top-left
                sprite.setScale(scaleX, scaleY);
            }
            else
            {

                sprite.setOrigin(idleTexture.getSize().x, 0); // Top-right
                sprite.setScale(-scaleX, scaleY);
            }
            sprite.setPosition(getX(), getY());
            getWindow().draw(sprite); // Draw small player texture
        }
    }
}

sf::FloatRect Player::getBounds()
{
    // cout << "In Player::getBounds()" << endl;
    sf::FloatRect bounds{
        getX() + getWidth() / 2 - getWidth() / 4,
        getY() + getHeight() / 2 + getHeight() / 4,
        getWidth() / 2,
        getHeight() / 4};
    return bounds;
}

sf::FloatRect Player::getBoundsTop()
{
    // cout << "In Player::getBoundsTop()" << endl;
    sf::FloatRect boundsTop{getX() + getWidth() / 2 - getWidth() / 4,
                            getY(),
                            getWidth() / 2,
                            getHeight() / 2};
    return boundsTop;
}

sf::FloatRect Player::getBoundsRight()
{
    // cout << "In Player::getBoundsRight()" << endl;
    sf::FloatRect boundsRight{getX() + getWidth() - 5,
                              getY() + 5,
                              5,
                              getHeight() - 10};
    return boundsRight;
}

sf::FloatRect Player::getBoundsLeft()
{
    // cout << "In Player::getBoundsLeft()" << endl;
    sf::FloatRect boundsLeft{getX(),
                             getY() + 5,
                             8,
                             getHeight() - 10};
    return boundsLeft;
}

bool Player::hasJumped()
{
    return jumped;
}

void Player::setJump(bool jump)
{
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

        if (id == ObjectID::Item)
        {
            itemCollision(object);
        }

        if (id == ObjectID::Background)
        {
            backgroundCollision(object);
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
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    auto it = std::find(removedBlocks.begin(), removedBlocks.end(), object);
    if (it != removedBlocks.end())
    {
        // If the object is in the removed blocks list, skip collision detection
        return;
    }

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Block *block = dynamic_cast<Block *>(object);

    if (boundsTop.intersects(objectBoundsBottom) && getVelY() < 0 && jumped)
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

        block->playerCollision(this); // Handle question block collision

        if (block != nullptr && block->getBlockID() == BlockType::Normal)
        {
            if (state == PlayerState::Large)
            {
                removedBlocks.push_back(object); // Add to removed blocks}
            }
        }

        // Reset the jump state
        // jumped = false;
    }
    if (boundsBottom.intersects(objectBoundsTop))
    {
        if (block && block->getBlockID() == BlockType::Flag)
        {
            setType(previousType); // Set to previous type
            setVelX(4.0f);
            setX(object->getX() + object->getWidth() + object->getWidth() / 2);
        }
        else
        {
            setY(object->getY() - getHeight());
            setVelY(0);
        }

        jumped = false;
        GameObject::collision();
    }
    if (boundsRight.intersects(objectBoundsLeft) && getVelX() > 0)
    {
        // Check for collision with the right bounds of the block
        // DrawText("Player hits the block from the right!", 10, 10, 20, RED);

        setX(object->getX() - getWidth());
    }
    if (boundsLeft.intersects(objectBoundsRight) && getVelX() < 0)
    {
        // Check for collision with the left bounds of the block
        // DrawText("Player hits the block from the left!", 10, 10, 20, RED);

        setX(object->getX() + object->getWidth());
    }
}

void Player::pipeCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    if (boundsTop.intersects(objectBoundsBottom))
    {
        // DrawText("Player hits the pipe from the bottom", 10, 30, 20, RED);
        setY(object->getY() + object->getHeight());
        setVelY(0);
        // jumped = false;
    }

    // Check for collision with the top bounds of the object
    if (boundsBottom.intersects(objectBoundsTop) && getVelY() > 0)
    {
        // DrawText("Player hits the pipe from the top!", 10, 50, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0);
        jumped = false;
    }

    // Check for collision with the right bounds of the object
    if (boundsRight.intersects(objectBoundsLeft) && getVelX() > 0)
    {
        // DrawText("Player hits the pipe from the right!", 10, 70, 20, RED);
        // DrawText("Right collision detected!", 10, 70, 20, RED);
        setX(object->getX() - getWidth());
    }

    // Check for collision with the left bounds of the object
    if (boundsLeft.intersects(objectBoundsRight) && getVelX() < 0)
    {
        // DrawText("Player hits the pipe from the left!", 10, 10, 20, RED);
        setX(object->getX() + object->getWidth());
    }
}

void Player::enemyCollision(GameObject *object)
{
    // For update the mode

    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Enemy *enemy = dynamic_cast<Enemy *>(object);

    if ((boundsRight.intersects(objectBoundsLeft) || boundsLeft.intersects(objectBoundsRight)) && !object->isDead())
    {
        if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Goomba && !object->isStomped())
        {
            isPlayingDeath = true; // Player is dead
            setY(getY() - getHeight());
            setVelY(0);
        }
        else if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa)
        {
            Koopa *koopa = dynamic_cast<Koopa *>(object);
            if (koopa && (koopa->getState() == KoopaState::Normal || koopa->getState() == KoopaState::ShellMoving))
            {
                isPlayingDeath = true;
                setY(getY() - getHeight());
                setVelY(0);

                koopa->playerCollision(0); // Nothing happens with koopa
            }
            else if (koopa && koopa->getState() == KoopaState::Shell)
            {
                isPlayingDeath = false;

                koopa->playerCollision(2);
            }
        }
    }
    else if (boundsBottom.intersects(objectBoundsTop) && getVelY() > 0 && !isPlayingDeath)
    {
        // Set the player on the ground
        Enemy *enemy = dynamic_cast<Enemy *>(object);

        // Goomba
        if (enemy->getEnemyID() == EnemyCharacter::Goomba)
        {
            setY(object->getY() + object->getHeight() - getHeight());
            setVelY(0);
            object->collision();
        }

        // Koopa
        else if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa)
        {
            Koopa *koopa = dynamic_cast<Koopa *>(object);
            if (koopa && (koopa->getState() == KoopaState::Normal || koopa->getState() == KoopaState::ShellMoving))
            {
                //  << "In Player::enemyCollision() - Koopa in normal or shell moving state" << endl;

                // Wont dead
                isPlayingDeath = false;

                // Set the position
                setY(object->getY() - getHeight() - getHeight() / 4);

                // Set the velocity
                setVelY(-8.0f);

                // Call playerCollision in koopa class
                koopa->playerCollision(1);

                return;
            }
            else if (koopa && koopa->getState() == KoopaState::Shell)
            {
                isPlayingDeath = false;
                // cout << "In Player::enemyCollision() - Koopa in shell state" << endl;
                koopa->playerCollision(2);
                return;
            }
        }

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
    if (isPlayingDeath && timeCountForDeath > 20)
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

void Player::setState(PlayerState newState)
{
    state = newState;
    if (state == PlayerState::Large)
    {
        // setHeight(2 * originalHeight);
        setPlayerScale(2 * originalScale);
        // cout << getX() << endl;
        // cout << getY() << endl;
        // cout << getWidth() << endl;
        // cout << getHeight() << endl;
        // cout << getScale() << endl;
    }
    else if (state == PlayerState::GrowingUp)
    {
        float newScale = getPlayerScale() + 0.5f;
        float newHeight = getHeight() * (newScale / getPlayerScale());

        if (newHeight <= originalHeight * 2 * originalScale)
        {
            setPlayerScale(newScale);
        }
    }
    else if (state == PlayerState::Small)
    {
        setPlayerScale(originalScale);
    }
    else if (type == PlayerType::Win)
    {
        if (getVelY() == 0)
            setVelX(2.0f);
    }
}

void Player::setType(PlayerType newType)
{
    type = newType;
    currentPlayerTextures.clear(); // Always clear before repopulating!
    switch (type)
    {
    case PlayerType::Normal:
        for (int i = 1; i < 4; ++i)
        {
            if (id == PlayerID::Mario)
            {
                if (state == PlayerState::Small)
                {
                    currentPlayerTextures.push_back(normalMarioSmallTextures[i]);
                }
                else if (state == PlayerState::Large || state == PlayerState::GrowingUp)
                {
                    currentPlayerTextures.push_back(normalMarioLargeTextures[i]);
                }
            }
            else if (id == PlayerID::Luigi)
            {
                if (state == PlayerState::Small)
                {
                    currentPlayerTextures.push_back(normalLuigiSmallTextures[i]);
                }
                else if (state == PlayerState::Large || state == PlayerState::GrowingUp)
                {
                    currentPlayerTextures.push_back(normalLuigiLargeTextures[i]);
                }
            }
        }
        if (state == PlayerState::Small && id == PlayerID::Mario)
        {
            idleTexture = normalMarioSmallTextures[0];
            jumpTexture = normalMarioSmallTextures[5];
            deadTexture = normalMarioSmallTextures[6];
        }
        else if (state == PlayerState::Large && id == PlayerID::Mario)
        {
            idleTexture = normalMarioLargeTextures[0];
            jumpTexture = normalMarioLargeTextures[5];
            deadTexture = normalMarioLargeTextures[6];
        }
        else if (state == PlayerState::Small && id == PlayerID::Luigi)
        {
            idleTexture = normalLuigiSmallTextures[0];
            jumpTexture = normalLuigiSmallTextures[5];
            deadTexture = normalLuigiSmallTextures[6];
        }
        else if (state == PlayerState::Large && id == PlayerID::Luigi)
        {
            idleTexture = normalLuigiLargeTextures[0];
            jumpTexture = normalLuigiLargeTextures[5];
            deadTexture = normalLuigiLargeTextures[6];
        }
        else if (state == PlayerState::GrowingUp && id == PlayerID::Mario)
        {
            idleTexture = normalMarioLargeTextures[0];
            jumpTexture = normalMarioLargeTextures[5];
            deadTexture = normalMarioLargeTextures[6];
        }
        else if (state == PlayerState::GrowingUp && id == PlayerID::Luigi)
        {
            idleTexture = normalLuigiLargeTextures[0];
            jumpTexture = normalLuigiLargeTextures[5];
            deadTexture = normalLuigiLargeTextures[6];
        }
        break;

    case PlayerType::Fire:
        for (int i = 1; i < 4; ++i)
        {
            currentPlayerTextures.push_back(fireLargeTextures[i]);
        }
        idleTexture = fireLargeTextures[0];
        jumpTexture = fireLargeTextures[5];
        deadTexture = fireLargeTextures[6];
        break;

    case PlayerType::Star:
        if (state == PlayerState::Small)
        {
            currentPlayerTextures = starModeSmallTexturesWalk;
            // idleTexture = starModeSmallTextures[0];
            // jumpTexture = starModeSmallTextures[5];
            // deadTexture = starModeSmallTextures[6]; // wont died in this mode
        }
        else if (state == PlayerState::Large)
        {
            currentPlayerTextures = starModeLargeTexturesWalk;
            // idleTexture = starModeLargeTextures[0];
            // jumpTexture = starModeLargeTextures[5];
            // deadTexture = starModeLargeTextures[6]; // wont died in this mode
        }
    case PlayerType::Win:
        if (state == PlayerState::Small)
            currentPlayerTextures = winSmallTextures;
        else if (state == PlayerState::Large)
            currentPlayerTextures = winLargeTextures;
    default:
        cerr << "Unknown player type!" << endl;
    }
    if (type == PlayerType::Star)
    {
        // Delete the previous animation if it exists
        if (currentAnimation)
            delete currentAnimation;

        // Create a new animation for star mode
        currentAnimation = new Animation(1, currentPlayerTextures, getWindow());
    }
    else
    {
        // Delete the previous animation if it exists
        if (currentAnimation)
            delete currentAnimation;

        // Create a new animation for normal or fire mode
        currentAnimation = new Animation(5, currentPlayerTextures, getWindow());
    }
    currentAnimation->reset();
}

void Player::setPlayerID(PlayerID newID)
{
    id = newID;
}

void Player::LoadPlayerTextures()
{
    if (getUI() == nullptr)
    {
        cerr << "UI is null in LoadPlayerTextures!" << endl;
        return;
    }
    // Load player textures from UI
    normalMarioLargeTextures = getUI()->getMarioLarge();
    normalMarioSmallTextures = getUI()->getMarioSmall();
    normalLuigiLargeTextures = getUI()->getLuigiLarge();
    normalLuigiSmallTextures = getUI()->getLuigiSmall();
    fireLargeTextures = getUI()->getFireLarge();
    fireSmallTextures = getUI()->getFireSmall();
}

void Player::LoadRandomTextures()
{
    if (getUI() == nullptr)
    {
        cerr << "UI is null in LoadRandomTextures!" << endl;
        return;
    }
    // Load random textures for player animations
    for (int i = 0; i < 7; ++i)
    {
        if (i == 0) // Idle -> 0
        {
            randomTextures1.push_back(getUI()->getFireLarge()[i]);
            randomTextures1.push_back(getUI()->getRedLarge()[i]);
            randomTextures1.push_back(getUI()->getBlackLarge()[i]);
            randomTextures1.push_back(getUI()->getGreenLarge()[i]);
            randomTextures1.push_back(getUI()->getBlueLarge()[i]);

            starModeLargeTextures.push_back(getUI()->getFireLarge()[i]);
            starModeLargeTextures.push_back(getUI()->getRedLarge()[i]);
            starModeLargeTextures.push_back(getUI()->getBlackLarge()[i]);
            starModeLargeTextures.push_back(getUI()->getGreenLarge()[i]);
            starModeLargeTextures.push_back(getUI()->getBlueLarge()[i]);

            starModeSmallTextures.push_back(getUI()->getFireSmall()[i]);
            starModeSmallTextures.push_back(getUI()->getRedSmall()[i]);
            starModeSmallTextures.push_back(getUI()->getBlackSmall()[i]);
            starModeSmallTextures.push_back(getUI()->getGreenSmall()[i]);
            starModeSmallTextures.push_back(getUI()->getBlueSmall()[i]);
        }
        else if (i == 1) // Walk1 -> 1
        {
            randomTextures2.push_back(getUI()->getFireLarge()[i]);
            randomTextures2.push_back(getUI()->getRedLarge()[i]);
            randomTextures2.push_back(getUI()->getBlackLarge()[i]);
            randomTextures2.push_back(getUI()->getGreenLarge()[i]);
            randomTextures2.push_back(getUI()->getBlueLarge()[i]);

            starModeLargeTexturesWalk.push_back(getUI()->getFireLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getRedLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlackLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getGreenLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlueLarge()[i]);

            starModeSmallTexturesWalk.push_back(getUI()->getFireSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getRedSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlackSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getGreenSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlueSmall()[i]);
        }
        else if (i == 2) // Walk2 -> 2
        {
            randomTextures3.push_back(getUI()->getFireLarge()[i]);
            randomTextures3.push_back(getUI()->getRedLarge()[i]);
            randomTextures3.push_back(getUI()->getBlackLarge()[i]);
            randomTextures3.push_back(getUI()->getGreenLarge()[i]);
            randomTextures3.push_back(getUI()->getBlueLarge()[i]);

            starModeLargeTexturesWalk.push_back(getUI()->getFireLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getRedLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlackLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getGreenLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlueLarge()[i]);

            starModeSmallTexturesWalk.push_back(getUI()->getFireSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getRedSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlackSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getGreenSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlueSmall()[i]);
        }
        else if (i == 3) // Walk3 -> 3
        {
            randomTextures4.push_back(getUI()->getFireLarge()[i]);
            randomTextures4.push_back(getUI()->getRedLarge()[i]);
            randomTextures4.push_back(getUI()->getBlackLarge()[i]);
            randomTextures4.push_back(getUI()->getGreenLarge()[i]);
            randomTextures4.push_back(getUI()->getBlueLarge()[i]);

            starModeLargeTexturesWalk.push_back(getUI()->getFireLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getRedLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlackLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getGreenLarge()[i]);
            starModeLargeTexturesWalk.push_back(getUI()->getBlueLarge()[i]);

            starModeSmallTexturesWalk.push_back(getUI()->getFireSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getRedSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlackSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getGreenSmall()[i]);
            starModeSmallTexturesWalk.push_back(getUI()->getBlueSmall()[i]);
        }
        else if (i == 4) // Walk4 -> 4
        {
            randomTextures5.push_back(getUI()->getFireLarge()[i]);
            randomTextures5.push_back(getUI()->getRedLarge()[i]);
            randomTextures5.push_back(getUI()->getBlackLarge()[i]);
            randomTextures5.push_back(getUI()->getGreenLarge()[i]);
            randomTextures5.push_back(getUI()->getBlueLarge()[i]);
        }
        else if (i == 5) // Jumping -> 5
        {
            randomTextures6.push_back(getUI()->getFireLarge()[i]);
            randomTextures6.push_back(getUI()->getRedLarge()[i]);
            randomTextures6.push_back(getUI()->getBlackLarge()[i]);
            randomTextures6.push_back(getUI()->getGreenLarge()[i]);
            randomTextures6.push_back(getUI()->getBlueLarge()[i]);

            starModeLargeTexturesJump.push_back(getUI()->getBlackLarge()[i]);
            starModeLargeTexturesJump.push_back(getUI()->getFireLarge()[i]);
            starModeLargeTexturesJump.push_back(getUI()->getRedLarge()[i]);
            starModeLargeTexturesJump.push_back(getUI()->getGreenLarge()[i]);
            starModeLargeTexturesJump.push_back(getUI()->getBlueLarge()[i]);

            starModeSmallTexturesJump.push_back(getUI()->getBlackSmall()[i]);
            starModeSmallTexturesJump.push_back(getUI()->getFireSmall()[i]);
            starModeSmallTexturesJump.push_back(getUI()->getRedSmall()[i]);
            starModeSmallTexturesJump.push_back(getUI()->getGreenSmall()[i]);
            starModeSmallTexturesJump.push_back(getUI()->getBlueSmall()[i]);
        }
        else if (i == 6) // Flag pole
        {
            winLargeTextures.push_back(getUI()->getMarioLarge()[i + 2]);
            winLargeTextures.push_back(getUI()->getLuigiLarge()[i + 2]);
            winLargeTextures.push_back(getUI()->getFireLarge()[i + 2]);

            winSmallTextures.push_back(getUI()->getMarioSmall()[i + 2]);
            winSmallTextures.push_back(getUI()->getLuigiSmall()[i + 2]);
        }
    }
}

void Player::itemCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds();
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Item *item = dynamic_cast<Item *>(object);

    if ((boundsTop.intersects(objectBoundsBottom) || boundsBottom.intersects(objectBoundsTop) ||
         boundsLeft.intersects(objectBoundsRight) || boundsRight.intersects(objectBoundsLeft)) &&
        !object->isStomped())
    {
        if (item->getItemType() == ItemType::Star)
        {
            // Reset the timer
            timeCountForRandomTextures = 100;

            // Random texture first
            int randomIndex = currentAnimation->getCurrentFrameIndex();
            setRandomTextures(randomIndex);

            // Store the previous type
            previousType = type;

            // Set type
            type = PlayerType::RandomBeforeStar;

            // Set the velocity to 0
            setVelX(0.0f);
            setVelY(0.0f);

            // Lock for a while
            isLocked = true;
        }
        else if (item->getItemType() == ItemType::Flower)
        {
            // Check the state of the player
            if (state == PlayerState::Small)
            {
                // Decrease the background music
                getUI()->getOverworldBackGroundMusic().setVolume(20.0f);

                // Play the power-up music
                getUI()->getPowerUpSound().play();

                // Set the player to the growing up state
                setState(PlayerState::GrowingUp);

                // Set the player type to normal
                setType(PlayerType::Normal);

                // Set the time count for growing up
                timeCountForGrowingUp = 15;

                // Set the velocity to 0
                setVelX(0.0f);
                setVelY(0.0f);

                // Lock the player for a while
                isLocked = true;

                return;
            }
            // Reset the timer
            timeCountForRandomTextures = 100;

            // Random texture until timer runs out
            int randomIndex = currentAnimation->getCurrentFrameIndex();
            setRandomTextures(randomIndex);

            // setState(PlayerState::Large);

            // Set type
            type = PlayerType::RandomBeforeFire;

            // Set the velocity to 0
            setVelX(0.0f);
            setVelY(0.0f);

            // Lock for a while
            isLocked = true;
        }
        else if (item->getItemType() == ItemType::Mushroom)
        {
            if (state == PlayerState::Small)
            {
                // Decrease the background music
                getUI()->getOverworldBackGroundMusic().setVolume(20.0f);

                // Play the power-up music
                getUI()->getPowerUpSound().play();

                setState(PlayerState::GrowingUp);
                setType(PlayerType::Normal);

                // Set the velocity to 0
                setVelX(0.0f);
                setVelY(0.0f);

                timeCountForGrowingUp = 15;

                isLocked = true;
            }
            else if (state == PlayerState::Large)
            {
                // Do nothing
            }
        }
        item->playerCollision();
        // cout << "Item collision detected!" << endl;
        if (std::find(removedItems.begin(), removedItems.end(), object) == removedItems.end())
        {
            removedItems.push_back(object);
        }
    }
}

std::vector<GameObject *> Player::getAndResetRemovedItems()
{
    std::vector<GameObject *> temp;

    for (auto &item : removedItems)
    {
        Item *removedItemPointer = dynamic_cast<Item *>(item);
        if (removedItemPointer == nullptr || !removedItemPointer->shouldRemoveItem())
        {
            continue; // Skip if the item is not valid or should not be removed
        }
        temp.push_back(item);
        auto it = std::find(removedItems.begin(), removedItems.end(), item);
        if (it != removedItems.end())
        {
            it = removedItems.erase(it); // Remove the item from the removeItems vector
        }
    }
    return temp;
}

void Player::setRandomTextures(int index)
{
    if (index <= 0 || index >= 4)
    {
        cerr << "Random index out of bounds!" << endl;
        return;
    }

    if (jumped)
    {
        index = 5;
    }
    else if (getVelX() != 0)
    {
        index = index;
    }
    else
    {
        index = 0; // Default to idle texture if no movement or jump
    }

    currentPlayerTextures.clear(); // Clear the current textures before setting new ones
    // Set the random textures based on the index
    switch (index)
    {
    case 0:
        currentPlayerTextures = randomTextures1;
        break;
    case 1:
        currentPlayerTextures = randomTextures2;
        break;
    case 2:
        currentPlayerTextures = randomTextures3;
        break;
    case 3:
        currentPlayerTextures = randomTextures4;
        break;
    case 4:
        currentPlayerTextures = randomTextures5;
        break;
    case 5:
        currentPlayerTextures = randomTextures6;
        break;
    default:
        cerr << "Invalid index for random textures!" << endl;
    }
    // Delete the previous animation if it exists
    if (currentAnimation)
        delete currentAnimation;

    // Create a new animation with the random textures
    currentAnimation = new Animation(5, currentPlayerTextures, getWindow());
    currentAnimation->reset();
}

void Player::fire()
{
    // cout << Fire::count << endl;

    // For the first fire bullet
    if (Fire::count >= 2)
        return;
    else if (Fire::count < 2 && timeCountForFire <= 0)
    {
        // cout << "Player position: " << getX() << " " << getY() << endl;
        fireBullet = new Fire((getX() - getWidth() / 2) / getScale(), (getY() + getHeight() / 8) / getScale(), originalScale, handler,
                              getUI(), getWindow());
        handler->addObject(fireBullet);
        timeCountForFire = 10;
        // cout << "Fire bullet 1 created" << endl;
    }
}

bool Player::isFireMario()
{
    return type == PlayerType::Fire;
}

bool Player::isPlayerLocked()
{
    return isLocked;
}

bool Player::isPlayerForward()
{
    // Check if the player is facing forward
    return forward;
}

void Player::backgroundCollision(GameObject *object)
{
    // Handle background collision if needed
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds();
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    BackGround *background = dynamic_cast<BackGround *>(object);
    if (background && background->getBackGroundID() == BackGroundType::FlagPole)
    {
        if (boundsTop.intersects(objectBoundsBottom) || boundsBottom.intersects(objectBoundsTop) ||
            boundsLeft.intersects(objectBoundsRight) || boundsRight.intersects(objectBoundsLeft))
        {
            // cout << "Player hits the flagpole!" << endl;
            // Player hits the background from the top

            // setY(object->getY() - getHeight());
            setX(object->getX() - object->getWidth() / 2);
            setVelY(4.0f);
            setVelX(0.0f);

            jumped = false;

            isLocked = true;

            if (type != PlayerType::Win)
            {
                // Only set once
                previousType = type;
            }

            setType(PlayerType::Win);

            // if (getY() > object->getY() + object->getHeight() - object->getHeight() / 8)
            // {
            //     setType(PlayerType::Normal);
            //     setVelX(2.0f);
            //     setX(object->getX() + object->getWidth() + object->getWidth() / 2);
            // }
        }
    }
}

Player::~Player()
{
    if (normalMarioWalkL)
    {
        delete normalMarioWalkL;
    }
    if (normalMarioWalkS)
    {
        delete normalMarioWalkS;
    }

    if (normalLuigiWalkL)
    {
        delete normalLuigiWalkL;
    }
    if (normalLuigiWalkS)
    {
        delete normalLuigiWalkS;
    }
    if (fireWalkL)
    {
        delete fireWalkL;
    }
    if (redWalkL)
    {
        delete redWalkL;
    }
    if (blackWalkL)
    {
        delete blackWalkL;
    }
    if (greenWalkL)
    {
        delete greenWalkL;
    }
    if (blueWalkL)
    {
        delete blueWalkL;
    }

    currentAnimation = nullptr;
    normalMarioWalkL = nullptr;
    normalMarioWalkS = nullptr;
    normalLuigiWalkL = nullptr;
    normalLuigiWalkS = nullptr;
    fireWalkL = nullptr;
    redWalkL = nullptr;
    blackWalkL = nullptr;
    greenWalkL = nullptr;
    blueWalkL = nullptr;
}