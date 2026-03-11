
#include <iostream>
#include "../include/game/Input.h"
#include "../include/util/Helpers.h"


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
    printAscii(introString(), 5);

    std::cout << "Your goal is to explore the overworld and defeat all wild creatures.\n";
    std::cout << "Be careful! If your creature faints and you run out of healing items, you lose!\n";
    std::cout << "Try not to die!\n\n";

    std::cout << "Press Enter to start your adventure...";
    waitForEnter();
    std::cout << "\n\n\n\n\n\n\n"; // spacing after intro
}

void waitForEnter(const std::string& prompt) {
    std::cout << prompt;
    std::cin.get(); // waits for user to press Enter
}

    