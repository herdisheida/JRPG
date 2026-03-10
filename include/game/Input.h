#ifndef INPUT_H
#define INPUT_H

#include <string>

// get user input for move (has to be a single char in a line)
char getPlayerMove();

// short intro at start of game
void startGameIntro();

// user press enter to continue
void waitForEnter(const std::string& prompt = "");

#endif