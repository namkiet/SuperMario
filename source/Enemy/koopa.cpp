#include <iostream>
#include <cmath>
#include "koopa.h"
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

    if (state == KoopaState::Shell)
    {
        ++timeCount;
        if (timeCount == 400)
        {
            //cout << timeCount << endl;
            setState(KoopaState::ShellMoving);
            timeCount = 0;

            // Reset the player's collision checking state
            handler->getPlayer()->setPlayerFinishedCollisionChecking(false);
        }
    }
    // cout << "Tick: state = " << (int)state << ", timeCount = " << timeCount << endl;

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
        if (timeCount < 200)
        {
            //cout << getX() << ", " << getY() << ", " << getWidth() << ", " << getHeight() << endl;
            DrawTexturePro(koopaTextures[4],
                           {0.0f, 0.0f, (float)koopaTextures[4].width, (float)koopaTextures[4].height},
                           {getX(), getY(), getWidth(), getHeight()},
                           {0.0f, 0.0f}, 0.0f, WHITE);
        }
        else
        {
            setHeight(getKoopaHeight());
            currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        }
    }
    else if (state == KoopaState::ShellMoving)
    {
        if (isForward)
        {
            // cout << "Koopa is moving forward in shell state" << endl;
            currentAnimation.drawAnimation(getX(), getY(), -(float)getWidth(), (float)getHeight());
        }
        else
        {
            currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
        }
    }
    else if (state == KoopaState::Stomped)
    {
        DrawTexturePro(koopaTextures[4],
                       {0.0f, 0.0f, (float)koopaTextures[4].width, (float)koopaTextures[4].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
    }
    // cout << "Render: state = " << (int)state << ", timeCount = " << timeCount << endl;
}

void Koopa::collision()
{
    Enemy::collision();
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

void Koopa::playerCollision(GameObject *object)
{
    ++mode;

    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    // cout << playerFinishedCollisionChecking() << endl;

    // Normal case
    if (CheckCollisionRecs(boundsTop, objectBoundsBottom) && !object->isStomped())
    {
        // cout << "Koopa is hit in playerCollision()" << endl;
        if ((state == KoopaState::Normal || state == KoopaState::ShellMoving || state == KoopaState::Shell))
        {

            if (!object->playerFinishedCollisionChecking())
            {
                cout << "The order that i expected: 1" << endl;
                setState(KoopaState::Shell);
                // object->setPlayerFinishedCollisionChecking(false); // Reset player collision checking statesetState(KoopaState::Stomped)
                setVelY(0);
                setVelX(0);

                mode = 0; // Reset mode
            }
            else if (object->playerFinishedCollisionChecking())
            {
                cout << "The order that i expected: 3" << endl;
                setState(KoopaState::Stomped); // Use setState instead of direct assignment
                // object->setPlayerFinishedCollisionChecking(false); // Reset player collision checking state
                timeCount = 0; // Reset timer for stomped state}
                return;
            }
        }
        else if (state == KoopaState::Stomped)
        {
            if (isForward)
            {
                setVelX(4.0f);
            }
            else
            {
                setVelX(-4.0f);
            }
        }
    }
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        if (state == KoopaState::Shell)
        {
            setVelX(4.0f);
            timeCount = 0; // Reset timer for shell state
        }
    }
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        if (state == KoopaState::Shell)
        {
            setVelX(-4.0f);
            timeCount = 0; // Reset timer for shell state
        }
    }
}

bool Koopa::shouldRemove()
{
    // Only die if the Koopa is hit by a fire or its y coordinate is more than the screen height
    // if (state == KoopaState::Stomped && timeCount > 100)
    // {
    //     state = KoopaState::Dead;
    //     return true;
    // }
    return false;
}

bool Koopa::isDead()
{
    // cout << "In Koopa::isDead()" << endl;
    return state == KoopaState::Dead;
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
    return state == KoopaState::Stomped;
}

void Koopa::setState(KoopaState newState)
{
    if (state != KoopaState::Shell && newState == KoopaState::Shell)
    {
        // cout << "Origin height: " << getHeight() << endl;
        setY(getY() + getKoopaHeight() - getShellHeight());
        
        setHeight(getShellHeight());
        setWidth(getShellWidth());

        // cout << "New height: " << getHeight() << endl;
    }
    else if (state != KoopaState::Stomped && newState == KoopaState::Stomped)
    {
        setY(getY() + getKoopaHeight() - getShellHeight());
        setHeight(getShellHeight());
    }
    state = newState;
    if (state == KoopaState::Normal)
    {
        currentAnimation = normalKoopa;
        currentAnimation.reset();
    }
    else if (state == KoopaState::ShellMoving)
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
    }
    else if (state == KoopaState::Dead)
    {
        timeCount = 0;
    }
}

Rectangle Koopa::getBounds()
{
    if (state == KoopaState ::Shell || state == KoopaState::Stomped)
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
    if (state == KoopaState::Shell || state == KoopaState::Stomped)
    {
        Rectangle boundsTop = {getX(),
                               getY() + getHeight() / 2,
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
    if (state == KoopaState::Shell | state == KoopaState::Stomped)
    {
        Rectangle boundsRight = {getX() + getWidth() - getWidth() / 4,
                                 getY() + getHeight() / 2,
                                 getWidth() / 4,
                                 getHeight() / 2};
        return boundsRight;
    }
    else
    {
        return Enemy::getBoundsRight();
    }
}

Rectangle Koopa::getBoundsLeft()
{
    if (state == KoopaState::Shell || state == KoopaState::Stomped)
    {
        Rectangle boundsLeft = {getX(),
                                getY() + getHeight() / 2,
                                getWidth() / 4,
                                getHeight() / 2};
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