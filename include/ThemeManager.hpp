#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

class ThemeManager
{
private:
    static int theme;
    static int coin2Theme;

public:
    ThemeManager()
    {
        theme = 1;
    }

    static int getTheme()
    {
        return theme;
    }

    static void setTheme(int newTheme)
    {
        theme = newTheme;
    }

    static int getCoin2Theme()
    {
        return coin2Theme;
    }

    static void setCoin2Theme(int newCoin2Theme)
    {
        coin2Theme = newCoin2Theme;
    }
};
