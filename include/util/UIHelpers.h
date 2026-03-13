#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <iostream>
#include <vector>
#include "Colors.h"

class Creature;
enum class DamageType;

namespace UIHelper {

// wait for enter to continue
void waitForEnter(const std::string& prompt = "");

// print ascii with offset to the right
void printAscii(std::vector<std::string> ascii, int offset = 3);

// print health bar with 🟩 and 🟥 colors (name and health beneath)
void printHealthBar(const Creature& creature, int offset);

// print string with offset
void printWithOffset(const std::string& text, int offset);

// center text in a field of given width
std::string center(const std::string& s, size_t width);

// get string input (max 15 chars, only letters and underscores)
std::string getStringInput(const std::string& prompt, std::string nameOfInput);

// New colored versions
std::string getColored(const std::string& text, Color::Code color, int offset = 0);
std::string getSuccessStr(const std::string& text, int offset = 0);
std::string getErrorStr(const std::string& text, int offset = 0);
}



#endif
