#include <iostream>

#include "../include/game/GameEnd.h"
#include "../include/util/UIHelpers.h"

constexpr int gameEndOffset = 5;


std::vector<std::string> victoryStr() {
    return {
        "                                        ▄▄  ",
        "██     ██ ▄▄ ▄▄  ▄▄ ▄▄  ▄▄ ▄▄▄▄▄ ▄▄▄▄   ██  ",
        "██ ▄█▄ ██ ██ ███▄██ ███▄██ ██▄▄  ██▄█▄  ██  ",
        " ▀██▀██▀  ██ ██ ▀██ ██ ▀██ ██▄▄▄ ██ ██  ▄▄  ",
    };
}                                           

                                           
void printVictoryMsg() {
    std::cout << "\n\n\n\n=========================================\n";
    UIHelper::printAscii(victoryStr(), gameEndOffset);
    UIHelper::printWithOffset("\nYou've defeated all the wild creatures and won the game!\n", gameEndOffset);
}

std::vector<std::string> gameOverStr() {
    return {
        " ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████   ",
        "██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██  ",
        "██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████   ",
        "██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██  ",
        " ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██  ",  
    };
}

void printLoseMsg() {
    std::cout << "\n\n\n\n=========================================\n";
    UIHelper::printAscii(gameOverStr(), gameEndOffset);
    UIHelper::printWithOffset("\nYour creature has fainted and there are no healing items left.", gameEndOffset);
    UIHelper::printWithOffset("Better luck next time!", gameEndOffset);
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