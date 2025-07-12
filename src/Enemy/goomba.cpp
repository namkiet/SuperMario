#include <iostream>
#include <cmath>
#include "goomba.h"
#include "item.h"
#include "koopa.h"
using namespace std;

Goomba::Goomba(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window)
    : Enemy(x, y, scale, handler, ui, window, EnemyCharacter::Goomba)
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
    for (int i = 0; i < 3; ++i)
    {
        goombaTextures.push_back(ui->getEnemy1()[i]);
    }

    // Initialize animation
    std::vector<sf::Texture> normalGoombaTextures;
    for (int i = 0; i < 2; ++i)
    {
        normalGoombaTextures.push_back(goombaTextures[i]);
    }
    normalGoomba = new Animation(4, normalGoombaTextures, window);

    // Set the initial animation
    state = GoombaState::Normal;
    currentAnimation = normalGoomba;

    // Backward direction
    setVelX(-2.0f);
}

void Goomba::tick()
{
    Enemy::tick();

    currentAnimation->runAnimation();
}

void Goomba::render()
{
    // cout << timeCount << endl;
    // cout << "Rendering Goomba at position: (" << getX() << ", " << getY() << ") with width: " << getWidth() << " and height: " << getHeight() << endl;
    if (state == GoombaState::Normal)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == GoombaState::Stomped)
    {
        sf::Sprite sprite;
        sprite.setTexture(goombaTextures[2]);
        sprite.setPosition(getX(), getY());
        float scaleX = getWidth() / goombaTextures[2].getSize().x;
        float scaleY = getHeight() / goombaTextures[2].getSize().y;
        sprite.setScale(scaleX, scaleY); // Set the scale
        getWindow().draw(sprite);        // Draw the stomped Goomba texture
        ++timeCount;
    }
    else if (state == GoombaState ::DeadByEnemy || state == GoombaState::DeadByFire)
    {
        sf::Sprite sprite;
        sprite.setTexture(goombaTextures[1]);
        sprite.setPosition(getX(), getY());
        float scaleX = getWidth() / goombaTextures[1].getSize().x;
        float scaleY = getHeight() / goombaTextures[1].getSize().y;
        sprite.setOrigin(0, goombaTextures[1].getSize().y); // Set the origin to the bottom-left corner
        sprite.setScale(scaleX, -scaleY);                    // Set the scale of the sprite
        getWindow().draw(sprite);                           // Draw the dead Goomba texture
        ++timeCount;
    }
}

void Goomba::collision()
{
    Enemy::collision();
}

void Goomba::pipeCollision(GameObject *object)
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
        // DrawText("Enemy hits the pipe from the bottom", 10, 30, 20, RED);
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
        // cout << "Enemy hits the pipe from the bottom!" << endl;
        return;
    }

    // Check for collision with the top bounds of the object
    if (boundsBottom.intersects(objectBoundsTop))
    {
        // DrawText("Enemy hits the pipe from the top!", 10, 50, 20, RED);
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        return;
    }

    // Check for collision with the right bounds of the object
    if (boundsRight.intersects(objectBoundsLeft))
    {
        // DrawText("Enemy hits the pipe from the right!", 10, 70, 20, RED);
        setX(object->getX() - getWidth());
        setVelX(-abs(getVelX())); // Move left after hitting right wall
        return;
    }

    // Check for collision with the left bounds of the object
    if (objectBoundsRight.intersects(boundsLeft))
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
        // cout << "Enemy hits the block from the bottom!" << endl;
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
    }
    if (boundsBottom.intersects(objectBoundsTop))
    {
        // cout << "Enemy hits the block from the top!" << endl;
        // cout<<"Object Y: " << object->getY() << ", Enemy Height: " << getHeight() << endl;
        setY(object->getY() - getHeight());

        // cout << "y coordinate of enemy in block collision is = " << getY() << endl;
        setVelY(0.0f);
        // setVelX(-8.0f);
        GameObject::collision();
    }
    if (boundsRight.intersects(objectBoundsLeft))
    {
        // cout << "Enemy hits the block from the right!" << endl;
        // setX(object->getX() - getWidth());
        // setVelX(abs(getVelX())); // Move left after hitting right wall
    }
    if (objectBoundsRight.intersects(boundsLeft))
    {
        // cout << "Enemy hits the block from the left!" << endl;
        // setX(object->getX() + object->getWidth());
        // setVelX(-abs(getVelX()));
    }
}

