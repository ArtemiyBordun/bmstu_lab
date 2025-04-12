#ifndef CALCULATORCOMMAND_H
#define CALCULATORCOMMAND_H

#include "command.h"
#include "calculator.h"

template <typename Reseiver>
class CalculatorCommand : public Command<Reseiver> {
    using Action = void(Reseiver::*)();
private:
    Action act;
public:
    CalculatorCommand(Action a) : act(a) {}
    virtual void execute(shared_ptr<Reseiver> r) override { ((*r).*act)(); }
};

#endif // CALCULATORCOMMAND_H
