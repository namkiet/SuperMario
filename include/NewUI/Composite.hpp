#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>


// struct StateColor
// {
//     sf::Color normal;
//     sf::Color hover;
//     // sf::Color outline;
//     // sf::Color activeOutline;

//     StateColor(
//         const sf::Color& normalColor = sf::Color::Blue,
//         // const sf::Color& outlineColor = sf::Color::White,
//         const sf::Color& activeOutlineColor = sf::Color::Red):
//         normal(normalColor) {
//             this->hover = getHoverColor();
//         } 
    
//     sf::Color darkenColor(const sf::Color& color, int amount) const
//     {
//         int r = std::max(color.r - amount, 0);
//         int g = std::max(color.g - amount, 0);
//         int b = std::max(color.b - amount, 0);

//         return sf::Color(r, g, b);
//     }

//     // Function to get the hover color (darkened)
//     sf::Color getHoverColor() const
//     {
//         return darkenColor(normal, 50);
//     }
// };


struct StateColor
{
    sf::Color normal;
    sf::Color hover;

    StateColor(
        const sf::Color& normalColor = sf::Color(255, 255, 255, 0)
    ) : normal(normalColor) {
        this->hover = getHoverColor();
    } 

    sf::Color brightenColor(const sf::Color& color, int amount) const
    {
        int r = std::min(color.r + amount, 255);
        int g = std::min(color.g + amount, 255);
        int b = std::min(color.b + amount, 255);
        return sf::Color(r, g, b, color.a);
    }

    sf::Color getHoverColor() const
    {
        return brightenColor(normal, 50);
    }
};


struct DrawableElement
{
    std::shared_ptr<sf::Shape> shape;
    std::shared_ptr<sf::Sprite> sprite;
    sf::Text text;

    void draw(sf::RenderWindow& window) {
        if (shape) window.draw(*shape);
        if (sprite) window.draw(*sprite);
        window.draw(text);
    }
    sf::FloatRect getBound() 
    {
        return shape->getGlobalBounds();
    }
};


// ==============================================================================
class UIComponent {
protected:
    std::shared_ptr<DrawableElement> drawableEle;
public:
    UIComponent(std::shared_ptr<DrawableElement> ele): drawableEle(ele) {}
    virtual ~UIComponent() = default;
    virtual void draw(sf::RenderWindow& window) 
    {
        drawableEle->draw(window);
    }
    virtual void handleEvent(const sf::Event& event) = 0;
};


class UIInteractive: public UIComponent
{
    protected:
        bool canHover = true;
        bool canActive = true;
        bool toggle;
        bool isHovered = false;
        bool isActive = false;
        StateColor colorSetting;
    public:
        UIInteractive(const StateColor& newcolorSetting, std::shared_ptr<DrawableElement> drawEle, bool toggle = false):
        UIComponent(drawEle), colorSetting(newcolorSetting)
        {
            this->toggle = toggle;
        }
    public:
        virtual void activate() 
        { 
            if (canActive && !isActive) 
            { 
                isActive = true;  
                onActivate(); 
                if (!toggle) deactivate();
            } 
        }
        virtual void deactivate()  
        { 
            if (canActive && isActive) 
            { 
                isActive = false; 
                onDeactivate(); 
            } 
        }
        virtual void hover()       
        { 
            if (canHover && !isHovered)
            { 
                isHovered = true; 
                onHover();       
            } 
        }
        virtual void unhover()     
        { 
            if (canHover && isHovered)
            { 
                isHovered = false;
                onUnhover();     
            } 
        }

        bool getIsActive()  const { return isActive;  }
        bool getIsHovered() const { return isHovered; }

    protected:
        virtual void onActivate()   
        {
            updateColor();
        }
        virtual void onDeactivate() {updateColor();}
        virtual void onHover()      {updateColor();}
        virtual void onUnhover()    {updateColor();}
    private:
        void updateColor()
        {
            if (!isHovered && !isActive) 
                drawableEle->shape->setFillColor(colorSetting.normal);
            else 
                drawableEle->shape->setFillColor(colorSetting.hover);
        }
};

