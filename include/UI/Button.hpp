// #pragma once
// #include <functional>
// #include <vector>
// #include <memory>
// #include <SFML/Window/Event.hpp>
// #include <SFML/Graphics.hpp>
// class CanChooseComponent
// {
//     private:
//         std::shared_ptr<sf::Shape> shape;
//         bool isVisible;
//         bool isHover;
//         bool isClicked;

//         std::function<void()> func;
//     public:
//         void setVisible(bool isVisible)
//         {
//             this->isVisible = isVisible;
//         }
//     public:
//         void handleEvent(sf::Event& event)
//         {
//             if (event.type == sf::Event::MouseButtonPressed 
//             && event.mouseButton.button == sf::Mouse::Left) {
//                 // Check if the mouse click is inside the shape's bounds
//                 if (shape->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                     isClicked = true;
//                     click();
//                 }
//             }

//             if (event.type == sf::Event::MouseButtonPressed) {
//                 if (event.mouseButton.button == sf::Mouse::Left) {
//                     // Check if the mouse click is within the bounds of the component
//                     // Add your condition here.
//                     if (/* check if mouse is within the bounds of the component */) {
//                         click();
//                     }
//                 }
//             }
//         }

//         void hover();
//         void click();

//         // virtual void activate() = 0;
//         // void setFunc(std::function<void()> someFunc);

// };

// class ExpandableComponent: public CanChooseComponent
// {
//     private:
//         std::vector<std::shared_ptr<CanChooseComponent>> ChildComponent;
//     public:
//         // void activate() override
//         // {

//         // }        

// };

// class Button: public CanChooseComponent
// {
//     private:
    
//     public:

// };  

#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <iostream>
struct StateColor
{
    sf::Color normal;
    sf::Color hover;
    sf::Color outline;
    sf::Color activeOutline;

    StateColor(
        const sf::Color& normalColor = sf::Color::Blue,
        const sf::Color& outlineColor = sf::Color::White,
        const sf::Color& activeOutlineColor = sf::Color::Red):
        normal(normalColor), outline(outlineColor), activeOutline(activeOutlineColor) {
            this->hover = getHoverColor();
        } 
    
    sf::Color darkenColor(const sf::Color& color, int amount) const
    {
        int r = std::max(color.r - amount, 0);
        int g = std::max(color.g - amount, 0);
        int b = std::max(color.b - amount, 0);

        return sf::Color(r, g, b);
    }

    // Function to get the hover color (darkened)
    sf::Color getHoverColor() const
    {
        return darkenColor(normal, 50);
    }
};
class Button
{
    private:
        std::shared_ptr<sf::Shape> shape;
        bool canHover;
        bool canClick;
        // bool canHandleEventWhileActivate;

        bool isHovered;
        bool isClicked;

        StateColor colorSetting;

        sf::Text text;
        std::function<void()> func;

    public:
        bool getIsClicked() 
        {
            return isClicked;
        }
        bool getIsHovered()
        {
            return isHovered;
        }
        // Button(
        //     const sf::Vector2f& size,           
        //     const sf::Vector2f& position,       
        //     const StateColor& colors,
        //     const sf::Text& text,           
        //     bool canHover = true,               
        //     bool canClick = true
        // )
        //     : canHover(canHover), canClick(canClick), isHovered(false), isClicked(false), colorSetting(colors), text(text)
        // {
        //     // shape
        //     shape = std::make_shared<sf::RectangleShape>(size);
        //     shape->setFillColor(colorSetting.normal);
        //     shape->setOutlineColor(colorSetting.outline); 
        //     shape->setOutlineThickness(2.f);
        //     setShapeCenter(*shape, position);
        //     // text
        //     this->text.setPosition(
        //         shape->getPosition().x - text.getGlobalBounds().width,
        //         shape->getPosition().y - text.getGlobalBounds().height
        //     );

        // }
        Button(
            const sf::Text& text,
            std::shared_ptr<sf::Shape> newShape,
            const StateColor& newColorSetting,
            bool canHover = true,
            bool canClick = true
            // bool canHandleEventWhileActivate = false
        ): isHovered(false), isClicked(false)
        {
            // this->canHandleEventWhileActivate = canHandleEventWhileActivate;
            this->canHover = canHover;
            this->canClick = canClick;
            setShape(newShape); 
            setText(text);
            setColorState(newColorSetting);
        }
        
        void setText(const sf::Text& text)
        {
            this->text = text;
            if (shape)
            {
                this->text.setPosition(
                shape->getPosition().x - text.getGlobalBounds().width / 2,
                shape->getPosition().y - text.getGlobalBounds().height / 2 - 10.f
            );
            }
        }

        void setContent(std::string content)
        {
            this->text.setString(content);
            if (shape)
            {
                this->text.setPosition(
                shape->getPosition().x - this->text.getGlobalBounds().width / 2,
                shape->getPosition().y - this->text.getGlobalBounds().height / 2 - 10.f
            );
            }
        }
        void setShape(std::shared_ptr<sf::Shape> newShape)
        {
            shape = newShape;
            setShapeCenter(*shape, newShape->getPosition());
        }


        void setColorState(const StateColor& newColorSetting)
        {
            colorSetting = newColorSetting;
            if (shape) 
            {
                shape->setFillColor(colorSetting.normal); 
                shape->setOutlineColor(colorSetting.outline);
                shape->setOutlineThickness(2.f);
            }
        }
        void setFunc(std::function<void()> func)
        {
            this->func = func;
        }
        void hover()
        {
            if (!canHover) return;
            isHovered = true;
            // logic hover
        }
        void activate()
        {
            if (!canClick) return;
            isClicked = true;
            if (func) func();
        }
        void unhover()
        {
            if (!canHover) return;
            isHovered = false;
        } 
        void deactivate() 
        {
            if (!canClick) return;
            isClicked = false;
        }
        void handleEvent(const sf::Event& event)
        {
            
            if (event.type == sf::Event::MouseButtonPressed 
            && event.mouseButton.button == sf::Mouse::Left) 
            {
                if (!shape->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) deactivate();
                else {
                    activate();
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (!shape->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    unhover();
                else hover();
            }

        }
        void render(sf::RenderWindow& window)
        {
            if (!isHovered){
                shape->setFillColor(colorSetting.normal);
                }
            else
            {
                shape->setFillColor(colorSetting.hover);
            }
            if (!isClicked)
                shape->setOutlineColor(colorSetting.outline);
            else
                shape->setOutlineColor(colorSetting.activeOutline);

            window.draw(*shape);
            window.draw(text);
        }
};
