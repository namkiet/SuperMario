#include <States/GameState.hpp>
#include <memory>

GameState::GameState(std::shared_ptr<Game> game)
{
    this->game = game;
}