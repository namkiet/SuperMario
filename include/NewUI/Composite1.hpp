#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <Engine/Rendering/Utility.hpp>
#include <UI/roundedRectShape.hpp>
#include <iostream>
struct StateColor
{
    sf::Color normal;
    sf::Color hover;

    StateColor(sf::Color hoverColor, sf::Color normalColor = sf::Color(255, 255, 255, 0))
        : normal(normalColor),
          hover(hoverColor)
    {}
    StateColor()
        : normal(sf::Color(255, 255, 255, 0)), 
          hover(sf::Color(255, 255, 255, 50)) 
    {}
};


struct DrawableElement
{
    std::shared_ptr<sf::Shape> shape;
    std::shared_ptr<sf::Sprite> sprite;
    sf::Text text;

    std::function<bool(sf::Vector2f)> containsFn;

    // ======CircleShape===========
    DrawableElement(std::shared_ptr<sf::CircleShape> circle): shape(circle)
    {
        containsFn = [circle](sf::Vector2f pos)
        {
            float radius = circle->getRadius();
            sf::Vector2f center = circle->getPosition();
            center += sf::Vector2f(radius, radius);
            float dx = pos.x - center.x;
            float dy = pos.y - center.y;
            return (dx * dx + dy * dy) <= (radius * radius);
        };
    }
    DrawableElement(std::shared_ptr<RoundedRectangleShape> roundedRect): shape(roundedRect)
    {
        containsFn = [roundedRect](sf::Vector2f pos)
        {
            return roundedRect->contains(pos);
        };
    }
    // ======Other Shape==========
    DrawableElement(std::shared_ptr<sf::Shape> shape) : shape(shape) {
        containsFn = [shape](sf::Vector2f pos) {
            return shape->getGlobalBounds().contains(pos);
        };
    }
    DrawableElement(){}

    // ====== Sprite only ===========
    // DrawableElement(std::shared_ptr<sf::Sprite> spr)
    // : sprite(std::move(spr))
    // {
    //     if (sprite) {
    //         auto bounds = sprite->getGlobalBounds();
    //         auto rectShape = std::make_shared<sf::RectangleShape>(
    //             sf::Vector2f(bounds.width, bounds.height)
    //         );
    //         rectShape->setPosition(bounds.left, bounds.top);
    //         shape = rectShape; // shape = globalbound of sprite

    //         containsFn = [rectShape](sf::Vector2f pos) {
    //             return rectShape->getGlobalBounds().contains(pos);
    //         };
    //     }
    // }
    DrawableElement(std::shared_ptr<sf::Sprite> spr)
    : sprite(std::move(spr))
{
    if (sprite) {
        containsFn = [this](sf::Vector2f pos) {
            return sprite->getGlobalBounds().contains(pos);
        };
    }
}
    // setter
    void setText(const sf::Text& newText)
    {
        text = newText;
    }
    void setSprite(std::shared_ptr<sf::Sprite> spr)
    {

        sprite = std::move(spr);
        
        if (!shape || !sprite) return;

        sf::FloatRect shapeBounds = shape->getGlobalBounds();
        resizeSprite(*sprite, {shapeBounds.width, shapeBounds.height});
        sprite->setPosition(shapeBounds.left, shapeBounds.top);
    }

    void draw(sf::RenderWindow& window) {
        if (shape) window.draw(*shape);
        if (sprite) window.draw(*sprite);
        window.draw(text);
    }
    bool contains(sf::Vector2f pos) 
    {
        if (containsFn) return containsFn(pos);
        return false;
    }
};

class Interact
{
    private:
        bool canHover = true;
        bool canActive = true;
        bool toggle;
        bool isHovered = false;
        bool isActive = false;
        StateColor colorSetting;
    public:
        Interact(const StateColor& newcolorSetting, bool toggle = false):
        colorSetting(newcolorSetting)
        {
            this->toggle = toggle;
        }
    public:
        void setCanHover(bool a)
        {
            canHover = a;
        }
        void setCanActive(bool a)
        {
            canActive = a;
        }
        bool activate() 
        { 
            if (canActive && !isActive) 
            { 
                isActive = true;  
                if (!toggle) deactivate();
                return true;
            } 
            return false;
        }
        bool deactivate()  
        { 
            if (canActive && isActive) 
            { 
                isActive = false; 
                return true;
            } 
            return false;
        }
        bool hover()       
        { 
            if (canHover && !isHovered)
            { 
                isHovered = true; 
                return true;      
            } 
            return false;
        }
        bool unhover()     
        { 
            if (canHover && isHovered)
            { 
                isHovered = false;
                return true;
            } 
            return false;
        }
        
