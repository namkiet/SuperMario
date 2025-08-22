// === Game.cpp ===
#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <States/SettingsState.hpp>
#include <Core/Variables.hpp>
#include <States/KeySettingState.hpp>

Game::Game()
    : contextSettings(0, 0, 16), window(sf::VideoMode(SIZE::SCREEN.x, SIZE::SCREEN.y), "Game", sf::Style::Default, contextSettings)
{
    window.setFramerateLimit(90);
    if (!backgroundMusic.openFromFile("assets/Sounds/Background.mp3")) {
    std::cerr << "Could not load music\n";
    }
    else {
    backgroundMusic.setLoop(true); 
    backgroundMusic.setVolume(50.f);
    backgroundMusic.play();       
    }

    // load textureholder
    textureHolder.load(TexType::background, "assets/Background/MenuBackground.png");
    textureHolder.load(TexType::close, "assets/UI/close.png");
    textureHolder.load(TexType::settingpanel, "assets/Background/MenuBackground.png");
    textureHolder.load(TexType::home, "assets/UI/home.png");
    textureHolder.load(TexType::soundOn, "assets/UI/soundOn.png");
    textureHolder.load(TexType::sound, "assets/UI/sound.png");
    textureHolder.load(TexType::music, "assets/UI/music.png");
    textureHolder.load(TexType::save, "assets/UI/save.png");
    textureHolder.load(TexType::turnback, "assets/UI/turn-back.png");
    textureHolder.load(TexType::soundOff, "assets/UI/soundOff.png");
    textureHolder.load(TexType::playPanel, "assets/Background/MenuBackground.png");
    textureHolder.load(TexType::marioidling, "assets/Mario/Small/idling.png");
    textureHolder.load(TexType::mariochoose, "assets/Characters/RedMarioActive.png");
    textureHolder.load(TexType::marionotchoose, "assets/Characters/RedMarioNotActive.png");
    textureHolder.load(TexType::luigichoose, "assets/Characters/GreenMarioActive.png");
    textureHolder.load(TexType::luiginotchoose, "assets/Characters/GreenMarioNotActive.png");
    textureHolder.load(TexType::keybutton, "assets/UI/keyButton.png");
    textureHolder.load(TexType::pause, "assets/UI/pause.png");

    registry.registerInstance("menu", std::make_shared<MenuState>(std::shared_ptr<Game>(this)));
    registry.registerInstance("play", std::make_shared<PlayingState>(std::shared_ptr<Game>(this)));
    registry.registerInstance("settings", std::make_shared<SettingsState>(std::shared_ptr<Game>(this)));
// registry.registerInstance("keysettings", std::make_shared<KeySettingState>(std::shared_ptr<Game>(this)));

    pushState("menu");

    ImGui::SFML::Init(window);
}

void Game::run()
{
    sf::Clock clock;
    const float fixedDt = 1.0f / 100.0f; // 60 updates/sec
    float lag = 0.0f;

    while (window.isOpen() && isRunning && (!stateStack.empty() || !currentState()))
    {
        float dt = clock.restart().asSeconds();
        lag += dt;

        // --- Input xử lý mỗi frame ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (currentState())
                currentState()->handleEvent(event);
        }
        
        ImGui::SFML::Update(window, clock.restart());
        if (currentState())
            currentState()->update(dt);

        backgroundMusic.setVolume(SOUND::shouldPlayMusic? 50.f : 0.f);

        window.clear(sf::Color(146, 144, 255, 255));
        if (currentState())
            currentState()->render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void Game::pushState(const std::string &name)
{
    stateStack.push_back(registry.getState(name));
}

void Game::popState()
{
    if (!stateStack.empty())
        stateStack.pop_back();
}

GameState *Game::currentState()
{
    return stateStack.empty() ? nullptr : stateStack.back().get();
}

sf::RenderWindow &Game::getWindow()
{
    return window;
}

void Game::quit()
{
    isRunning = false;
    window.close();
}

StateRegistry &Game::getRegistry()
{
    return registry;
}
TextureHolder& Game::getTexHolder()
{
    return textureHolder;
}