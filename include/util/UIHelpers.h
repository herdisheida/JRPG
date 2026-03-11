#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <iostream>
#include <vector>
#include "Colors.h"

class Creature;
enum class DamageType;

namespace UIHelper {


// print ascii with offset to the right
void printAscii(std::vector<std::string> ascii, int offset = 3);

// print health bar with 🟩 and 🟥 colors (name and health beneath)
void printHealthBar(const Creature& creature, int offset);

// print string with offset
void printWithOffset(const std::string& text, int offset);

// void print spacer '=' for prettyfactor
std::string getSpacer(int length);


// New colored versions
std::string getColored(const std::string& text, Color::Code color, int offset = 0);
std::string getSuccessStr(const std::string& text, int offset = 0);
std::string getErrorStr(const std::string& text, int offset = 0);
}

#endif
