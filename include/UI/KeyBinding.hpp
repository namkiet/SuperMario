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

    public:
        KeyBinding()
        {
            mapping[Action::MoveLeft] = sf::Keyboard::A;
            mapping[Action::MoveRight] = sf::Keyboard::D;
            mapping[Action::MoveUp] = sf::Keyboard::W;
            mapping[Action::MoveDown] = sf::Keyboard::S;
            mapping[Action::Sit] = sf::Keyboard::Space;
            mapping[Action::Shoot] = sf::Keyboard::Enter;
        }
        void setKey(Action action, sf::Keyboard::Key key)
        {
            mapping[action] = key;
        }
        sf::Keyboard::Key getKey(Action action) const
        {
            return mapping.at(action);   
        }
        friend class KeySettingState;
};