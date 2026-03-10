#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <random>

#include "../creatures/Creature.h"


class Controller {
    public:
        virtual ~Controller() = default;
        virtual int chooseAction(const Creature& self, const Creature& opponent) = 0;
};


#endif