void Goomba::playerCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    if (boundsTop.intersects(objectBoundsBottom) && !object->isStomped())
    {
        // Player hits the Goomba from the top
        setState(GoombaState::Stomped);
        setVelY(0);
        setVelX(0);
    }
}

bool Goomba::shouldRemove()
{
    // cout << (state == GoombaState::DeadByEnemy) << endl;
    if ((state == GoombaState::Stomped || state == GoombaState::DeadByEnemy || state == GoombaState::DeadByFire) && timeCount > 20)
    {
        setState(GoombaState::Dead);
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
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Enemy *enemy = dynamic_cast<Enemy *>(object);
    if (boundsTop.intersects(objectBoundsBottom) || boundsBottom.intersects(objectBoundsTop) ||
        boundsLeft.intersects(objectBoundsRight) || boundsRight.intersects(objectBoundsLeft))
    {
        Koopa *koopa = dynamic_cast<Koopa *>(enemy);
        if (koopa && koopa->getState() != KoopaState::Normal)
        {
            setState(GoombaState::DeadByEnemy);
            timeCount = 0; // Reset timer for dead state
            setY(getY() - getHeight());
            setVelY(-8.0f);
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

sf::FloatRect Goomba::getBounds()
{
    if (state == GoombaState::Stomped)
    {
        sf::FloatRect boundsBottom = {getX(),
                                      getY() + getHeight() - getHeight() / 4,
                                      getWidth(),
                                      getHeight() / 4};

        return boundsBottom;
    }
    else
    {
        sf::FloatRect boundsBottom = {getX(),
                                      getY() + getHeight() / 2,
                                      getWidth(),
                                      getHeight() / 2};
        return boundsBottom;
    }
}

sf::FloatRect Goomba::getBoundsTop()
{
    if (state == GoombaState::Stomped)
    {
        sf::FloatRect boundsTop = {getX(),
                                   getY(),
                                   getWidth(),
                                   getHeight() / 4};
        return boundsTop;
    }
    else
    {
        sf::FloatRect boundsTop = {getX(),
                                   getY(),
                                   getWidth(),
                                   getHeight() / 2};
        return boundsTop;
    }
}

sf::FloatRect Goomba::getBoundsRight()
{
    if (state == GoombaState::Stomped)
    {
        sf::FloatRect boundsRight = {getX() + getWidth() - getWidth() / 4,
                                     getY() + getHeight() / 2,
                                     getWidth() / 4,
                                     getHeight() / 2};
        return boundsRight;
    }
    else
    {
        sf::FloatRect boundsRight = {getX() + getWidth() - getWidth() / 4,
                                     getY(),
                                     getWidth() / 4,
                                     getHeight()};
        return boundsRight;
    }
}

sf::FloatRect Goomba::getBoundsLeft()
{
    if (state == GoombaState::Stomped)
    {
        sf::FloatRect boundsLeft = {getX(),
                                    getY() + getHeight() / 2,
                                    getWidth() / 4,
                                    getHeight() / 2};
        return boundsLeft;
    }
    else
    {
        sf::FloatRect boundsLeft = {getX(),
                                    getY(),
                                    getWidth() / 4,
                                    getHeight()};
        return boundsLeft;
    }
}

void Goomba::itemCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Item *item = dynamic_cast<Item *>(object);

    if (item && item->getItemType() == ItemType::Fire)
    {
        if ((boundsTop.intersects(objectBoundsBottom) || boundsBottom.intersects(objectBoundsTop) ||
             boundsLeft.intersects(objectBoundsRight) || boundsRight.intersects(objectBoundsLeft)) &&
            !item->isStomped())
        {
            setState(GoombaState::DeadByFire);

            timeCount = 0;
            setY(getY() - getHeight());

            setVelY(0);

            item->enemyCollision();
        }
    }
}

void Goomba::setState(GoombaState newState)
{
    if (state != GoombaState::Stomped && newState == GoombaState::Stomped)
    {
        setY(getY() + getHeight() - getStompedGoombaHeight());
        setHeight(getStompedGoombaHeight());
    }
    state = newState;
}

Goomba::~Goomba()
{
    if (normalGoomba)
    {
        delete normalGoomba;
    }
    currentAnimation = nullptr;
    normalGoomba = nullptr;
}