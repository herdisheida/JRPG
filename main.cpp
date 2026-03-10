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
        
        if (handleGameEnd(map, *playerCreature)) { break; }

        char input = getPlayerMove();
        if (input == '\0') continue;
    
        if (input == 'q' || input == 'Q') { break; }
        if (input == 'i' || input == 'I') { map.printInstructions(); continue; }

        if (!map.movePlayer(input)) { continue; } // if player can move he moves
        handleEncounters(map, enemyField, playerCreature.get(), playerController, enemyController, input);

    }
}
