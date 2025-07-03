#include <iostream>
#include <string>
#include <thread>
#include <raylib.h>
#include "handler.h"
#include "keyInput.h"
#include "UI.h"
#include "levelHandler.h"
using namespace std;

class Runnable
{
};
class Game : public Runnable
{
public:
    Game(int screenWidth = 0, int screenHeight = 0, UI *ui = nullptr);
    void main(std::string args[]);
    void run();
    ~Game() = default; // Default destructor
    void initialize();
    void start();
    void stop();
    void tick();
    void render();
    bool shouldExit();

private:
    // Game constants
    static const int MILLIS_PER_SEC;
    static const int NANOS_PER_SEC;
    static const double NUM_TICKS;

    int screenWidth, screenHeight;
    // UI *ui;
    //  Game variables
    bool running;

    // Game components
    // std::thread thread;
    // Handler handler;
    Camera2D camera;
    LevelHandler levelHandler;
    KeyInput keyInput{levelHandler.getHandler()}; // KeyInput instance initialized with handler
    long long nanoTime();
    long long currentTimeMillis();
};