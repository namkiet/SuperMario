#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <iostream>
MenuState::MenuState(std::shared_ptr<Game> game): GameState(game)
{
    
    font.loadFromFile("arial.ttf");

    // === Background Panel (root) ===
    bgTex_ = std::make_shared<sf::Texture>();
    if (!bgTex_->loadFromFile("assets/Background/MenuBackground.png")) {
        std::cout << "Cannot load menu background\n";
        assert(false);
    }

    auto background = std::make_shared<sf::Sprite>();
    background->setTexture(*bgTex_);

    const auto ws = game->getWindow().getSize();
    resizeSprite(*background, sf::Vector2f((float)ws.x, (float)ws.y));
    background->setPosition(0.f, 0.f);

    auto bgDE = std::make_shared<DrawableElement>(background);

    Interact panelInter(StateColor(), /*toggle=*/true);
    panelInter.setActive(true); // root panel luôn active
    auto panelIU = std::make_shared<InteractUI>(panelInter, bgDE);

    uiRoot = std::make_shared<Panel>(panelIU);
    auto root = std::static_pointer_cast<UIContainer>(uiRoot);

    auto makeButton = [&](sf::Vector2f pos,
                          sf::Vector2f size,
                          const std::string& label,
                          const StateColor& colors,   // normal + hover
                          bool toggle,
                          unsigned int textSize,
                          std::function<void()> onClick) -> std::shared_ptr<Button>
    {
        auto rect = std::make_shared<sf::RectangleShape>(size);
        rect->setPosition(pos);
        rect->setFillColor(colors.normal);

        auto de = std::make_shared<DrawableElement>(std::static_pointer_cast<sf::Shape>(rect));

        sf::Text t;
        t.setFont(font);
        t.setString(label);
        t.setCharacterSize(textSize);
        t.setFillColor(sf::Color::White);
        auto tb = t.getLocalBounds();
        t.setPosition(
            pos.x + (size.x - tb.width) * 0.5f - tb.left,
            pos.y + (size.y - tb.height) * 0.5f - tb.top
        );
        de->setText(t);

        Interact inter(colors, toggle);
        auto iu = std::make_shared<InteractUI>(inter, de);

        auto btn = std::make_shared<Button>(iu);
        btn->setFunc(std::move(onClick));
        return btn;
    };


    sf::Vector2f btnSize(220.f, 56.f);
    sf::Vector2f playPos((float)ws.x * 0.5f - btnSize.x * 0.5f, (float)ws.y * 0.5f - 80.f);
    sf::Vector2f quitPos((float)ws.x * 0.5f - btnSize.x * 0.5f, (float)ws.y * 0.5f + 10.f);


    StateColor mainBtnColor(
        sf::Color(162,208,255,255),sf::Color(122,178,255,  0)   // hover
    );

    auto playBtn = makeButton(
        playPos, btnSize, "Play", mainBtnColor, /*toggle=*/false, 25,
        [this](){
            if (auto playState = this->game->getRegistry().getState("play")) {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(1);
                this->game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(2);
                game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(3);
                game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::X)
        {
            game->pushState("keysettings");
        }
    }
}

void MenuState::update(float dt)
{
    // no-op
}

void MenuState::render(sf::RenderWindow &window)
{
    uiRoot->draw(window);
}