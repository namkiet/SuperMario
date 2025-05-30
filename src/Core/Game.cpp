#include <Core/Game.hpp>

Game::Game()
    : contextSettings(0, 0, 16)
    , window(sf::VideoMode(1600, 900), "Super Mario Bros!", sf::Style::Default, contextSettings)
    , shape(50.f)
{
    shape.setFillColor(sf::Color::Green);   
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
    shape.setPosition(shape.getPosition() + sf::Vector2f(100, 20) * dt);
}

void Game::draw()
{

    window.clear(sf::Color(245, 245, 245));
    window.draw(shape);
    window.display();
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvent();
        float dt = clock.restart().asSeconds();
        update(dt);
        draw();
    }
}