#pragma once
#include <SFML/Graphics.hpp>
#include "handler.h"
#include "UI.h"
class LevelHandler
{
private:
    sf::Image levelImage;
    sf::Image characterImage;
    sf::Image backgroundImage;

    Handler handler;
    UI *ui;
    sf::RenderWindow &window;

    void loadImage();
    void setLevel();
    void levelCharacter();
    void setEnemy();
    void setBackground();

public:
    LevelHandler() = default;
    LevelHandler(Handler handler, UI *ui, sf::RenderWindow &window);

    Handler &getHandler() { return handler; }
    void start();
    ~LevelHandler();
};