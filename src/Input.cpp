
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
