#include <iostream>
#include <cmath>
#include "koopa.h"
#include "item.h"
using namespace std;

Koopa::Koopa(float x, float y, int scale, Handler *handler, UI *ui)
    : Enemy(x, y, scale, handler, ui, EnemyCharacter::Koopa)
{
    if (handler == nullptr)
    {
        cerr << "Handler is null in Koopa constructor!" << endl;
        return;
    }

    if (ui == nullptr)
    {
        cerr << "UI is null in Koopa constructor!" << endl;
        return;
    }

    // Load koopa textures from UI
    for (int i = 3; i < 9; ++i)
    {
        koopaTextures.push_back(ui->getEnemy1()[i]);
    }

    // Initialize animation
    std::vector<Texture2D> normalKoopaTextures;
    for (int i = 0; i < 2; ++i)
    {
        normalKoopaTextures.push_back(koopaTextures[i]);
    }
    normalKoopa = Animation(2, normalKoopaTextures);

    std::vector<Texture2D> shellKoopaTextures;
    for (int i = 4; i < 6; ++i)
    {
        shellKoopaTextures.push_back(koopaTextures[i]);
    }
    shellKoopa = Animation(2, shellKoopaTextures);

    // Set the initial animation
    state = KoopaState::Normal;
    currentAnimation = normalKoopa;

    // Backward direction
    setVelX(-2.0f);
    isForward = false; // Initially moving left
}

void Koopa::tick()
{
    Enemy::tick();

    // Update the timer
    ++timeCountForDeath;
    ++timeCountForShell;
    ++timeCountForShellMoving;

    // If
    if ((state == KoopaState::Shell && timeCountForShell == 400) || (state == KoopaState::ShellMoving && timeCountForShellMoving == 400))
    {
        setState(KoopaState::Normal);
    }

    currentAnimation.runAnimation();
}

void Koopa::render()
{
    if (state == KoopaState::Normal)
    {
        if (isForward)
        {
            // cout << "Koopa is moving forward" << endl;
            currentAnimation.drawAnimation(getX(), getY(), -(float)getWidth(), (float)getHeight());
        }
        else
        {
            currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        }
    }
    else if (state == KoopaState::Shell)
    {
        if (timeCountForShell < 200) // No legs
        {
            DrawTexturePro(koopaTextures[4],
                           {0.0f, 0.0f, (float)koopaTextures[4].width, (float)koopaTextures[4].height},
                           {getX(), getY(), getWidth(), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE);
        }
        else // With legs
            currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == KoopaState::ShellMoving) // No legs
    {
        DrawTexturePro(koopaTextures[4],
                       {0.0f, 0.0f, (float)koopaTextures[4].width, (float)koopaTextures[4].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
    }
    else if (state == KoopaState::DeadByFire)
    {
        DrawTexturePro(koopaTextures[4],
                       {0.0f, (float)koopaTextures[4].height, (float)koopaTextures[4].width, -(float)koopaTextures[4].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void Koopa::collision()
{
    const auto &gameObjects = handler->getGameObjects();
    // Check collision with all game objects
    for (auto &object : gameObjects)
    {
        if (object->getID() == ObjectID::Block)
            blockCollision(object);
        if (object->getID() == ObjectID::Pipe)
            pipeCollision(object);
        if (object->getID() == ObjectID::Player)
            continue;
        if (object->getID() == ObjectID::Enemy)
            enemyCollision(object);
        if (object->getID() == ObjectID::Item)
            itemCollision(object);
    }
}

void Koopa::pipeCollision(GameObject *object)
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
        // DrawText("Enemy hits the pipe from the bottom", 10, 30, 20, RED);
        setY(object->getY() + object->getHeight());
        setVelY(0);
        // cout << "Enemy hits the pipe from the bottom!" << endl;
        return;
    }

    // Check for collision with the top bounds of the object
    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        // DrawText("Enemy hits the pipe from the top!", 10, 50, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0);
        // cout << "Enemy hits the pipe from the top!" << endl;
        GameObject::collision();
        return;
    }

    // Check for collision with the right bounds of the object
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        // DrawText("Enemy hits the pipe from the right!", 10, 70, 20, RED);
        setX(object->getX() - getWidth());
        setVelX(-abs(getVelX()));
        isForward = false;
        return;
    }

    // Check for collision with the left bounds of the object
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        // DrawText("Enemy hits the pipe from the left!", 10, 10, 20, RED);
        setX(object->getX() + object->getWidth());
        setVelX(abs(getVelX()));
        isForward = true;
        return;
    }
}

void Koopa::blockCollision(GameObject *object)
{
    // cout<<"In Enemy::blockCollision()" << endl;
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
        // cout << "Enemy hits the block from the bottom!" << endl;
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
    }
    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        // Normal case
        setY(object->getY() - getHeight());
        setVelY(0.0f);
    }
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        // cout << "Enemy hits the block from the right!" << endl;
        // setX(object->getX() - getWidth());
        // setVelX(abs(getVelX())); // Move left after hitting right wall
    }
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        // cout << "Enemy hits the block from the left!" << endl;
        // setX(object->getX() + object->getWidth());
        // setVelX(-abs(getVelX()));
    }
}

