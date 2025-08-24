#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

class TimeObserver
{
public:
    virtual ~TimeObserver() = default;
    virtual void onTimeChanged(int newScore) = 0;
};

class TimeManager
{
private:
    int timeLeft = 7;
    bool isPaused = false;
    bool goesFaster = false;
    bool firstTimeReach0 = false;
    bool firstTimePause = false;
    int timeUnitLeft = 0;

    std::vector<TimeObserver *> observers;

    // Singleton: private constructor and deleted copy/move
    TimeManager() = default;
    TimeManager(const TimeManager &) = delete;
    TimeManager &operator=(const TimeManager &) = delete;

public:
    static TimeManager &instance()
    {
        static TimeManager instance;
        return instance;
    }

    void addObserver(TimeObserver *observer)
    {
        observers.push_back(observer);
        observer->onTimeChanged(timeLeft);
    }

    void decrementTime()
    {
        if (isPaused && !goesFaster)
            return;

        --timeLeft;
        if (timeLeft < 0)
        {
            timeLeft = 0;
        }
        for (auto &observer : observers)
        {
            observer->onTimeChanged(timeLeft);
        }
    }

    int getTime() const
    {
        return timeLeft;
    }

    ~TimeManager()
    {
        for (auto &observer : observers)
        {
            delete observer;
        }
        observers.clear();
    }

    void setTimePaused(bool paused)
    {
        isPaused = paused;
    }

    void setTimeGoesFaster(bool faster)
    {
        goesFaster = faster;
    }

    bool getTimeGoesFaster() const
    {
        return goesFaster;
    }

    void setFirstTimeReach0(bool first)
    {
        firstTimeReach0 = first;
    }

    void setTimeUnitLeft(int unit)
    {
        timeUnitLeft = unit;
    }

    int getTimeUnitLeft() const
    {
        return timeUnitLeft;
    }

    bool getFirstTimeReach0() const
    {
        return firstTimeReach0;
    }

    void setFirstTimePause(bool first)
    {
        firstTimePause = first;
    }

    bool getFirstTimePause() const
    {
        return firstTimePause;
    }

    bool getIsPaused() const
    {
        return isPaused;
    }

    void reset()
    {
        timeLeft = 7;
        isPaused = false;
        goesFaster = false;
        firstTimeReach0 = false;
        firstTimePause = false;
        timeUnitLeft = 0;

        for (auto &observer : observers)
        {
            observer->onTimeChanged(timeLeft);
        }
    }
};

class TimeUI : public TimeObserver
{
private:
    int time = 0;
    sf::Font font;

public:
    TimeUI()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void onTimeChanged(int newTime) override
    {
        time = newTime;
    }
    void draw(sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());

        // Render time
        sf::Text timeText = textRender("TIME", 660.f, 35.f, font, 25);

        // Render time value
        std::ostringstream timeOss;
        timeOss << std::setw(3) << std::setfill('0') << time;
        sf::Text timeValue = textRender(timeOss.str(), 680.f, 65.f, font, 25);

        // Draw time and time value
        window.draw(timeText);
        window.draw(timeValue);
    }
};