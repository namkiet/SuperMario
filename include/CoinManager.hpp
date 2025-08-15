#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

class CoinObserver
{
public:
    virtual ~CoinObserver() = default;
    virtual void onCoinChanged(int newCoins) = 0;
};

class CoinManager
{
private:
    int coins = 0;
    std::vector<CoinObserver *> observers;

    // Singleton: private constructor and deleted copy/move
    CoinManager() = default;
    CoinManager(const CoinManager &) = delete;
    CoinManager &operator=(const CoinManager &) = delete;

public:
    static CoinManager &instance()
    {
        static CoinManager instance;
        return instance;
    }

    void addObserver(CoinObserver *observer)
    {
        observers.push_back(observer);
        observer->onCoinChanged(coins); // Notify new observer of current score
    }

    void addCoin()
    {
        ++coins;
        std::cout << "Coin added. Total coins: " << coins << std::endl;
        for (auto &observer : observers)
        {
            observer->onCoinChanged(coins);
        }
    }
    ~CoinManager()
    {
        for (auto &observer : observers)
        {
            delete observer;
        }
        observers.clear();
    }
    void reset()
    {
        coins = 0;
        for (auto &observer : observers)
        {
            observer->onCoinChanged(coins);
        }
    }
};

class CoinUI : public CoinObserver
{
private:
    int coins = 0;
    sf::Font font;

public:
    CoinUI()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void onCoinChanged(int newCoins) override
    {
        this->coins = newCoins;
    }
    void draw(sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());

        std::ostringstream coinOss;
        coinOss << "x" << std::setw(2) << std::setfill('0') << coins;
        sf::Text coinValue = textRender(coinOss.str(), 350.f, 65.f, font, 25);

        // Draw coin count
        window.draw(coinValue);
    }
};