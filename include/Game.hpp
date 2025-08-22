#pragma once
#include <States/GameState.hpp>
#include <States/StateRegistry.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <UI/TextureHolder.hpp>
#include <UI/Composite.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
    sf::ContextSettings contextSettings;
    sf::RenderWindow window;
    std::vector<std::shared_ptr<GameState>> stateStack;
    bool isRunning = true;
    StateRegistry registry;
    TextureHolder textureHolder;
    sf::Music backgroundMusic;
public:
    Game();
    void run();
    void pushState(const std::string &string);
    void popState();
    GameState *currentState();
    sf::RenderWindow &getWindow();
    void quit();
    StateRegistry &getRegistry();
    TextureHolder& getTexHolder();
};