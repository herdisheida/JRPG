#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>

#include "../overworld/OverworldMap.h"
#include "../creatures/Creature.h"


// get user input for move (has to be a single char in a line)
char getPlayerMove();

// short intro at start of game
std::vector<std::string> introString();
void startGameIntro();

// try loading old games
bool loadOldGames(std::unique_ptr<Creature>& playerCreature, OverworldMap& map);

#endif