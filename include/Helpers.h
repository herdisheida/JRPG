#ifndef HELPERS_H
#define HELPERS_H

#include <memory>
#include <string>
#include "OverworldMap.h"
#include "EnemyField.h"
#include "creatures/Creature.h"
#include "GameSettings.h"

// overworld map difficulty selection
Difficulty chooseDifficulty();

// player creature selection
std::unique_ptr<Creature> chooseCreature(const std::string& prompt);

// get or create wild enemies (persisteent)
Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos);

// nickname customization
void customizeCreature(Creature& creature);

// print victory/lose messages
void printVictoryMsg();
void printLoseMsg();


#endif
