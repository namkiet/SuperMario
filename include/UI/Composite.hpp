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
    // for shape

    sf::Color normalText;
    sf::Color hoverText;

    StateColor(sf::Color hoverColor, sf::Color normalColor = sf::Color(255, 255, 255, 0), sf::Color normalText = sf::Color::White, sf::Color hoverText = sf::Color::White)
        : normal(normalColor),
          hover(hoverColor),
          normalText(normalText),
          hoverText(hoverText)
    {
    }
    StateColor()
        : normal(sf::Color(255, 255, 255, 0)),
          hover(sf::Color(255, 255, 255, 50)),
          normalText(sf::Color::White),
          hoverText(sf::Color::White)
    {
    }
};

struct DrawableElement
{
    std::shared_ptr<sf::Shape> shape;
    std::shared_ptr<sf::Sprite> sprite;
    sf::Text text;

    std::function<bool(sf::Vector2f)> containsFn;

    // ======CircleShape===========
    DrawableElement(std::shared_ptr<sf::CircleShape> circle) : shape(circle)
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
    DrawableElement(std::shared_ptr<sf::RectangleShape> shape) : shape(shape)
    {
        containsFn = [shape](sf::Vector2f pos)
        {
            return shape->getGlobalBounds().contains(pos);
        };
    }
    DrawableElement(std::shared_ptr<RoundedRectangleShape> roundedRect) : shape(roundedRect)
    {
        containsFn = [roundedRect](sf::Vector2f pos)
        {
            return roundedRect->contains(pos);
        };
    }
    // ======Other Shape==========
    DrawableElement(std::shared_ptr<sf::Shape> shape) : shape(shape)
    {
        containsFn = [shape](sf::Vector2f pos)
        {
            return shape->getGlobalBounds().contains(pos);
        };
    }
    DrawableElement() {}

    DrawableElement(std::shared_ptr<sf::Sprite> spr)
        : sprite(std::move(spr))
    {
        if (sprite)
        {
            containsFn = [this](sf::Vector2f pos)
            {
                return sprite->getGlobalBounds().contains(pos);
            };
        }
    }
    // setter
    void setText(const sf::Text &newText)
    {
        text = newText;
    }
    void setSprite(std::shared_ptr<sf::Sprite> spr)
    {

        sprite = std::move(spr);
        if (!shape || !sprite)
            return;
        sf::FloatRect shapeBounds = shape->getGlobalBounds();
        resizeSprite(*sprite, {shapeBounds.width, shapeBounds.height});
        sprite->setPosition(shapeBounds.left, shapeBounds.top);
    }
    void draw(sf::RenderWindow &window)
    {
        if (sprite)
            window.draw(*sprite);

        if (shape)
            window.draw(*shape);
        window.draw(text);
    }
    bool contains(sf::Vector2f pos)
    {
        if (containsFn)
            return containsFn(pos);
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
    Interact(const StateColor &newcolorSetting, bool toggle = false) : colorSetting(newcolorSetting)
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
            if (!toggle)
                deactivate();
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
    bool getIsActive() const { return isActive; }
    bool getIsHovered() const { return isHovered; }

    // setter
    void setActive(bool active)
    {
        if (!canActive)
            return;
        if (active == false)
        {
            // std::cout << "set deActive is call" << std::endl;
        }
        isActive = active;
    }
    void setHover(bool hover)
    {
        if (!canHover)
            return;
        isHovered = hover;
    }

    friend class InteractUI;
};

struct InteractUI
{
    Interact interact;
    std::shared_ptr<DrawableElement> drawableEle;

    InteractUI(const Interact &inter, std::shared_ptr<DrawableElement> drawable)
        : interact(inter), drawableEle(std::move(drawable)) {}

