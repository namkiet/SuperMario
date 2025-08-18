#pragma once
#include <Editor/Command/ICommand.hpp>
#include <Editor/Model.hpp>

class DeleteCommand : public ICommand
{
public:
    DeleteCommand(Model& model, sf::Vector2f mousePos) : model(model), mousePos(mousePos) {}

    bool execute() override 
    {
        model.removeEntity(mousePos.x, mousePos.y);
        return true;
    }

private:
    Model& model;
    sf::Vector2f mousePos;
};
