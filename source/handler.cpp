#include <iostream>
#include <raylib.h>
#include "handler.h"
using namespace std;

Handler::Handler() : player(nullptr)
{
}

void Handler::tick()
{
    for (auto &gameObject : gameObjects)
    {
        if (gameObject == nullptr)
        {
            cerr << "Warning: Found nullptr in gameObjects during tick!" << endl;
            continue;
        }
        if (gameObject != nullptr)
        {
            gameObject->tick();
        }
    }

    std::vector<GameObject *> removedBlocks = player->getAndResetRemovedBlocks();
    // cout<< "Number of blocks to remove in tick(): " << removedBlocks.size() << endl;
    for (auto &block : removedBlocks)
    {
        // cout << "Address of block to remove in tick(): " << block << endl;
        if (block == nullptr)
        {
            cerr << "Warning: Found nullptr in removedBlocks!" << endl;
            continue;
        }
        removeObject(block);
    }

    std::vector<GameObject *> removedEnemy = player->getAndResetRemovedEnemies();
    // cout<< "Number of enemies to remove in tick(): " << removedEnemy.size() << endl;
    for (auto &enemy : removedEnemy)
    {
        // cout << "Address of enemy to remove in tick(): " << enemy << endl;
        if (enemy == nullptr)
        {
            cerr << "Warning: Found nullptr in removedEnemy!" << endl;
            continue;
        }
        removeObject(enemy);
    }
}

void Handler::render()
{
    for (auto &gameObject : gameObjects)
    {
        if (gameObject == nullptr)
        {
            cerr << "Warning: Found nullptr in gameObjects during render!" << endl;
            continue;
        }
        if (gameObject->getID() == GameObject::ObjectID::Player)
        {
            continue;
        }
        else
        {
            gameObject->render();
            // cout << "In Handler::render()" << endl;
        }
    }
    if (player)
    {
        player->render();
        // cout << "Rendering player." << endl;
    }
    else
    {
        cerr << "Warning: Player is null during render!" << endl;
    }
}

void Handler::addObject(GameObject *obj)
{
    if (obj == nullptr)
    {
        cerr << "Error: Attempted to add a null GameObject." << endl;
        return;
    }
    gameObjects.push_back(obj);
    // cout << "In Handler::addObject()" << endl;
}

void Handler::removeObject(GameObject *obj)
{
    // cout << "Address of object to remove in removeObject(): " << obj << endl;
    auto it = std::remove(gameObjects.begin(), gameObjects.end(), obj);
    if (it != gameObjects.end())
    {
        delete obj;
        gameObjects.erase(it, gameObjects.end());
        // cout << "Object removed from gameObjects." << endl;
    }
    else
    {
        cerr << "Error: Attempted to remove an object not in gameObjects!" << endl;
    }
}

std::vector<GameObject *> &Handler::getGameObjects()
{
    // cout << "Game objects size: " << gameObjects.size() << endl;
    // for (auto &gameObject : gameObjects)
    // {
    //     cout << gameObject << endl; // Print addresses of gameObjects
    // }
    return gameObjects;
}

int Handler::setPlayer(Player &player)
{
    if (this->player != nullptr)
    {
        return -1;
    }
    addObject(&player);
    this->player = &player;

    return 0;
}

int Handler::removePlayer()
{
    if (this->player == nullptr)
    {
        return -1;
    }
    removeObject(this->player);
    this->player = nullptr;

    return 0;
}

Player *Handler::getPlayer()
{
    return this->player;
}

Handler::~Handler()
{
    // cout << "Handler destructor called." << endl;
    for (auto &gameObject : gameObjects)
    {
        if (gameObject != player) // Avoid double deletion of player
        {
            delete gameObject;
        }
    }
    gameObjects.clear();
    if (player != nullptr)
    {
        delete player; // Clean up Player if it was dynamically allocated
        player = nullptr;
    }
}