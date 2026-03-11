#ifndef HELPERS_H
#define HELPERS_H

#include "../overworld/EnemyField.h"
#include "../creatures/Creature.h"


// get or create wild enemies (persisteent)
Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos);


#endif
