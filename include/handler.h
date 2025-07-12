#pragma once
#include <vector>
#include "player.h"
#include "enemy.h"
#include "gameObject.h"
class Player;
class Enemy;

class Handler
{
private:
    std::vector<GameObject *> gameObjects;
    Player *player;
    Handler *handler;

public:
    // Constructor
    Handler();

    // Update
    void tick();
    void render();

    // Game objects management
    void addObject(GameObject *obj);
    void removeObject(GameObject *obj);
    std::vector<GameObject *> &getGameObjects();
    bool isObjectRemoved(GameObject*obj);
    
    // Player management
    int setPlayer(Player &player);
    int removePlayer();
    Player *getPlayer();

    // Destructor
    ~Handler();
};