#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

class LevelObserver
{
public:
    virtual ~LevelObserver() = default;
    virtual void onLevelChanged(int newScore) = 0;
};

class LevelManager
{
private:
    int level = 1;
    std::string status = "playing";
    bool skipUpdate = false;
    bool shouldLoadNextLevel = false;

    std::vector<LevelObserver *> observers;

    // Singleton: private constructor and deleted copy/move
    LevelManager() = default;
    LevelManager(const LevelManager &) = delete;
    LevelManager &operator=(const LevelManager &) = delete;

public:
    static LevelManager &instance()
    {
        static LevelManager instance;
        return instance;
    }

    void addObserver(LevelObserver *observer)
    {
        observers.push_back(observer);
        observer->onLevelChanged(level); // Notify new observer of current score
    }

    void setLevel(int newLevel)
    {
        // std::cout << "Setting level to " << newLevel << std::endl;
        if (newLevel == 0)
        {
            // Keep the level unchanged
            // level = level;
        }
        else
            level = newLevel;

        for (auto &observer : observers)
        {
            observer->onLevelChanged(level);
        }
    }
    ~LevelManager()
    {
        for (auto &observer : observers)
        {
            delete observer;
        }
        observers.clear();
    }
    int getLevel() const
    {
        return level;
    }
    void reset()
    {
        level = 1;
        for (auto &observer : observers)
        {
            observer->onLevelChanged(level);
        }
    }

    bool getSkipUpdate() const
    {
        return skipUpdate;
    }

    void setSkipUpdate(bool value)
    {
        skipUpdate = value;
    }

    std::string getStatus()
    {
        return status;
    }

    void setStatus(const std::string &newStatus)
    {
        status = newStatus;
    }

    bool getShouldLoadNextLevel()
    {
        return shouldLoadNextLevel;
    }
    void setShouldLoadNextLevel(bool value)
    {
        shouldLoadNextLevel = value;
    }
};

class LevelUI : public LevelObserver
{
private:
    int level = 0;
    sf::Font font;

public:
    LevelUI()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void onLevelChanged(int newLevel) override
    {
        level = newLevel;
    }
    void draw(sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());

        sf::Text worldName = textRender("WORLD", 500.f, 35.f, font, 25);
        sf::Text mapName;

        // Render map name based on the current level
        switch (level)
        {
        case 1:
            mapName = textRender("1-1", 520.f, 65.f, font, 25);
            break;
        case 2:
            mapName = textRender("6-1", 520.f, 65.f, font, 25);
            break;
        case 3:
            mapName = textRender("5-4", 520.f, 65.f, font, 25);
            break;
        default:
            mapName = textRender("Unknown Level", 520.f, 65.f, font, 25);
        }

        // Draw world name and map name
        window.draw(worldName);
        window.draw(mapName);
    }
};