#ifndef HELPERS_H
#define HELPERS_H

#include <memory>
#include <string>
#include "../overworld/OverworldMap.h"
#include "../overworld/EnemyField.h"
#include "../creatures/Creature.h"
#include "GameSettings.h"

// overworld map difficulty selection
Difficulty chooseDifficulty();

// player creature selection
std::unique_ptr<Creature> chooseCreature(const std::string& prompt);

// nickname customization
void customizeCreature(Creature& creature);


// get or create wild enemies (persisteent)
Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos);

// print victory/lose messages
void printVictoryMsg();
void printLoseMsg();


// check if game is lost/won -> print msg
bool handleGameEnd(const OverworldMap& map, const Creature& playerCreature);


#endif
