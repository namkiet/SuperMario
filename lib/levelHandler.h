#pragma once
#include "handler.h"

#include "raylib.h"
#include "UI.h"
class LevelHandler
{
private:
    Image levelImage;
    Image characterImage;
    Handler handler;
    UI *ui;

public:
    LevelHandler(Handler handler = Handler(), UI *ui = nullptr);
    void loadImage();
    void setLevel();
    void levelCharacter();
    void setEnemy();
    Handler &getHandler() { return handler; }
    void start();
    ~LevelHandler();
};