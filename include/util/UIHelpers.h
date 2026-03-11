#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <iostream>
#include <vector>


class Creature; // forward declare

namespace UIHelpers {
    void printAscii(std::vector<std::string> ascii, int offset = 3);

    // print health bar with 🟩 and 🟥 colors (name and health beneath)
    void printHealthBar(const Creature& creature, int offset);
}


#endif
