#pragma once
#include <iostream>

namespace sf
{
    class RenderWindow;
}

class Controller;

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
    virtual void undo() { std::cout << "No Undo implemented\n"; }
    virtual void redo() { std::cout << "No Redo implemented\n"; }
};
