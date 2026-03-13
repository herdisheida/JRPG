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
#include "include/game/GameStore.h"

#include "include/util/GameSettings.h"
#include "include/util/UIHelpers.h"



void quitGame(Creature* playerCreature, const OverworldMap& map, EnemyField& enemyField) {
    std::cout << "\n\nSave before quitting? (Y/N): ";
    
    char saveChoice;
    std::cin >> saveChoice;
    saveChoice = std::toupper(saveChoice);

    if (saveChoice == 'Y') {
        std::string filename = playerCreature->name() + "_save";

        if (GameStore::saveGame(filename, *playerCreature, map, enemyField)) {
            std::cout << UIHelper::getSuccessStr("Game saved successfully as <" + filename + "> !") << "\n";
        } else {
            std::cout << UIHelper::getErrorStr("Failed to save game.") << "\n";
        }
    }
    std::cout << "Quitting game...\n";
}



int main() {
    startGameIntro(); // prints intro and waits for Enter

    // initialize map and player for a new session
    GameSettings defaultSettings;
    OverworldMap map(defaultSettings.rows, defaultSettings.cols);
    EnemyField enemyField;
    std::unique_ptr<Creature> playerCreature;

    // try to load old game, if user wants to
    bool loaded = loadOldGames(playerCreature, map, enemyField);

    // if not loaded, then initialize normally
    if (!loaded) {
        // difficulty
        Difficulty difficulty = chooseDifficulty();
        GameSettings settings = settingsForDifficulty(difficulty);
        std::cout << "\nDifficulty: " << difficultyToString(difficulty) << "\n\n";

        // player creature
        playerCreature = chooseCreature("Choose your creature:");
        customizeCreature(*playerCreature);

        // initialize map properly
        map = OverworldMap(settings.rows, settings.cols);
        map.initialize(settings.wildCount, settings.heartCount, settings.mysteryCount);
    }

    // display user's creature
    if (!playerCreature) { std::cerr << UIHelper::getErrorStr("Failed to initialize player creature.") << "\n"; return 1; }
    printCreatureSummary(*playerCreature);

    // init controllers
    PlayerController playerController;
    EnemyController enemyController;

    // main game loop - player moves around map and encounters wild creatures
    while (true) {
        map.print();
        
        char input = getPlayerMove();
        if (input == '\0') continue;
    
        if (input == 'q' || input == 'Q') { quitGame(playerCreature.get(), map, enemyField); break; }
        if (input == 'i' || input == 'I') { map.printInstructions(); continue; }

        if (!map.movePlayer(input)) { continue; } // if player can move he moves
        
        handleEncounters(map, enemyField, playerCreature.get(), playerController, enemyController, input);
        if (handleBattleEnd(map, *playerCreature)) { break; }

    }
}
