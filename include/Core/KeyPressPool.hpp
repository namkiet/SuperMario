#pragma once
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>

class KeyPressPool
{
    private:
        std::unordered_set<sf::Keyboard::Key> keyStates;
    private:
        KeyPressPool() = default;
    
    public:
        static KeyPressPool& Instance()
        {
            static KeyPressPool instance;
            return instance;
        }
        KeyPressPool(const KeyPressPool&) = delete;
        KeyPressPool& operator=(const KeyPressPool&) = delete;
        KeyPressPool(KeyPressPool&&) = delete;
        KeyPressPool& operator=(KeyPressPool&&) = delete;
        void addKey(sf::Keyboard::Key key)
        {
            keyStates.insert(key);
        }
        void clear()
        {
            keyStates.clear();
        }
        bool isKeyPressed(sf::Keyboard::Key key) const
        {
            return keyStates.find(key) != keyStates.end();
        }
};