#include <iostream>
#include <SFML/Audio.hpp>
#include "app.h"
using namespace std;

App::App(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), window(sf::VideoMode(screenWidth, screenHeight), "Game Window"), game(nullptr)
{
    window.setFramerateLimit(60); // Set the frame rate limit to 60 FPS
    // cout << "In App constructor" << endl;
    ui.loadImages(); // Load UI images
    ui.loadAudio();  // Load audio files
}

void App::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); // Close the window if the close event is triggered
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close(); // Close the window if Escape is pressed
            }

            if (game)
            {
                game->getKeyInput().eventUpdate(event);
            }
        }
        window.clear(sf::Color(146, 144, 255, 255));

        // Handle game state control
        control(event);

        // Display the contents of the window
        window.display();
    }
}

App::~App()
{
    if (game != nullptr)
    {
        delete game;    // Delete the game instance to free memory
        game = nullptr; // Set to nullptr to avoid dangling pointer
    }
}

void App::control(sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && gameState != GameState::Play)
    {
        // Change game state to Play
        gameState = GameState::Play;

        // Play music
        ui.getOverworldBackGroundMusic().play();

        // Initialize the game
        // cout << "Starting the game..." << endl;
        game = new Game(window, screenWidth, screenHeight, &ui, event);

        // cout << "In App::control()" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        gameState = GameState::Pause; // Change game state to Pause
    }

    if (gameState == GameState::Play)
    {
        game->run();
        if (game->shouldExit())
        {
            // cout << "Game Over! Exiting..." << endl;

            // Delete the current game
            delete game;
            game = nullptr;

            // Change game state to GameOver
            gameState = GameState::GameOver;

            // Stop background music
            ui.getOverworldBackGroundMusic().stop();

            cout << "Game Over! Exiting..." << endl;
        }
    }

    if (gameState == GameState::Pause)
        cout << "Game is paused. Press ENTER to resume." << endl;

    if (gameState == GameState::MainMenu)
        cout << "Main Menu: Press B to start the game." << endl;

    if (gameState == GameState::GameOver)
    {
        cout << "Game Over: Press B to restart or ESC to exit." << endl;
    }
}