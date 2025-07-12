#pragma once
#include <SFML/Graphics.hpp>
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
    // Screen properties
    int screenWidth;
    int screenHeight;

    // UI
    UI ui;

    // Game state management
    GameState gameState = GameState::MainMenu;

    // Game
    Game *game;

    //
    sf::RenderWindow window;

public:
    App(int screenWidth, int screenHeight);

    // Main method to run the application
    void run();

    // Control method to handle game state
    void control(sf::Event &event);

    // UI &getUI();
    ~App();
};