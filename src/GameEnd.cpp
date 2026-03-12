#include <iostream>

#include "../include/game/GameEnd.h"
#include "../include/util/UIHelpers.h"




void printVictoryMsg() {
    std::cout << "\n\n\n=========================================\n";
    std::cout << "\nCongratulations!\n";
    std::cout <<" You've defeated all the wild creatures and won the game!\n";
}

std::vector<std::string> gameOver() {
    return {
        " ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████   ",
        "██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██  ",
        "██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████   ",
        "██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██  ",
        " ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██  ",  
    };
}

void printLoseMsg() {
    const int gameOverOffset = 5;
    std::cout << "\n\n\n\n=========================================\n";
    UIHelper::printAscii(gameOver(), gameOverOffset);
    UIHelper::printWithOffset("\nYour creature has fainted and there are no healing items left.", gameOverOffset);
    UIHelper::printWithOffset("Better luck next time!", gameOverOffset);
}

bool handleGameEnd(const OverworldMap& map, const Creature& playerCreature) {

    // win condition
    if (!map.hasWildsLeft()) {
        printVictoryMsg();
        return true;
    }

    // lose condition
    if (playerCreature.isFainted() && !map.hasHeartsLeft()) {
        printLoseMsg();
        return true;
    }

    return false;
}