#include <iostream>
#include "enemy.h"
using namespace std;

const float Enemy::WIDTH = 16.0f;
const float Enemy::KOOPA_HEIGHT = 24.0f;
const float Enemy::GOOMBA_HEIGHT = 16.0f;
const float Enemy::SHELL_HEIGHT = 14.0f;
const float Enemy::SHELL_WIDTH = 14.0f;
const float Enemy::STOMPED_GOOMBA_HEIGHT = 8.0f; // Height of a stomped Goomba

Enemy::Enemy(float x, float y, int scale, Handler *handler, UI *ui, EnemyCharacter id)
    : GameObject(x, y, ObjectID::Enemy, WIDTH, GOOMBA_HEIGHT, scale), ui(ui), index(index), handler(handler), enemyID(id)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in Enemy constructor!" << endl;
        return;
    }

    // Set the position of the enemy
    positionX = (float)getX();
    positionY = (float)getY();

    // Load enemy textures from UI
    enemyTextures = ui->getEnemy1();

    // Set velX and velY to 0
    setVelX(0.0f);
    setVelY(0.0f);

    // Set the height of the enemy
    if (enemyID == EnemyCharacter::Koopa)
    {
        setHeight(KOOPA_HEIGHT);
    }
    else if (enemyID == EnemyCharacter::Goomba)
    {
        setHeight(GOOMBA_HEIGHT);
    }

    // cout << "Enemy created at position: (" << positionX << ", " << positionY << ")" << endl;
}

void Enemy::render()
{
    DrawTexturePro(enemyTextures[index],
                   {0.0f, 0.0f, (float)enemyTextures[index].width, (float)enemyTextures[index].height},
                   {getX(), getY(), getWidth(), getHeight()},
                   {0.0f, 0.0f}, 0.0f, WHITE); // Draw small player texture
}

void Enemy::tick()
{
    applyGravity();
    // cout<<"In Enemy::tick()" << endl;
    collision();

    // Update the enemy's position based on its velocity
    setX(getX() + getVelX());
    setY(getY() + getVelY());

    // cout<< "Enemy position updated to: (" << getX() << ", " << getY() << ")" << endl;
}

Rectangle Enemy::getBounds()
{
    // cout << "In Enemy::getBounds()" << endl;
    Rectangle bounds{getX(),
                     getY() + getHeight() / 2,
                     getWidth(),
                     getHeight() / 2};
    return bounds;
}

Rectangle Enemy::getBoundsTop()
{
    Rectangle boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 2};
    return boundsTop;
}

Rectangle Enemy::getBoundsRight()
{
    Rectangle boundsRight{getX() + getWidth() / 2 + getWidth() / 4,
                          getY(),
                          getWidth() / 4,
                          getHeight()};
    return boundsRight;
}

Rectangle Enemy::getBoundsLeft()
{
    Rectangle boundsLeft{getX(),
                         getY(),
                         getWidth() / 4,
                         getHeight()};
    return boundsLeft;
}

Enemy::~Enemy()
{
}

void Enemy::collision()
{

    const auto &gameObjects = handler->getGameObjects();

    for (const auto &object : gameObjects)
    {
        ObjectID id = object->getID();

        if (id == ObjectID::Enemy)
        {
            enemyCollision(object);
        }

        if (id == ObjectID::Player)
        {
            playerCollision(object);
        }

        if (id == ObjectID::Block)
        {
            // cout<< "In Enemy::collision() with Block" << endl;
            blockCollision(object);
        }
        if (id == ObjectID::Pipe)
        {
            // cout << "In Enemy::collision() with Pipe" << endl;
            pipeCollision(object);
        }

        if (id == ObjectID::Item)
        {
            // cout << "In Enemy::collision() with Item" << endl;
            itemCollision(object);
        }
    }
}

void Enemy::pipeCollision(GameObject *object)
{
}

void Enemy::blockCollision(GameObject *object)
{
}

void Enemy::setEnemyID(EnemyCharacter id)
{
    enemyID = id;
}

EnemyCharacter Enemy::getEnemyID()
{
    return enemyID;
}

void Enemy::playerCollision(GameObject *object)
{
    // This method should be overridden in derived classes
    // cerr << "Error: playerCollision not implemented in Enemy class!" << endl;
}

bool Enemy::shouldRemove()
{
    return false;
}

bool Enemy::isDead()
{
    return false;
}

void Enemy::enemyCollision(GameObject *object)
{
}

bool Enemy::isStomped()
{
    return false;
}

bool Enemy::isShell()
{
    return false; // Default implementation, can be overridden in derived classes
}

void Enemy::itemCollision(GameObject *object)
{
    // This method should be overridden in derived classes
    // cerr << "Error: itemCollision not implemented in Enemy class!" << endl;
}

float Enemy::getShellHeight()
{
    return SHELL_HEIGHT; // Default implementation, can be overridden in derived classes
}

float Enemy::getKoopaHeight()
{
    return KOOPA_HEIGHT; // Default implementation, can be overridden in derived classes
}

float Enemy::getShellWidth()
{
    return SHELL_WIDTH; // Default implementation, can be overridden in derived classes
}

float Enemy::getStompedGoombaHeight()
{
    return STOMPED_GOOMBA_HEIGHT; // Default implementation, can be overridden in derived classes
}