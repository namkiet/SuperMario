#include <iostream>
#include <thread>
#include <chrono>
#include <raylib.h>
#include "game.h"
#include "player.h"
#include "block.h"
using namespace std;

const int Game::MILLIS_PER_SEC = 1000;
const int Game::NANOS_PER_SEC = 1000000000;
const double Game::NUM_TICKS = 60.0;

Game::Game(int screenWidth, int screenHeight, UI *ui) : screenWidth(screenWidth), screenHeight(screenHeight), levelHandler(Handler(), ui)
{
    // cout << "Game constructor called." << endl;
    // handler = Handler();
    // for (auto &texture : ui->getMarioLarge())
    // {
    //     if (texture.id == 0)
    //     {
    //         std::cerr << "Error: Texture not loaded properly!" << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "Loaded texture with ID: " << texture.id << std::endl;
    //     }
    // }
    initialize();
};

void Game::main(std::string args[])
{
    // cout << "In Game::main()" << endl;
    new Game();
}
void Game::run()
{
    // cout << "In Game::run()" << endl;
    // Take nano seconds
    long long lastTime = nanoTime();

    double amountOfTicks = NUM_TICKS;
    double ns = NANOS_PER_SEC / amountOfTicks;
    double delta = 0;

    // Take current time in milliseconds
    long timer = currentTimeMillis();
    int frames = 0;
    int updates = 0;

    tick();
    render();

    // while (running)
    // {
    //     long long now = nanoTime();
    //     delta += (now - lastTime) / ns;
    //     lastTime = now;
    //     while (delta >= 1)
    //     {
    //         tick();
    //         ++updates;
    //         --delta;
    //     }

    //     if (running)
    //     {
    //         render();
    //         ++frames;
    //     }

    //     if (currentTimeMillis() - timer > MILLIS_PER_SEC)
    //     {
    //         timer += MILLIS_PER_SEC;
    //         cout << "FPS: " << frames << " TPS: " << updates << endl;
    //         updates = 0;
    //         frames = 0;
    //     }
    // }
    stop();
}

void Game::initialize()
{
    // cout << "In Game::initialize()" << endl;
    // Player *player = new Player(32, 32, 0, 2, &handler, ui);
    // handler.setPlayer(*player);
    // for (int i = 0; i < 20; ++i)
    // {
    //     handler.addObject(new Block(i * 32, 32 * 10, 32, 32, 0, 1, ui));
    // }
    // for (int i = 0; i < 30; ++i)
    // {
    //     handler.addObject(new Block(i * 32, 32 * 15, 32, 32, 0, 1, ui));
    // }
    levelHandler.start();

    start();
}
void Game::start()
{
    // cout << "In Game::start()" << endl;
    // thread = new std::thread(*this);
    // thread.start();
    running = true;
}
void Game::stop()
{
    try
    {
        // thread.join();
        running = false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error stopping the game: " << e.what() << std::endl;
    }
}

long long Game::nanoTime()
{
    // Get current time point with nanosecond precision
    auto now = std::chrono::high_resolution_clock::now();

    // Convert time point to nanoseconds since epoch
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    return nanos;
}

long long Game::currentTimeMillis()
{
    // Get current time point with nanosecond precision
    auto now = std::chrono::high_resolution_clock::now();

    // Convert time point to milliseconds since epoch
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return millis;
}

void Game::tick()
{
    keyInput.keyPressed();
    keyInput.keyReleased();
    levelHandler.getHandler().tick();

    // std::cout << "Player X: " << handler.getPlayer()->getX() << ", Y: " << handler.getPlayer()->getY() << std::endl;
    camera.target = Vector2{levelHandler.getHandler().getPlayer()->getX(), 0.0f};
    // // std::cout << "Camera Target X: " << camera.target.x << ", Y: " << camera.target.y << std::endl;
    camera.offset = Vector2{screenWidth / 2.0f, 16};
    camera.rotation = 0.0f; // No rotation
    camera.zoom = 1.0f;     // Default zoom level
}
void Game::render()
{
    BeginMode2D(camera);
    levelHandler.getHandler().render();
    EndMode2D();
}

bool Game::shouldExit()
{
    return levelHandler.getHandler().getPlayer()->isDead();
}