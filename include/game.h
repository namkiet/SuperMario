#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "handler.h"
#include "keyInput.h"
#include "UI.h"
#include "levelHandler.h"
using namespace std;

class Game
{
public:
    Game() = default;
    Game(sf::RenderWindow &window, int screenWidth, int screenHeight, UI *ui, sf::Event &event);
    void run();
    ~Game() = default; // Default destructor
    void initialize();
    void tick();
    void render();
    bool shouldExit();
    KeyInput &getKeyInput();

private:
    // Game constants

    int screenWidth, screenHeight;

    // Game components

    LevelHandler levelHandler;
    sf::View camera;
    sf::Event &event;
    KeyInput keyInput{levelHandler.getHandler(), event}; // KeyInput instance initialized with handler

    sf::RenderWindow &window;
};