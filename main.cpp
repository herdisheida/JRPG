#include <iostream>
#include <memory>
#include <cctype>    // for ::toupper


#include "include/controllers/EnemyController.h"
#include "include/controllers/PlayerController.h"

#include "include/creatures/Creature.h"

#include "include/EnemyField.h"
#include "include/OverworldMap.h"
#include "include/GameSettings.h"

#include "include/Helpers.h"
#include "include/Encounters.h"




int main() {
    std::cout << "=== Welcome to Miniiees by Herdis ===\n\n";

    Difficulty difficulty = chooseDifficulty();
    GameSettings settings = settingsForDifficulty(difficulty);
    std::cout << "\nDifficulty: " << difficultyToString(difficulty) << "\n\n";

    auto playerCreature = chooseCreature("Choose your creature:");
    customizeCreature(*playerCreature);

    // initalize game
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

        // get player input (move on map)
        char input;
        std::cout << "\nEnter move: (I for instructions)\n";
        std::cout << "> ";

        std::string line;
        getline(std::cin, line);
        std::cout << "\n\n\n\n\n\n\n\n"; // add spacing after input
        if (line.length() > 1) {
            std::cout << "\nInvalid input. Please enter a single character.\n";
            continue;
        }
        input = line[0];
        
        if (input == 'q' || input == 'Q') { break; }
        if (input == 'i' || input == 'I') {
            map.printInstructions();
            continue;
        }
        if (!map.movePlayer(input)) { continue; } // ask for input again if move == invalid
        handleEncounters(map, enemyField, playerCreature.get(), playerController, enemyController, input);

    }
}
