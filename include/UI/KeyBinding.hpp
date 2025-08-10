#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class KeyBinding
{
public:
    enum class Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Sit,
        Shoot,
    };

private:

    std::unordered_map<Action, sf::Keyboard::Key> mapping;

    KeyBinding()
    {
        // Default key mappings
        mapping[Action::MoveLeft] = sf::Keyboard::A;
        mapping[Action::MoveRight] = sf::Keyboard::D;
        mapping[Action::MoveUp] = sf::Keyboard::W;
        mapping[Action::MoveDown] = sf::Keyboard::S;
        mapping[Action::Sit] = sf::Keyboard::Space;
        mapping[Action::Shoot] = sf::Keyboard::M;
    }

    KeyBinding(const KeyBinding&) = delete;
    KeyBinding& operator=(const KeyBinding&) = delete;
    KeyBinding(KeyBinding&&) = delete;
    KeyBinding& operator=(KeyBinding&&) = delete;

public:
    static KeyBinding& Instance()
    {
        static KeyBinding instance;
        return instance;
    }

    void setKey(Action action, sf::Keyboard::Key key)
    {
        for (auto& pair: mapping)
        {
            if (pair.second == key) {
                pair.second = sf::Keyboard::Unknown;
            }
        }
        mapping[action] = key;
    }


    sf::Keyboard::Key getKey(Action action) const
    {
        auto it = mapping.find(action);
        if (it != mapping.end()) {
            return it->second;
        }
        return sf::Keyboard::Unknown;
    }

    ~KeyBinding() = default;
};
