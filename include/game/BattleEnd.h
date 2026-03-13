#ifndef BATTLEEND_H
#define BATTLEEND_H

#include "../overworld/OverworldMap.h"
#include "../creatures/Creature.h"


// check if battle is lost/won -> print msg
bool handleBattleEnd(const OverworldMap& map, const Creature& playerCreature);

// print victory/lose messages
void printVictoryMsg();
void printLoseMsg();

#endif
