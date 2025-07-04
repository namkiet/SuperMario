#include <iostream>
#include <raylib.h>
#include "app.h"
using namespace std;

Color backgroundColor = {146, 144, 255, 255};
App::App(int screenWidth, int screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight), gameObject(screenWidth, screenHeight)
{
    InitWindow(screenWidth, screenHeight, "Game Window");
    SetTargetFPS(60); // Set the game to run at 60 frames per second
    ui.loadImages();  // Load UI images
   
    // cout << "App constructor called" << endl;
}

void App::run()
{
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        control();
        EndDrawing();
    }
    ui.unloadImages(); // Unload UI images
    CloseWindow();     // Close the window and OpenGL context
}

App::~App()
{
    // cout << "App destructor called" << endl;
    // Cleanup if necessary
    if (game != nullptr)
    {
        delete game;    // Delete the game instance to free memory
        game = nullptr; // Set to nullptr to avoid dangling pointer
    }
}

void App::control()
{
    if (IsKeyPressed(KEY_B))
    {
        gameState = GameState::Play; // Change game state to Play
        game = new Game(screenWidth, screenHeight, &ui);
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        return; // Exit the game loop
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        gameState = GameState::Pause;
    }

    if (gameState == GameState::Play)
    {
        game->run(); // Because this did not stop, cancel it here first
        if (game->shouldExit())
        {
            delete game;
            game = nullptr;
            gameState = GameState::GameOver; // Change game state to GameOver
        }
    }

    if (gameState == GameState::Pause)
        cout << "Game is paused. Press ENTER to resume." << endl;

    if (gameState == GameState::MainMenu)
        cout << "Main Menu: Press B to start the game." << endl;

    if (gameState == GameState::GameOver)
        cout << "Game Over: Press B to restart or ESC to exit." << endl;
}