        // getter
        bool getIsActive()  const { return isActive;  }
        bool getIsHovered() const { return isHovered; }

        // setter
        void setActive(bool active)
        {
            if (!canActive) return;
            isActive = active;
        }
        void setHover(bool hover)
        {
            if (!canHover) return;
            isHovered = hover;
        }

        friend class InteractUI;
};

struct InteractUI
{
    Interact interact;
    std::shared_ptr<DrawableElement> drawableEle;

    InteractUI(const Interact& inter, std::shared_ptr<DrawableElement> drawable)
    : interact(inter), drawableEle(std::move(drawable)) {}


    // add setter and getter
    bool getIsActive()
    {
        return interact.getIsActive();
    }
    void setText(std::string text)
    {
        // Cập nhật văn bản
        drawableEle->text.setString(text);
        if (drawableEle->shape)
        {
            // Tính toán kích thước của văn bản và của shape (ví dụ: hình chữ nhật, hình tròn, v.v.)
            auto tb = drawableEle->text.getLocalBounds();  // Lấy kích thước của văn bản

            // Tính toán vị trí để căn giữa văn bản trong shape
            sf::Vector2f shapeSize = sf::Vector2f(drawableEle->shape->getGlobalBounds().width, drawableEle->shape->getGlobalBounds().height);

            // Căn giữa văn bản trong shape
            drawableEle->text.setPosition(
                drawableEle->shape->getPosition().x + (shapeSize.x - tb.width) * 0.5f - tb.left,  // Căn giữa theo chiều ngang
                drawableEle->shape->getPosition().y + (shapeSize.y - tb.height) * 0.5f - tb.top   // Căn giữa theo chiều dọc
            );
        }
    }
    void setTextPos(sf::Vector2f pos)
    {
        drawableEle->text.setPosition(pos);
    }
    void setSprite(std::shared_ptr<sf::Sprite> spr)
    {
        std::cout << "at least it goes to interactui" << std::endl;
        drawableEle->setSprite(spr);
    }

    void updateColor() {
        auto& inter = interact;
        auto shape = drawableEle->shape;
        if (shape) 
        {
            // if (inter.getIsActive() || inter.getIsHovered())
            // {
            //     shape->setFillColor(inter.colorSetting.hover);
            //     // std::cout << "hover" << std::endl;
            // }
            // else
            // {
            //     shape->setFillColor(inter.colorSetting.normal);
            // }
            shape->setFillColor((inter.getIsActive() || inter.getIsHovered())
                                ? inter.colorSetting.hover
                                : inter.colorSetting.normal);
        }
        // Optionally update text color too.
    }
    void draw(sf::RenderWindow& window)
    {
        // std::cout << "predraw line 181 ok" << std::endl;
        updateColor();
                // std::cout << "draw line 183 ok" << std::endl;
        drawableEle->draw(window);
                // std::cout << "draw line 185 ok" << std::endl;
    }
};
// hien tai neu nhan hut la tu dong deactivate luon, co van de


// ==============================================================================
class UIComponent {
protected:
    std::shared_ptr<InteractUI> component;
public:
    UIComponent() = default;
    explicit UIComponent(std::shared_ptr<InteractUI> comp)
        : component(std::move(comp)) {}
    
    virtual ~UIComponent() = default;
    virtual void draw(sf::RenderWindow& window) 
    {
        component->draw(window);
    } // co the draw cung khong xai chung
    virtual bool handleEvent(const sf::Event& event) = 0;
    bool getIsActive() const 
    { 
        return component && component->getIsActive(); 
    }
    void setActive(bool on) 
    {
        if (component) component->interact.setActive(on);
    }
    void setHover(bool on)
    {
        if (component) component->interact.setHover(on);
    }
    void setText(std::string text)
    {
        component->setText(text);
    }
    void setSprite(std::shared_ptr<sf::Sprite> spr)
    {
        // std::cout << "Ok only" <<std::endl;
        component->setSprite(spr);
    }
};



