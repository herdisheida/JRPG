#ifndef CREATURESELECTION_H
#define CREATURESELECTION_H

#include <memory>
#include <string>
#include "../creatures/Creature.h"


// player creature selection
std::unique_ptr<Creature> chooseCreature(const std::string& prompt);

// nickname customization
void customizeCreature(Creature& creature);

// display creature summary after selection and customization
void printCreatureSummary(const Creature& creature);

#endif
