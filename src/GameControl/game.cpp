#include <iostream>
#include <thread>
#include <chrono>
#include "game.h"
#include "player.h"
#include "block.h"
using namespace std;

Game::Game(sf::RenderWindow &window, int screenWidth, int screenHeight, UI *ui, sf::Event &event)
    : screenWidth(screenWidth), screenHeight(screenHeight), levelHandler(Handler(), ui, window), window(window), event(event)
{
    // cout << "In Game constructor" << endl;
    if (ui == nullptr)
    {
        cerr << "UI is null in Game constructor!" << endl;
        return;
    }
    initialize();
};

void Game::run()
{
    tick();
    render();
}

void Game::initialize()
{
    camera.setSize(screenWidth, screenHeight);
    levelHandler.start();
}

void Game::tick()
{
    keyInput.keyPressed();
    keyInput.keyReleased();
    levelHandler.getHandler().tick();

    float playerX = levelHandler.getHandler().getPlayer()->getX();
    float playerY = 0.0f;

    float cameraOffsetX = screenWidth / 2.0f;
    float cameraOffsetY = 16.0f;

    float centerX = playerX - (cameraOffsetX - screenWidth / 2.0f);
    float centerY = playerY - (cameraOffsetY - screenHeight / 2.0f);

    camera.setCenter(centerX, centerY);
    window.setView(camera);
}
void Game::render()
{

    levelHandler.getHandler().render();
}

bool Game::shouldExit()
{
    return levelHandler.getHandler().getPlayer()->isDead();
}

KeyInput &Game::getKeyInput()
{
    return keyInput;
}