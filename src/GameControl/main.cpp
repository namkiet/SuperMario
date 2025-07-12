#include <iostream>
#include "app.h"
using namespace std;

int main()
{
    App app(960, 720);
    app.run();
    return 0;
}

// #include <SFML/Audio.hpp>
// #include <SFML/System.hpp>
// #include <iostream>
// int main()
// {
//     sf::SoundBuffer buffer;
//     if (!buffer.loadFromFile("C:/Minh Tam/Mario_ecs/assets/Sounds/jump.wav"))
//     {
//         std::cout << "Failed to load sound!" << std::endl;
//         return -1;
//     }
//     sf::Sound sound(buffer);
//     sound.play();
//     sf::sleep(sf::seconds(2));
//     // std::cout << "SFML version: "
//     //           << SFML_VERSION_MAJOR << "."
//     //           << SFML_VERSION_MINOR << "."
//     //           << SFML_VERSION_PATCH << std::endl;

//     return 0;
// }