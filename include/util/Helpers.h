#ifndef HELPERS_H
#define HELPERS_H

#include "../overworld/OverworldMap.h"
#include "../overworld/EnemyField.h"
#include "../creatures/Creature.h"
#include "GameSettings.h"

// overworld map difficulty selection
Difficulty chooseDifficulty();

// get or create wild enemies (persisteent)
Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos);

#endif
