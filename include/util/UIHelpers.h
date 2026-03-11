#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>

class Creature;

// print ascii with offset to the right
void printAscii(std::vector<std::string> ascii, int offset = 3);

// print health bar with 🟩 and 🟥 colors (name and health beneath)
void printHealthBar(const Creature& creature, int offset);

// print string with offset
void printWithOffset(const std::string& text, int offset);


#endif
