#include <Game.hpp>
#include <States/CustomState.hpp>
#include <States/PlayingState.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CustomState::CustomState(std::shared_ptr<Game> game) : GameState(game)
{
    init();
}

void CustomState::init()
{
    saveBoxes.clear();
    saveBoxSprites.clear();
    saveTexts.clear();

    sf::Vector2f firstBoxPos(50.f, 100.f);
    sf::Vector2f boxSize(250.f, 150.f);
    float xSpacing = 50.f;
    float ySpacing = 50.f;

    font.loadFromFile("BalooBhai2-ExtraBold.ttf");

    json index;
    std::ifstream fin("customs/index.json");
    if (!fin.is_open()) return;
    fin >> index;
    saveCount = index.value("count", 0);
    saves = index.value("saves", json::array());

    for (int i = 0; i < 9; ++i)
    {
        int row = i / 3;
        int col = i % 3;
        sf::Vector2f position(firstBoxPos.x + col * (boxSize.x + xSpacing),
                              firstBoxPos.y + row * (boxSize.y + ySpacing));

        sf::Sprite boxSprite;
        if (i < saveCount)
        {
            std::string timestamp = saves[i]["timestamp"].get<std::string>();
            // std::replace_if(timestamp.begin(), timestamp.end(), ::isspace, '_');
            boxSprite.setTexture(TextureManager::load("customs/screenshots/" + timestamp + ".png"));
        }
        else
        {
            // boxSprite.setTexture(TextureManager::load("assets/Background/MenuBackground1.png"));
        }

        boxSprite.setColor(sf::Color(180, 180, 180));
        boxSprite.setPosition(position);
        boxSprite.setScale(boxSize.x / boxSprite.getLocalBounds().width,
                           boxSize.y / boxSprite.getLocalBounds().height);
        saveBoxSprites.push_back(boxSprite);

        sf::RectangleShape boxShape(boxSize);
        boxShape.setPosition(position);
        boxShape.setOutlineColor(sf::Color::Black);
        boxShape.setOutlineThickness(3.f);
        boxShape.setFillColor(sf::Color(0, 0, 0, 100)); // tối hơn
        saveBoxes.push_back(boxShape);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24); // chữ to hơn
        text.setFillColor(sf::Color::White);

        if (i < saveCount) {
            const auto& meta = saves[i];
            text.setString("Custom Map " + std::to_string(i + 1));
            // text.setString(meta.value("timestamp", "Unknown"));
        } else {
            text.setString("Empty");
        }

        // căn giữa text trong box
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.f,
                       textBounds.top + textBounds.height / 2.f);
        text.setPosition(position.x + boxSize.x / 2.f,
                         position.y + boxSize.y / 2.f);

        saveTexts.push_back(text);
    }

    // === Nút New Map ===
    sf::Vector2f buttonSize(220.f, 70.f);

    newMapButton.setSize(buttonSize);
    newMapButton.setFillColor(sf::Color(30, 144, 255)); // xanh dương đậm (DodgerBlue)
    newMapButton.setOutlineColor(sf::Color(255, 255, 255, 180)); // viền trắng mờ
    newMapButton.setOutlineThickness(2.f);
    newMapButton.setPosition(SIZE::SCREEN.x - buttonSize.x - 15, 15);

    // Text
    newMapText.setFont(font);
    newMapText.setString("New Map");
    newMapText.setCharacterSize(28);
    newMapText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = newMapText.getLocalBounds();
    newMapText.setOrigin(textBounds.left + textBounds.width / 2.f,
                         textBounds.top + textBounds.height / 2.f);
    newMapText.setPosition(
        newMapButton.getPosition().x + buttonSize.x / 2.f,
        newMapButton.getPosition().y + buttonSize.y / 2.f
    );

}

void CustomState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            game->popState();
            game->pushState("menu");
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        if (newMapButton.getGlobalBounds().contains(mousePos)) {
            newMapButton.setFillColor(sf::Color(65, 175, 255)); // xanh sáng hơn khi hover
        } else {
            newMapButton.setFillColor(sf::Color(30, 144, 255)); // xanh bình thường
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (newMapButton.getGlobalBounds().contains(mousePos)) {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::ifstream fin("sample.json");
                json j; fin >> j;
                if (!j.empty())
                {
                    std::static_pointer_cast<PlayingState>(playState)->setLevel(j["level"], false, GameManager::Mode::Editor, j);
                    game->pushState("play");
                }
            }
        }
    }

    for (int i = 0; i < saveBoxes.size(); i++)
    {
        auto& box = saveBoxes[i];
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                box.setFillColor(sf::Color(255, 255, 255, 0));
                box.setOutlineThickness(4);
            }
            else
            {
                box.setFillColor(sf::Color(0, 0, 0, 25));
                box.setOutlineThickness(3);
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (i >= saveCount) break;
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                auto path = "customs/" + saves[i]["filename"].get<std::string>();

                auto playState = game->getRegistry().getState("play");
                if (playState)
                {
                    std::ifstream fin(path);
                    json j; fin >> j;
                    if (!j.empty())
                    {
                        std::static_pointer_cast<PlayingState>(playState)->setLevel(j["level"], false, GameManager::Mode::LoadGame, j);
                        game->pushState("play");
                    }
                }
            }
        }
    }
}

void CustomState::update(float dt)
{
    // Update loading progress or animations if necessary
}

void CustomState::render(sf::RenderWindow &window)
{
    // window.clear(sf::Color::Black);
    sf::Sprite backgroundSprite(TextureManager::load("assets/Background/MenuBackground.png"));
    
    window.draw(backgroundSprite);

    for (const auto &boxSprite : saveBoxSprites)
    {
        window.draw(boxSprite);
    }

    for (const auto &box : saveBoxes)
    {
        window.draw(box);
    }

    for (const auto &txt : saveTexts)
        window.draw(txt);

    window.draw(newMapButton);
    window.draw(newMapText);
}