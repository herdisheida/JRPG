#ifndef GAMEEND_H
#define GAMEEND_H

#include "../overworld/OverworldMap.h"
#include "../creatures/Creature.h"


// check if game is lost/won -> print msg
bool handleGameEnd(const OverworldMap& map, const Creature& playerCreature);

// print victory/lose messages
void printVictoryMsg();
void printLoseMsg();

#endif
