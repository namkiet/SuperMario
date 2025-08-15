#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

class ScoreObserver
{
public:
    virtual ~ScoreObserver() = default;
    virtual void onScoreChanged(int newScore) = 0;
};

class ScoreManager
{
private:
    int score = 0;
    std::vector<ScoreObserver *> observers;

    // Singleton: private constructor and deleted copy/move
    ScoreManager() = default;
    ScoreManager(const ScoreManager &) = delete;
    ScoreManager &operator=(const ScoreManager &) = delete;

public:
    static ScoreManager &instance()
    {
        static ScoreManager instance;
        return instance;
    }

    void addObserver(ScoreObserver *observer)
    {
        observers.push_back(observer);
        observer->onScoreChanged(score); // Notify new observer of current score
    }
    void addScore(int newScore)
    {
        score += newScore;
        for (auto &observer : observers)
        {
            observer->onScoreChanged(score);
        }
    }
    ~ScoreManager()
    {
        for (auto &observer : observers)
        {
            delete observer;
        }
        observers.clear();
    }
    void reset()
    {
        score = 0;
        for (auto &observer : observers)
        {
            observer->onScoreChanged(score);
        }
    }
};

class ScoreUI : public ScoreObserver
{
private:
    int score = 0;
    sf::Font font;

public:
    ScoreUI()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void onScoreChanged(int newScore) override
    {
        score = newScore;
    }
    void draw(sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());

        // Render player name
        sf::Text player = textRender("MARIO", 100.f, 35.f, font, 25);
        std::ostringstream scoreOss;
        scoreOss << std::setw(6) << std::setfill('0') << score;
        sf::Text score = textRender(scoreOss.str(), 100.f, 65.f, font, 25);

        // Draw player name and score
        window.draw(player);
        window.draw(score);
    }
};