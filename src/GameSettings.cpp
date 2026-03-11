#include <iostream>
#include <limits>

#include "../include/util/GameSettings.h"



Difficulty chooseDifficulty() {
    while (true) {
        std::cout << "Choose difficulty:\n";
        std::cout << "1. Easy\n";
        std::cout << "2. Medium\n";
        std::cout << "3. Hard\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

        switch (choice) {
            case 1: return Difficulty::Easy;
            case 2: return Difficulty::Medium;
            case 3: return Difficulty::Hard;
            
            default:
                std::cout << "Invalid choice.\n\n";
        }
    }
}