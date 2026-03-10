#ifndef ENCOUNTERS_H
#define ENCOUNTERS_H

#include "../overworld/OverworldMap.h"
#include "../overworld/EnemyField.h"
#include "../creatures/Creature.h"
#include "../controllers/PlayerController.h"
#include "../controllers/EnemyController.h"
#include "../battle/Battle.h"

// wild enemies, hearts, and mystery encounters
void handleEncounters(
    OverworldMap& map,
    EnemyField& enemyField,
    Creature* playerCreature,
    PlayerController& playerController,
    EnemyController& enemyController,
    char lastMove
);

#endif