    // add setter and getter
    bool getIsActive()
    {
        return interact.getIsActive();
    }
    void setText(std::string text)
    {
        drawableEle->text.setString(text);
        if (drawableEle->shape)
        {

            auto tb = drawableEle->text.getLocalBounds();

            // Tính toán vị trí để căn giữa văn bản trong shape
            sf::Vector2f shapeSize = sf::Vector2f(drawableEle->shape->getGlobalBounds().width, drawableEle->shape->getGlobalBounds().height);

            // Căn giữa văn bản trong shape
            drawableEle->text.setPosition(
                drawableEle->shape->getPosition().x + (shapeSize.x - tb.width) * 0.5f - tb.left,
                drawableEle->shape->getPosition().y + (shapeSize.y - tb.height) * 0.5f - tb.top);
        }
    }
    void setTextPos(sf::Vector2f pos)
    {
        drawableEle->text.setPosition(pos);
    }
    void setSpritePos(sf::Vector2f pos)
    {
        drawableEle->sprite->setPosition(pos);
    }
    void setSprite(std::shared_ptr<sf::Sprite> spr)
    {
        drawableEle->setSprite(spr);
    }

    void updateColor()
    {
        auto &inter = interact;
        auto shape = drawableEle->shape;
        if (shape)
        {

            shape->setFillColor((inter.getIsActive() || inter.getIsHovered())
                                    ? inter.colorSetting.hover
                                    : inter.colorSetting.normal);
        }
        drawableEle->text.setFillColor((inter.getIsActive() || inter.getIsHovered())
                                           ? inter.colorSetting.hoverText
                                           : inter.colorSetting.normalText);
    }
    void draw(sf::RenderWindow &window)
    {
        updateColor();
        drawableEle->draw(window);
    }
};
// hien tai neu nhan hut la tu dong deactivate luon, co van de

// ==============================================================================
class UIComponent
{
protected:
    std::shared_ptr<InteractUI> component;

public:
    UIComponent() = default;
    explicit UIComponent(std::shared_ptr<InteractUI> comp)
        : component(std::move(comp)) {}

    virtual ~UIComponent() = default;
    virtual void draw(sf::RenderWindow &window)
    {
        component->draw(window);
    } // co the draw cung khong xai chung
    virtual bool handleEvent(const sf::Event &event) = 0;
    bool getIsActive() const
    {
        return component && component->getIsActive();
    }
    void setActive(bool on)
    {
        if (component)
            component->interact.setActive(on);
    }
    void setHover(bool on)
    {
        if (component)
            component->interact.setHover(on);
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

class Button : public UIComponent
{
private:
    std::function<void()> func;

public:
    explicit Button(std::shared_ptr<InteractUI> comp) : UIComponent(std::move(comp)) {}

    void setFunc(std::function<void()> func)
    {
        this->func = func;
    }
    bool handleEvent(const sf::Event &event) override
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                // if (component->interact.deactivate()) {}
            }
            else
            {
                if (component->interact.activate())
                {
                    if (func)
                        func();
                }
                else
                    component->interact.deactivate();
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                component->interact.unhover();
            else
                component->interact.hover();
        }
        return true;
    }
    void draw(sf::RenderWindow &window)
    {
        component->draw(window);
    }
};

class UIContainer : public UIComponent
{
protected:
    std::vector<std::shared_ptr<UIComponent>> ComponentList;

public:
    explicit UIContainer(std::shared_ptr<InteractUI> comp)
        : UIComponent(std::move(comp)) {}

    virtual void addComponent(std::shared_ptr<UIComponent> ele)
    {
        ComponentList.push_back(ele);
    }
    // void setComponent(std::vector<std::shared_ptr<UIComponent>> list)
    // {
    //     ComponentList = list;
    // }
    void sortComponentList()
    {
        std::stable_sort(ComponentList.begin(), ComponentList.end(),
                         [](const std::shared_ptr<UIComponent> &a, const std::shared_ptr<UIComponent> &b)
                         {
                             return !a->getIsActive() && b->getIsActive();
                         });
    }

public:
    void draw(sf::RenderWindow &window) override
    {
        sortComponentList();
        if (!getIsActive())
            return;
        UIComponent::draw(window); // draw itself first
        for (auto &component : ComponentList)
        {
            component->draw(window); // draw its children later
        }
    }
    bool handleEvent(const sf::Event &event) override
    {
        sortComponentList();
        if (!getIsActive())
            return true; // return if not active
        for (auto it = ComponentList.rbegin(); it != ComponentList.rend(); ++it)
        {

            // std::cout << "mid handle event in uicontainer" << std::endl;
            if (!(*it)->handleEvent(event))
                return false; // handle event for children in reverse order

            // std::cout << "after mid uicontainer handle event" << std::endl;
        }

        // std::cout << "end handle event in uicontainer" << std::endl;
        return true;
    }
};

class Panel : public UIContainer
{
private:
    sf::Keyboard::Key activeKey;
    // helper func
public:
    Panel(std::shared_ptr<InteractUI> comp, sf::Keyboard::Key k = sf::Keyboard::Unknown)
        : UIContainer(std::move(comp)), activeKey(k) {}

