#include <States/LoadState.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>

LoadState::LoadState(std::shared_ptr<Game> game) : GameState(game)
{
    sf::Vector2f firstBoxPos(50.f, 100.f);
    sf::Vector2f boxSize(250.f, 150.f);
    float xSpacing = 50.f;
    float ySpacing = 50.f;

    for (int i = 0; i < 9; ++i)
    {
        int row = i / 3;
        int col = i % 3;
        sf::Vector2f position = sf::Vector2f(firstBoxPos.x + col * (boxSize.x + xSpacing),
                                             firstBoxPos.y + row * (boxSize.y + ySpacing));
        sf::Sprite boxSprite = sf::Sprite(TextureManager::load("assets/Background/MenuBackground1.png"));
        boxSprite.setPosition(position);
        boxSprite.setScale(boxSize.x / boxSprite.getLocalBounds().width,
                           boxSize.y / boxSprite.getLocalBounds().height);
        saveBoxSprites.push_back(boxSprite);

        sf::RectangleShape boxShape(boxSize);
        boxShape.setPosition(position);
        boxShape.setOutlineColor(sf::Color::Black);
        boxShape.setOutlineThickness(3.f);
        boxShape.setFillColor(sf::Color(0, 0, 0, 25));
        saveBoxes.push_back(boxShape);
    }
}

void LoadState::handleEvent(const sf::Event &event)
{
    for (auto &box : saveBoxes)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                box.setFillColor(sf::Color(255, 255, 255, 0));
            }
            else
                box.setFillColor(sf::Color(0, 0, 0, 25));
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                // Do sth
            }
        }
    }
}

void LoadState::update(float dt)
{
    // Update loading progress or animations if necessary
}

void LoadState::render(sf::RenderWindow &window)
{
    // window.clear(sf::Color::Black);
    sf::Sprite backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/MenuBackground.png"));
    window.draw(backgroundSprite);

    for (const auto &boxSprite : saveBoxSprites)
    {
        window.draw(boxSprite);
    }

    for (const auto &box : saveBoxes)
    {
        window.draw(box);
    }
}