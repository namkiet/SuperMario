#pragma once
#include <unordered_map>
#include <memory>
#include <UI/KeyBinding.hpp>
#include <UI/Composite.hpp>
#include <cassert>
#include <string.h>
#include <Engine/Rendering/Utility.hpp>
class ButtonContainer
{
    private:
    std::unordered_map<std::shared_ptr<Button>, KeyBinding::Action> ButtonToAction;
    std::shared_ptr<Button> activeButton;
    public:
    ButtonContainer()
    {
        ButtonToAction.clear();
        activeButton = nullptr;
    }
    void add(std::shared_ptr<Button> button, KeyBinding::Action act)
    {
        assert (ButtonToAction.find(button) == ButtonToAction.end());
        ButtonToAction[button] = act;
    }

    void handleEvent(const sf::Event& event)
    {
        if (activeButton && !activeButton->getIsActive())
            activeButton = nullptr;
        for (auto& pair: ButtonToAction)
        {
            if (pair.first == activeButton) continue;
            // pair.first -> handleEvent(event);
            if (pair.first->getIsActive())
            {
                if (activeButton)
                    activeButton->setActive(false);
                activeButton = pair.first;
            }
        }

        if (!activeButton) 
            return;
        if (event.type == sf::Event::KeyPressed)
        {
            sf::Keyboard::Key key = event.key.code;
            auto& keybinding = KeyBinding::Instance();

            assert (ButtonToAction.find(activeButton) != ButtonToAction.end());
            auto activeAction = ButtonToAction[activeButton];
            keybinding.setKey(activeAction, key);
        }
        updateButtonContent();
    }

    void updateButtonContent()
    {
        auto& keybinding = KeyBinding::Instance();
        for (auto& pair: ButtonToAction)
        {
            std::string content = keyToString(keybinding.getKey(ButtonToAction.at(pair.first)));
            pair.first->setText(content);
        }
    }
    void draw(sf::RenderWindow& window)
    {
        for (auto& pair: ButtonToAction)
        {
            pair.first->draw(window);
        }
    }
};