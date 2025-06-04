// === Game.cpp ===
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "SettingsState.hpp"

Game::Game() 
    : contextSettings(0, 0, 16)
    , window(sf::VideoMode(800, 600), "Game", sf::Style::Default, contextSettings)
{
    registry.registerInstance("menu", std::make_shared<MenuState>());
    registry.registerInstance("play", std::make_shared<PlayingState>());
    registry.registerInstance("settings", std::make_shared<SettingsState>());

    pushState("menu");
}

void Game::run() 
{
    sf::Clock clock;
    while (window.isOpen() && isRunning && !stateStack.empty() || !currentState()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (currentState()) currentState()->handleEvent(*this, event);
        }

        float dt = clock.restart().asSeconds();
        if (currentState()) currentState()->update(*this, dt);

        window.clear();
        if (currentState()) currentState()->render(*this, window);
        window.display();
    }
}

void Game::pushState(const std::string& name) {
    stateStack.push_back(registry.getState(name));
}

void Game::popState() {
    if (!stateStack.empty()) stateStack.pop_back();
}

GameState* Game::currentState() {
    return stateStack.empty() ? nullptr : stateStack.back().get();
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

void Game::quit() {
    isRunning = false;
    window.close();
}