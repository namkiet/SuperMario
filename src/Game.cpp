// === Game.cpp ===
#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <States/SettingsState.hpp>
#include <Core/Variables.hpp>

Game::Game() 
    : contextSettings(0, 0, 16)
    , window(sf::VideoMode(SIZE::SCREEN.x, SIZE::SCREEN.y), "Game", sf::Style::Default, contextSettings)
{
    // window.setFramerateLimit(60);

    registry.registerInstance("menu", std::make_shared<MenuState>());
    registry.registerInstance("play", std::make_shared<PlayingState>());
    registry.registerInstance("settings", std::make_shared<SettingsState>());

    pushState("menu");
}

void Game::run() 
{
    sf::Clock clock;
    const float fixedDt = 1.0f / 100.0f; // 60 updates/sec
    float lag = 0.0f;

    while (window.isOpen() && isRunning && (!stateStack.empty() || !currentState())) 
    {
        float dt = clock.restart().asSeconds();
        lag += dt;

        // --- Input xử lý mỗi frame ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (currentState()) currentState()->handleEvent(*this, event);
        }

        // // --- Update logic vật lý nhiều lần nếu cần ---
        // while (lag >= fixedDt) {
        //     if (currentState()) currentState()->update(*this, fixedDt);
        //     lag -= fixedDt;
        // }


        if (currentState()) currentState()->update(*this, dt);

        // --- Vẽ chỉ 1 lần ---
        window.clear(sf::Color(101, 153, 248));
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