class Button: public UIInteractive
{
    private:
        std::function<void()> func;
    public:

        void handleEvent(const sf::Event& event) override
        {
            if (event.type == sf::Event::MouseButtonPressed 
            && event.mouseButton.button == sf::Mouse::Left) 
            {
                if (!drawableEle->getBound().contains(event.mouseButton.x, event.mouseButton.y)) deactivate();
                else activate();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (!drawableEle->getBound().contains(event.mouseMove.x, event.mouseMove.y)) unhover();
                else hover();
            }
        }
        void onActivate() override
        {
            UIInteractive::onActivate();
            if (func) func();
        }
    public:
        void setFunc(std::function<void()> func)
        {
            this->func = func;
        }
        Button(const StateColor& newcolorSetting, std::shared_ptr<DrawableElement> drawEle, bool toggle = false):
            UIInteractive(newcolorSetting, drawEle, toggle) {}

};


class UIContainer: public UIComponent
{
    private:
        bool isActive = false;
        std::vector<std::shared_ptr<UIComponent>> ComponentList;
    public:
        void addComponent(std::shared_ptr<UIComponent> ele)
        {
            ComponentList.push_back(ele);
        }
        void setComponent(std::vector<std::shared_ptr<UIComponent>> list)
        {
            ComponentList = list;
        }
    public:
        void draw(sf::RenderWindow& window) override
        {
            if (!isActive) return;
            UIComponent::draw(window);
            for (auto& component: ComponentList)
            {
                component->draw(window);
            }
        }
        void handleEvent(const sf::Event& event) override
        {
            if (!isActive) return;
            for (auto& component: ComponentList)
            {
                component->handleEvent(event);
            }
        }
        
};


class Text: public UIComponent
{
    void handleEvent(const sf::Event& event) override
    {
        // Nothing here
    }
};




// class UIComponent
// {
//     protected:
//         std::shared_ptr<DrawableElement> drawableEle;
//     protected:
//         bool canHover;
//         bool canActive;
//         bool isHovered;
//         bool isActive;
//         StateColor colorSetting;
//     public:
//         virtual void handleEvent(const sf::Event& event) = 0;
//         virtual void draw(sf::RenderWindow &window) 
//         {
//             drawableEle->draw(window);
//         }
//         virtual void activate()
//         {
//             if (!canActive || isActive) return;
//             isActive = !isActive;
//         }
//         virtual void deactivate()
//         {
//             if (!canActive || !isActive) return;
//             isActive = !isActive;
//         }
//         virtual void hover()
//         {

//         }
//         virtual void unhover()
//         {

//         }

// };


// class Button: public UIComponent
// {
//     private:
//         std::function<void()> func;
//     public:
//         // Button(const StateColor& newColorSetting): isHovered(false), isActive(false) {
//         //     colorSetting = newColorSetting;
//         //     if (drawableEle->shape) 
//         //     {
//         //         drawableEle->shape->setFillColor(colorSetting.normal); 
//         //         drawableEle->shape->setOutlineColor(colorSetting.outline);
//         //         drawableEle->shape->setOutlineThickness(2.f);
//         //     }
//         // }
//         void setFunc(std::function<void()> func)
//         {
//             this->func = func;
//         }
//         void handleEvent(const sf::Event& event) override
//         {
//             // should have something here
//         }
// };




// logic the nao?
/*
hover roi thi khong hover nua
chua hover ma unhover thi khong lam
active roi ma activate thi khong lam
chua active ma deactivate thi khong duoc

*/

// nho viet constructor
// co can them 1 lop trung gian nua khong, tuc la chia UI component thanh 2 lop la UIContainer va UIBase


// chua viet onActivate
// chua change color when hover or activate