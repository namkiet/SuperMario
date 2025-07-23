#include <Game.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
int main()
{
    std::ofstream fout("output.txt");
    if (fout.fail())
    {
        std::cerr << "Failed to open output.txt for writing." << std::endl;
        return 1;
    }
    try
    {

        Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }
    fout.close();
    return 0;
}