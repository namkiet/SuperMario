#pragma once
#include "handler.h"

#include "raylib.h"
#include "UI.h"
class LevelHandler
{
private:
    Image levelImage;
    Image characterImage;
    Image backgroundImage;
    
    Handler handler;
    UI *ui;
    
    void loadImage();
    void setLevel();
    void levelCharacter();
    void setEnemy();
    void setBackground();

public:
    LevelHandler(Handler handler = Handler(), UI *ui = nullptr);
    
    Handler &getHandler() { return handler; }
    void start();
    ~LevelHandler();
};