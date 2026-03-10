#include <iostream>
#include <memory>
#include <random>
#include <algorithm> // for std::transform
#include <cctype>    // for ::toupper

#include "include/Battle.h"

#include "include/controllers/EnemyController.h"
#include "include/controllers/PlayerController.h"

#include "include/creatures/Creature.h"

#include "include/EnemyField.h"
#include "include/OverworldMap.h"
#include "include/GameSettings.h"

#include "include/Random.h"
#include "include/Helpers.h"



using std::cout;
using std::cin;


int main() {
    cout << "=== Welcome to Miniiees by Herdis ===\n\n";

    Difficulty difficulty = chooseDifficulty();
    GameSettings settings = settingsForDifficulty(difficulty);
    cout << "\nDifficulty: " << difficultyToString(difficulty) << "\n\n";

    auto playerCreature = chooseCreature("Choose your creature:");
    customizeCreature(*playerCreature);


    PlayerController playerController;
    EnemyController enemyController;

    // initalize overworld
    OverworldMap map(settings.rows, settings.cols);
    EnemyField enemyField;
    map.initialize(settings.wildCount, settings.heartCount, settings.mysteryCount);


    // main game loop - player moves around map and encounters wild creatures
    while (true) {
        map.print();

        // win or lose conditions
        if (!map.hasWildsLeft()) {
            printVictoryMsg();
            break;
        }
        if (playerCreature->isFainted()) {
            if (!map.hasHeartsLeft()) {
                printLoseMsg();
                break;
            } else {
                std::cout << "\n" << playerCreature->name() << " has fainted. Find a heart to recover!\n";
            }
        }

        // move player
        char input;
        std::cout << "\nEnter move: (I for instructions)\n";
        std::cout << "> ";

        std::string line;
        getline(cin, line);
        std::cout << "\n\n\n\n\n\n\n\n"; // add spacing after input
        if (line.length() > 1) {
            cout << "\nInvalid input. Please enter a single character.\n";
            continue;
        }
        input = line[0];
        
        if (input == 'q' || input == 'Q') { break; }
        if (input == 'i' || input == 'I') {
            map.printInstructions();
            continue;
        }
        if (!map.movePlayer(input)) { continue; }

        // heart encounter
        if (map.hasHeart()) {
            std::cout << "\n" << playerCreature->name() << " found a healing heart!\n";
            playerCreature->healToFull();
            map.clearHeart();
            std::cout << playerCreature->name() << " was restored to full HP!\n";
        }

        // mystery encounter
        if (map.hasMystery()) {
            std::cout << "\n" << playerCreature->name() << " found a mystery box!\n";

            std::uniform_int_distribution<int> dist(0, 3); // 4 possible outcomes
            int outcome = dist(Random::rng());

            if (outcome == 0) {
                // positive effect: increase max HP
                playerCreature->changeMaxHp(10);
                std::cout << playerCreature->name() << " gained +10 max HP!\n";
            } else if (outcome == 1) {
                // negative effect: decrease max HP
                playerCreature->changeMaxHp(-10);
                std::cout << playerCreature->name() << " lost 10 max HP...\n";
            } else if (outcome == 2) {
                // DEATH EFFECT: faint immediately
                playerCreature->health().damage(playerCreature->health().current());
                std::cout << "Oh no! It was a trap! " << playerCreature->name() << " took massive damage and fainted!\n";
            } else if (outcome == 3) {
                // negative effect: decrease stats (attack, defense, speed)
                playerCreature->stats().attack = std::max(1, playerCreature->stats().attack - 5);
                playerCreature->stats().defense = std::max(1, playerCreature->stats().defense - 5);
                playerCreature->stats().speed = std::max(1, playerCreature->stats().speed - 5);
                std::cout << playerCreature->name() << "'s stats were reduced!\n";
            } else {
                // no effect
                std::cout << playerCreature->name() << " found nothing special.\n";
            }

            std::cout << "New HP: "
                    << playerCreature->health().current()
                    << "/" << playerCreature->health().max() << "\n";

            map.clearMystery();
        }

        // wild battle encounter
        if (map.hasEncounter()) {
            if (playerCreature->isFainted()) {
                cout << "\nYour creature has fainted and cannot battle.\n";
                // move player back to previous position to avoid repeated encounters
                map.movePlayerBack(input);
                continue; // skip battle
            }

            Position playerPos = map.getPlayerPos();
            Creature* enemyCreature = getOrCreateRandomWildCreatureAt(enemyField, playerPos);

            Battle battle(*playerCreature, *enemyCreature, playerController, enemyController);
            battle.run();

            if (enemyCreature->isFainted()) {
                // only remove enemy after victory
                enemyField.removeFainted(); // remove from field
                map.clearEncounter(); // remove from map
            } else {
                map.movePlayerBack(input); // player is right wher he was before encounter
            }
        }
    }
}
