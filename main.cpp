#include <iostream>
#include <memory>
#include <cctype>    // for ::toupper


#include "include/controllers/EnemyController.h"
#include "include/controllers/PlayerController.h"


#include "include/overworld/EnemyField.h"
#include "include/overworld/OverworldMap.h"

#include "include/game/CreatureSelection.h"
#include "include/game/GameEnd.h"
#include "include/game/Encounters.h"
#include "include/game/Input.h"

#include "include/util/GameSettings.h"
#include "include/game/GameStore.h"



void quitGame(Creature* playerCreature, const OverworldMap& map) {
    std::cout << "\n\nDo you want to save your game before quitting? (Y/N): ";
    
    char saveChoice;
    std::cin >> saveChoice;
    saveChoice = std::toupper(saveChoice);

    if (saveChoice == 'Y') {
        std::string filename;    
        UIHelper::getStringInput("Enter filename: ", filename);

        if (GameStore::saveGame(filename, *playerCreature, map)) {
            std::cout << "\nGame saved successfully as \"" << filename << "\"!\n";
        } else {
            std::cout << "\nFailed to save game.\n";
        }
    }

    std::cout << "Quitting game...\n";
}


int main() {
    startGameIntro(); // prints intro and waits for Enter

    // game setup
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
        
        char input = getPlayerMove();
        if (input == '\0') continue;
    
        if (input == 'q' || input == 'Q') { quitGame(playerCreature.get(), map); break; }
        if (input == 'i' || input == 'I') { map.printInstructions(); continue; }

        if (!map.movePlayer(input)) { continue; } // if player can move he moves
        
        handleEncounters(map, enemyField, playerCreature.get(), playerController, enemyController, input);
        if (handleGameEnd(map, *playerCreature)) { break; }

    }
}
