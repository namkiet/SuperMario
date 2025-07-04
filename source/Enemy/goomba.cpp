#include <iostream>
#include <cmath>
#include "goomba.h"
using namespace std;

Goomba::Goomba(float x, float y, int index, int scale, Handler *handler, UI *ui)
    : Enemy(x, y, index, scale, handler, ui, EnemyCharacter::Goomba)
{
    if (handler == nullptr)
    {
        cerr << "Handler is null in Goomba constructor!" << endl;
        return;
    }

    if (ui == nullptr)
    {
        cerr << "UI is null in Goomba constructor!" << endl;
        return;
    }

    // Load Goomba textures from UI
    for (int i = 0; i < 4; ++i)
    {
        goombaTextures.push_back(ui->getEnemy1()[i]);
    }

    // Initialize animation
    std::vector<Texture2D> normalGoombaTextures;
    for (int i = 0; i < 2; ++i)
    {
        normalGoombaTextures.push_back(goombaTextures[i]);
    }
    normalGoomba = Animation(4, normalGoombaTextures);

    // Set the initial animation
    state = GoombaState::Normal;
    currentAnimation = normalGoomba;

    // Backward direction
    setVelX(-2.0f);
}

void Goomba::tick()
{
    Enemy::tick();

    currentAnimation.runAnimation();
}

void Goomba::render()
{
    if (state == GoombaState::Normal)
    {
        currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == GoombaState::Stomped)
    {
        DrawTexturePro(goombaTextures[2],
                       {0.0f, 0.0f, (float)goombaTextures[2].width, (float)goombaTextures[2].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
        ++timeCount;
    }
    else if (state == GoombaState ::DeadByEnemy)
    {
        DrawTexturePro(goombaTextures[2],
                       {0.0f, (float)goombaTextures[2].height, (float)goombaTextures[2].width, -(float)goombaTextures[2].height},
                       {getX(), getY(), getWidth(), getHeight()},
                       {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void Goomba::collision()
{
    Enemy::collision();
}

void Goomba::pipeCollision(GameObject *object)
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
        setVelY(0.0f);
        // cout << "Enemy hits the pipe from the bottom!" << endl;
        return;
    }

    // Check for collision with the top bounds of the object
    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        // DrawText("Enemy hits the pipe from the top!", 10, 50, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        return;
    }

    // Check for collision with the right bounds of the object
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        // DrawText("Enemy hits the pipe from the right!", 10, 70, 20, RED);
        setX(object->getX() - getWidth());
        setVelX(-abs(getVelX())); // Move left after hitting right wall
        return;
    }

    // Check for collision with the left bounds of the object
    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        // DrawText("Enemy hits the pipe from the left!", 10, 10, 20, RED);
        setX(object->getX() + object->getWidth());
        setVelX(abs(getVelX())); // Move right after hitting left wall
        return;
    }
}

void Goomba::blockCollision(GameObject *object)
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
        // cout << "Enemy hits the block from the top!" << endl;
        // cout<<"Object Y: " << object->getY() << ", Enemy Height: " << getHeight() << endl;
        setY(object->getY() - getHeight());

        // cout << "y coordinate of enemy in block collision is = " << getY() << endl;
        setVelY(0.0f);
        // setVelX(-8.0f);
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

void Goomba::playerCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    if (CheckCollisionRecs(boundsTop, objectBoundsBottom) && !object->isStomped())
    {
        // Player hits the Goomba from the top
        state = GoombaState::Stomped;
        setVelY(0);
        setVelX(0);
    }
}

bool Goomba::shouldRemove()
{
    if ((state == GoombaState::Stomped || state == GoombaState::DeadByEnemy) && timeCount > 20)
    {
        state = GoombaState::Dead;
        return true;
    }
    return false;
}

bool Goomba::isDead()
{
    // cout << "In Goomba::isDead()" << endl;
    return state == GoombaState::Dead || state == GoombaState::DeadByEnemy;
}

void Goomba::enemyCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    Enemy *enemy = dynamic_cast<Enemy *>(object);
    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa && enemy->isShell())
        {
            state = GoombaState::DeadByEnemy;
            timeCount = 0; // Reset timer for dead state
            // isPlayingDeath = true; // Player is dead
            setY(getY() + getHeight() - getHeight() / 8);
            setVelY(0);
            setVelX(0.0f);
        }
        else
        {
            setVelX(-getVelX());
        }
    }

    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        if (enemy != nullptr && enemy->getEnemyID() == EnemyCharacter::Koopa && enemy->isShell())
        {
            state = GoombaState::DeadByEnemy;
            timeCount = 0; // Reset timer for death state
            // isPlayingDeath = true; // Player is dead
            setY(getY() + getHeight() - getHeight() / 8);
            setVelY(0);
            setVelX(0.0f);
        }
        else
        {
            setVelX(-getVelX());
        }
    }
}

bool Goomba::isStomped()
{
    return state == GoombaState::Stomped;
}

Rectangle Goomba::getBounds()
{
    if (state == GoombaState::Stomped || state == GoombaState::DeadByEnemy)
    {
        Rectangle boundsBottom = {getX(),
                                  getY() + getHeight() / 2 + getHeight() / 4 + getHeight() / 8,
                                  getWidth(),
                                  getHeight() / 8};

        return boundsBottom;
    }
    else
    {
        Rectangle boundsBottom = {getX(),
                                  getY() + getHeight() / 2,
                                  getWidth(),
                                  getHeight() / 2};
        return boundsBottom;
    }
}

Rectangle Goomba::getBoundsTop()
{
    if (state == GoombaState::Stomped || state == GoombaState::DeadByEnemy)
    {
        Rectangle boundsTop = {getX(),
                               getY() + getHeight() / 2 + getHeight() / 4,
                               getWidth(),
                               getHeight() / 8};
        return boundsTop;
    }
    else
    {
        Rectangle boundsTop = {getX(),
                               getY() + getHeight() / 2,
                               getWidth(),
                               getHeight() / 4};
        return boundsTop;
    }
}

Rectangle Goomba::getBoundsRight()
{
    if (state == GoombaState::Stomped || state == GoombaState::DeadByEnemy)
    {
        Rectangle boundsRight = {getX() + getWidth() - getWidth() / 4,
                                 getY() + getHeight() / 2 + getHeight() / 4,
                                 getWidth() / 4,
                                 getHeight() / 4};
        return boundsRight;
    }
    else
    {
        Rectangle boundsRight = {getX() + getWidth() - getWidth() / 4,
                                 getY() + getHeight() / 2,
                                 getWidth() / 4,
                                 getHeight() / 2};
        return boundsRight;
    }
}

Rectangle Goomba::getBoundsLeft()
{
    if (state == GoombaState::Stomped || state == GoombaState::DeadByEnemy)
    {
        Rectangle boundsLeft = {getX(),
                                getY() + getHeight() / 2 + getHeight() / 4,
                                getWidth() / 4,
                                getHeight() / 4};
        return boundsLeft;
    }
    else
    {
        Rectangle boundsLeft = {getX(),
                                getY() + getHeight() / 2,
                                getWidth() / 4,
                                getHeight() / 2};
        return boundsLeft;
    }
}