void Koopa::playerCollision(int mode)
{
    // Only call in player collision check

    // cout << playerFinishedCollisionChecking() << endl;

    // Normal case
    if (state == KoopaState::Normal)
    {
        if (mode == 1)
        {
            // Koopa turn to shell
            setState(KoopaState::Shell);
        }
    }

    else if (state == KoopaState::Shell)
    {
        if (mode == 2)
        {
            setState(KoopaState::ShellMoving);
        }
    }

    else if (state == KoopaState::ShellMoving)
    {
        if (mode == 1 && timeCountForShellMoving > 200) // player bottom
        {
            setState(KoopaState::Shell);
        }
    }
}

bool Koopa::shouldRemove()
{
    if (state == KoopaState::DeadByFire && timeCountForDeath > 20)
        return true;
    return false;
}

bool Koopa::isDead()
{
    // cout << "In Koopa::isDead()" << endl;
    return state == KoopaState::DeadByFire;
}

void Koopa::enemyCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        setVelX(-abs(getVelX()));
        isForward = false; // Change direction to left
    }
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        setVelX(abs(getVelX()));
        isForward = true; // Change direction to right
    }

    // Normal case
}

bool Koopa::isStomped()
{
    return state == KoopaState::DeadByFire;
}

void Koopa::setState(KoopaState newState)
{
    if (state != KoopaState::Shell && newState == KoopaState::Shell)
    {
        // Set the height and width
        setHeight(getShellHeight());
        setWidth(getShellWidth());

        // Reset the timer for shell state
        timeCountForShell = 0;
    }
    else if (state != KoopaState::ShellMoving && newState == KoopaState::ShellMoving)
    {
        // Set the x coordinate
        setX(getX() + getWidth() / 2);
        setHeight(getShellHeight());

        // Reset the timer for shell moving state
        timeCountForShellMoving = 0;
    }
    else if (state != KoopaState ::Normal && newState == KoopaState::Normal)
    {
        setHeight(getKoopaHeight());
        setWidth(16.0f);
    }
    else if (state != KoopaState::DeadByFire && newState == KoopaState::DeadByFire)
    {
        // Set the height and width
        setHeight(getShellHeight());
        setWidth(getShellWidth());
    }

    state = newState;
    if (state == KoopaState::Normal)
    {
        currentAnimation = normalKoopa;
        currentAnimation.reset();
        if (isForward)
        {
            setVelX(-2.0f);
            isForward = false;
        }
        else
        {
            setVelX(2.0f);
            isForward = true;
        }
    }
    else if (state == KoopaState::Shell)
    {
        currentAnimation = shellKoopa;
        currentAnimation.reset();

        setVelX(0.0f);
    }
    else if (state == KoopaState::ShellMoving)
    {
        currentAnimation = shellKoopa;
        currentAnimation.reset();

        // Set the velocity
        if (isForward)
        {
            setVelX(-8.0f);
        }
        else
        {
            setVelX(8.0f);
        }
    }
}

Rectangle Koopa::getBounds()
{
    if (state == KoopaState ::Shell)
    {
        Rectangle boundsBottom = {getX(),
                                  getY() + getHeight() / 2,
                                  getWidth(),
                                  getHeight() / 2};
        return boundsBottom;
    }
    else
    {
        return Enemy::getBounds();
    }
}

Rectangle Koopa::getBoundsTop()
{
    if (state == KoopaState::Shell)
    {
        Rectangle boundsTop = {getX(),
                               getY(),
                               getWidth(),
                               getHeight() / 4};
        return boundsTop;
    }
    else
    {
        return Enemy::getBoundsTop();
    }
}

Rectangle Koopa::getBoundsRight()
{
    if (state == KoopaState::Shell)
    {
        Rectangle boundsRight = {getX() + getWidth() - getWidth() / 4,
                                 getY(),
                                 getWidth() / 4,
                                 getHeight()};
        return boundsRight;
    }
    else
    {
        return Enemy::getBoundsRight();
    }
}

Rectangle Koopa::getBoundsLeft()
{
    if (state == KoopaState::Shell)
    {
        Rectangle boundsLeft = {getX(),
                                getY(),
                                getWidth() / 4,
                                getHeight()};
        return boundsLeft;
    }
    else
    {
        return Enemy::getBoundsLeft();
    }
}

void Koopa::setStomped(bool newState)
{
    if (newState)
    {
        // cout << "Here" << endl;
        DrawTexturePro(koopaTextures[4],
                       {0.0f, 0.0f, (float)koopaTextures[4].width, (float)koopaTextures[4].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
    }

    else
    {
    }
}

bool Koopa::isShell()
{
    return state == KoopaState::Shell;
}

KoopaState Koopa::getState()
{
    return state;
}

void Koopa::itemCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    Item *item = dynamic_cast<Item *>(object);

    if (item && item->getItemType() == ItemType::Fire)
    {
        if ((CheckCollisionRecs(boundsTop, objectBoundsBottom) || CheckCollisionRecs(boundsBottom, objectBoundsTop) ||
             CheckCollisionRecs(boundsRight, objectBoundsLeft) || CheckCollisionRecs(boundsLeft, objectBoundsRight)) &&
            !object->isStomped())
        {
            setState(KoopaState::DeadByFire);

            timeCountForDeath = 0;

            setY(getY() - getHeight());

            setVelY(-4.0f);
            setVelX(0.0f);

            item->enemyCollision();
        }
    }
}