class Button: public UIComponent
{
    private:
        std::function<void()> func;
    public:
        explicit Button(std::shared_ptr<InteractUI> comp): UIComponent(std::move(comp)) {}

        void setFunc(std::function<void()> func)
        {
            this->func = func;
        }
        bool handleEvent(const sf::Event& event) override
        {
            std::cout << "Button handle event" << std::endl;
            if (event.type == sf::Event::MouseButtonPressed 
            && event.mouseButton.button == sf::Mouse::Left) 
            {
                if (!component->drawableEle->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) 
                {
                    // if (component->interact.deactivate()) {}
                }
                else {
                    if (component->interact.activate())
                    {
                        if (func) func();
                    }
                    else component->interact.deactivate();
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (!component->drawableEle->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) component->interact.unhover();
                else component->interact.hover();
            }
            return true;
        }
        void draw(sf::RenderWindow& window)
        {
            component->draw(window);
        }
};

class UIContainer: public UIComponent
{
    protected:
        std::vector<std::shared_ptr<UIComponent>> ComponentList;
    public:
        explicit UIContainer(std::shared_ptr<InteractUI> comp)
        : UIComponent(std::move(comp)) {}

        void addComponent(std::shared_ptr<UIComponent> ele)
        {
            ComponentList.push_back(ele);
        }
        void setComponent(std::vector<std::shared_ptr<UIComponent>> list)
        {
            ComponentList = list;
        }
        void sortComponentList()
        {
            std::stable_sort(ComponentList.begin(), ComponentList.end(),
                [](const std::shared_ptr<UIComponent>& a, const std::shared_ptr<UIComponent>& b)
                {
                    return !a->getIsActive() && b->getIsActive();
                });
        }
    public:
        void draw(sf::RenderWindow& window) override
        {
            sortComponentList();
            if (!getIsActive()) return;
            UIComponent::draw(window); // draw itself first
            for (auto& component: ComponentList)
            {
                component->draw(window); // draw its children later
            }
        }
        bool handleEvent(const sf::Event& event) override
        {
            sortComponentList();
            // std::cout << "handle event in uicontainer" << std::endl;
            if (!getIsActive()) return true; // return if not active
            for (auto it = ComponentList.rbegin(); it != ComponentList.rend(); ++it)
            {
                
            // std::cout << "mid handle event in uicontainer" << std::endl;
                if (!(*it)->handleEvent(event)) return false; // handle event for children in reverse order
            
            // std::cout << "after mid uicontainer handle event" << std::endl;
            }
            
            // std::cout << "end handle event in uicontainer" << std::endl;
            return true;
        }
        
};

class Panel: public UIContainer
{
    // helper func
    using UIContainer::UIContainer;

    static void drawOverlay(sf::RenderWindow& window)
    {
        sf::RectangleShape overlay;
        overlay.setSize(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 220)); 
        window.draw(overlay);
    }

    void draw(sf::RenderWindow& window) override
    {
        if (!component->getIsActive()) return;
        drawOverlay(window);
        UIContainer::draw(window);
    }
    bool handleEvent(const sf::Event& event) override
    {
        std::cout << "panel handle Event" << std::endl;
        UIContainer::handleEvent(event); 
        return (!getIsActive());// avoid propagate event to its ancestor if it is active
    }

};

class ExpandableButton: public UIContainer
{
    public:
    bool handleEvent(const sf::Event& event) override
    {
        UIContainer::handleEvent(event); // handle for its children first


        // handle for it later
        if (event.type == sf::Event::MouseButtonPressed 
        && event.mouseButton.button == sf::Mouse::Left) 
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) 
            {
                if (component->interact.deactivate()) {}
            }
            else {
                if (component->interact.activate()) {}
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) 
                component->interact.unhover();
            else component->interact.hover();
        }
        return true;
    }
};

class TextUIComponent: public UIComponent
{
    public:
    TextUIComponent(std::shared_ptr<InteractUI> interactui): UIComponent(interactui) {}
    bool handleEvent(const sf::Event& event) override
    {
        // Nothing here
        std::cout << "start text handle event" << std::endl;
        return true;
    }
    void draw(sf::RenderWindow& window) override
    {
        std::cout << "start draw text" << std::endl;
        component->draw(window);
        
        std::cout << "end draw text" << std::endl;
    }
};
