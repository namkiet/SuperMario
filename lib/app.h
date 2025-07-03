#pragma once
#include "game.h"
#include "gameObject.h"
#include "UI.h"
enum class GameState
{
    MainMenu,
    Play,
    Pause,
    GameOver
};

class App
{
private:
    int screenWidth;
    int screenHeight;
    GameObject gameObject;
    UI ui;
    GameState gameState = GameState::MainMenu;
    Game *game;
public:
    App(int screenWidth, int screenHeight);
    
    // Main method to run the application
    void run();
    
    // Control method to handle game state
    void control();
    
    // UI &getUI();
    ~App();
};