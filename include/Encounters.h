#ifndef ENCOUNTERS_H
#define ENCOUNTERS_H

#include "OverworldMap.h"
#include "EnemyField.h"
#include "creatures/Creature.h"
#include "controllers/PlayerController.h"
#include "controllers/EnemyController.h"
#include "Battle.h"

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
