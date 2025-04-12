#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <memory>

#include "validate.h"
#include "calculator.h"

using namespace std;

template <typename Reseiver>
class Command {
public:
    virtual ~Command() = default;
    virtual void execute(shared_ptr<Reseiver>) = 0;
};

#endif // COMMAND_H
