#include <iostream>

#include "../include/game/Encounters.h"
#include "../include/util/Random.h"
#include "../include/util/Helpers.h" // for getOrCreateRandomWildCreatureAt


// main encounter handler
void handleEncounters(
    OverworldMap& map,
    EnemyField& enemyField,
    Creature* playerCreature,
    PlayerController& playerController,
    EnemyController& enemyController,
    char lastMove)
{
    if(!playerCreature) return;

    // heart
    if(map.hasHeart()) {
        std::cout << "\n" << playerCreature->name() << " found a healing heart!\n";
        playerCreature->healToFull();
        std::cout << playerCreature->name() << " was restored to full HP!\n";
        map.clearHeart();
    }

    // mystery
    if(map.hasMystery()) {
        std::cout << "\n" << playerCreature->name() << " found a mystery box!\n";

        int outcome = Random::range(0,3); //

        if(outcome == 0) {
            playerCreature->changeMaxHp(10); std::cout << "+10 max HP!\n";
        }
        else if(outcome == 1) {
            playerCreature->changeMaxHp(-10); std::cout << "-10 max HP...\n";
        }
        else if(outcome == 2) { 
            playerCreature->health().damage(playerCreature->health().current()); std::cout << "Trap! Fainted!\n";
        }
        else if (outcome == 3) {
            playerCreature->stats().attack = std::max(1, playerCreature->stats().attack-5);
            playerCreature->stats().defense = std::max(1, playerCreature->stats().defense-5);
            playerCreature->stats().speed = std::max(1, playerCreature->stats().speed-5);
            std::cout << "Stats reduced!\n"; 
        }
        else {
            std::cout << "hmphh! the box was empty :(\n";
        }
        map.clearMystery();
    }

    // wild
    if(map.hasEncounter()) {
        if(playerCreature->isFainted()) {
            std::cout << "\nYour creature has fainted and cannot battle.\n";
            // move player back to prev pos to prevent repeated encounters
            map.movePlayerBack(lastMove);
            return; // skip battle
        }

        Position pos = map.getPlayerPos();
        Creature* enemyCreature = getOrCreateRandomWildCreatureAt(enemyField, pos);

        Battle battle(*playerCreature, *enemyCreature, playerController, enemyController);
        battle.run();

        if(enemyCreature->isFainted()) {
            // only remove enemy after victory
            enemyField.removeFainted(); // remove enemy from field
            map.clearEncounter();       // remove symbol from map
        } else {
            map.movePlayerBack(lastMove); // player is set right wher he was before encounter
        }
    }
}