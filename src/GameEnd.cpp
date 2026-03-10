#include <iostream>

#include "../include/game/GameEnd.h"



void printVictoryMsg() {
    std::cout << "\n\n\n=========================================\n";
    std::cout << "\nCongratulations!\n";
    std::cout <<" You've defeated all the wild creatures and won the game!\n";
}

void printLoseMsg() {
    std::cout << "\n\n\n=========================================\n";
    std::cout << "\nGame Over!\n";
    std::cout << "Your creature has fainted and there are no healing items left.\n";
    std::cout << "Better luck next time!\n";
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

    // player fainted but hearts still exist
    if (playerCreature.isFainted()) {
        std::cout << "\n" << playerCreature.name()
                  << " has fainted. Find a heart to recover!\n";
    }

    return false;
}