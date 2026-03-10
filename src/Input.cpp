
#include <iostream>
#include "../include/game/Input.h"


char getPlayerMove() {
    std::cout << "\nEnter move: (I for instructions)\n";
    std::cout << "> ";

    std::string line;
    getline(std::cin, line);
    std::cout << "\n\n\n\n\n\n\n\n"; // spacing after input

    if (line.length() > 1) {
        std::cout << "\nInvalid input. Please enter a single character.\n";
        return '\0'; // error value
    }
    return line[0];
}

void startGameIntro() {
    std::cout << "========================================\n";
    std::cout << "          Welcome to Miniiees!          \n";
    std::cout << "========================================\n\n";

    std::cout << "Your goal is to explore the overworld and defeat all wild creatures. \n\n";

    std::cout << "Be careful! If your creature faints and you run out of healing items, you lose!\n";
    std::cout << "Try not to die!\n\n";

    std::cout << "Press Enter to start your adventure...";
    std::string dummy;
    std::getline(std::cin, dummy);  // waits for user to press Enter
    std::cout << "\nGood luck, adventurer!\n\n";
}
    