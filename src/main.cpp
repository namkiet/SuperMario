#include <Game.hpp>
#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }

    return 0;
}