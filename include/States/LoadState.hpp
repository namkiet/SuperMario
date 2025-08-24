#pragma once
#include <States/GameState.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class LoadState : public GameState
{
private:
    std::vector<sf::RectangleShape> saveBoxes;
    std::vector<sf::Sprite> saveBoxSprites;
    std::vector<sf::Text> saveTexts;
    sf::Font font;
    int saveCount;
    json saves;

public:
    LoadState(std::shared_ptr<Game> game);
    void init();
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
};