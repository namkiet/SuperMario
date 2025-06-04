#include <Game.hpp>

Game::Game()    
    : contextSettings(0, 0, 16)
    , window(sf::VideoMode(1600, 900), "Super Mario Bros!", sf::Style::Default, contextSettings)
{
    player = std::make_unique<Mario>(100, 200);
    goomba = std::make_unique<Enemy>(500, 100);

    movementSystem.addEntity(player.get());
    renderSystem.addEntity(player.get());

    movementSystem.addEntity(goomba.get());
    renderSystem.addEntity(goomba.get());
}

void Game::handleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }  
}

void Game::update(float dt)
{
    movementSystem.update(dt);
}

void Game::draw()
{
    renderSystem.draw(window);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvent();

        float dt = clock.restart().asSeconds();
        update(dt);

        window.clear(sf::Color(245, 245, 245));
        draw();
        window.display();
    }
}