
#include <iostream>
#include "../include/game/Input.h"
#include "../include/util/UIHelpers.h"
#include "../include/game/GameStore.h"


char getPlayerMove() {

    std::cout << "\nEnter move: (I for instructions)\n";
    std::cout << "> ";

    std::string line;
    getline(std::cin, line);
    std::cout << "\n\n\n\n\n\n\n\n"; // spacing after input

    if (line.length() > 1) {
        std::cout << UIHelper::getErrorStr("\nInvalid input.") << " Please enter a single character.\n";
        return '\0'; // error value
    }
    if (line.empty()) return '\0';

    return line[0];
}


std::vector<std::string> introString() {
    return {
        "▗▖  ▗▖▄ ▄▄▄▄  ▗▞▀▜▌ ▄▄▄      ▗▄▖    ▐▌▄   ▄ ▗▞▀▚▖▄▄▄▄     ■  █  ▐▌ ▄▄▄ ▗▞▀▚▖",
        "▐▛▚▞▜▌▄ █ █ █ ▝▚▄▟▌▀▄▄      ▐▌ ▐▌   ▐▌█   █ ▐▛▀▀▘█   █ ▗▄▟▙▄▖▀▄▄▞▘█    ▐▛▀▀▘",
        "▐▌  ▐▌█ █   █      ▄▄▄▀     ▐▛▀▜▌▗▞▀▜▌ ▀▄▀  ▝▚▄▄▖█   █   ▐▌       █    ▝▚▄▄▖",
        "▐▌  ▐▌█                     ▐▌ ▐▌▝▚▄▟▌                   ▐▌                 ",
        "                                                         ▐▌                 "
    };
}

void startGameIntro() {
    std::cout << "\n";
    const int startGameOffset = 5;
    UIHelper::printAscii(introString(), startGameOffset);

    UIHelper::printWithOffset("\nYour goal is to explore the overworld and defeat all wild creatures.\n", startGameOffset);
    UIHelper::printWithOffset("Be careful! If your creature faints and you run out of healing items, you lose!\n", startGameOffset);
    UIHelper::printWithOffset("Try not to die!\n\n", startGameOffset);
    UIHelper::printWithOffset("enter to continue...", startGameOffset);

    UIHelper::waitForEnter();
    std::cout << "\n\n\n\n\n\n\n"; // spacing after intro
}

// asking user if they want to play old games
bool loadOldGames(std::unique_ptr<Creature>& playerCreature, OverworldMap& map, EnemyField& enemyField) {
    std::vector<std::string> saves = GameStore::listSaves();
    if (saves.empty()) return false;

    std::cout << "Saved games found:\n";
    for (size_t i = 0; i < saves.size(); ++i) {
        std::cout << "  " << (i+1) << ". " << saves[i] << "\n";
    }
    std::cout << "\nSelect a save to load or 0 to start new: ";
    
    int choice;
    std::cin >> choice;

    // invalid input - not a num
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cout << UIHelper::getErrorStr("\nInvalid input - not a number. ") << "Loading new game..." << "\n\n";
        return false;
    }
    // invalid range
    if (choice > (int)saves.size() || choice < 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cout << UIHelper::getErrorStr("\nInvalid input. ") << "Loading new game..." << "\n\n";
        return false;
    }

    // valid choice
    if (choice > 0 && choice <= (int)saves.size()) {
        bool loaded = GameStore::loadGame(saves[choice-1], playerCreature, map, enemyField);
        
        if (loaded) {
            std::cout << UIHelper::getSuccessStr("\nGame loaded successfully!");
            return true;
        } else {
            std::cout << UIHelper::getErrorStr("\nFailed to load save.");
        }
    }
    std::cout << "\n\n";
    return false;
}