    void setActiveKey(sf::Keyboard::Key k) { this->activeKey = k; }

    static void drawOverlay(sf::RenderWindow &window)
    {
        sf::RectangleShape overlay;
        overlay.setSize(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 220));
        window.draw(overlay);
    }

    void draw(sf::RenderWindow &window) override
    {
        if (!component->getIsActive())
            return;
        drawOverlay(window);
        UIContainer::draw(window);
    }
    bool handleEvent(const sf::Event &event) override
    {
        UIContainer::handleEvent(event);
        // std::cout << "can go here" << std::endl;
        if (activeKey != sf::Keyboard::Unknown && event.type == sf::Event::KeyPressed && event.key.code == activeKey)
        {
            this->setActive(true);
        }
        return (!getIsActive()); // avoid propagate event to its ancestor if it is active
    }
};
class OptionContainer : public UIContainer
{
private:
    std::shared_ptr<UIComponent> activeComponent;
    std::function<void(const sf::Event &)> func;
    bool mustHaveOption;

public:
    OptionContainer(std::shared_ptr<InteractUI> comp, bool mustHaveOp = false)
        : UIContainer(comp), activeComponent(nullptr), mustHaveOption(mustHaveOp)
    {
    }

    void setFunc(std::function<void(const sf::Event &)> func)
    {
        this->func = func;
    }

    void addComponent(std::shared_ptr<UIComponent> ele) override
    {
        ComponentList.push_back(ele);
        if (ComponentList.size() == 1)
            activeComponent = ele;
    }

    std::shared_ptr<UIComponent> getActiveComponent()
    {
        return activeComponent;
    }

    bool handleEvent(const sf::Event &event) override
    {
        sortComponentList();

        if (mustHaveOption)
            assert(activeComponent != nullptr);

        std::shared_ptr<UIComponent> tempActiveComponent = activeComponent;

        for (int i = ComponentList.size() - 1; i >= 0; i--)
        {
            if (!ComponentList[i]->handleEvent(event))
                return false;

            if (ComponentList[i]->getIsActive())
            {
                tempActiveComponent = ComponentList[i];
            }
        }

        if (tempActiveComponent != activeComponent)
        {
            if (activeComponent)
                activeComponent->setActive(false);
            activeComponent = tempActiveComponent;
        }
        else
        {
            if (activeComponent && !activeComponent->getIsActive())
            {
                if (!mustHaveOption)
                    activeComponent = nullptr;
                else
                    activeComponent->setActive(true);
            }
        }

        if (func && activeComponent)
        {
            func(event);
        }

        return true;
    }
};

class ExpandableButton : public UIContainer
{
public:
    bool handleEvent(const sf::Event &event) override
    {
        UIContainer::handleEvent(event);

        // handle for it later
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                if (component->interact.deactivate())
                {
                }
            }
            else
            {
                if (component->interact.activate())
                {
                }
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (!component->drawableEle->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                component->interact.unhover();
            else
                component->interact.hover();
        }
        return true;
    }
};

class StaticComponent : public UIComponent
{
public:
    StaticComponent(std::shared_ptr<InteractUI> interactui) : UIComponent(interactui) {}
    bool handleEvent(const sf::Event &event) override
    {
        // Nothing here
        return true;
    }
    // void draw(sf::RenderWindow& window) override
    // {
    //     component->draw(window);
    // }
};
