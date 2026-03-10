#include <iostream>

#include "../include/game/CreatureSelection.h"
#include "../include/creatures/CreatureType.h"


std::unique_ptr<Creature> chooseCreature(const std::string& prompt) {
    while (true) {
        std::cout << prompt << "\n";
        std::cout << "1. Pikachu"   << " - " << Pikachu().Roles()   << "\n";
        std::cout << "2. Piplup"    << " - " << Piplup().Roles()    << "\n";
        std::cout << "3. Charizard" << " - " << Charizard().Roles() << "\n";
        std::cout << "4. Lucario"   << " - " << Lucario().Roles()   << "\n";
        std::cout << "5. Gengar"    << " - " << Gengar().Roles()    << "\n";

        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n\n";
            continue;
        }

        switch (choice) {
            case 1: return std::make_unique<Pikachu>();
            case 2: return std::make_unique<Piplup>();
            case 3: return std::make_unique<Charizard>();
            case 4: return std::make_unique<Lucario>();
            case 5: return std::make_unique<Gengar>();
            default:
                std::cout << "Invalid choice.\n\n";
        }
    }
}


// choose and set nickname for player creature
void customizeCreature(Creature& creature) {
    std::cout << "\nGive " << creature.species() << " a nickname: ";
    std::string nickname;
    std::getline(std::cin, nickname);
    
    while (std::getline(std::cin, nickname)) {
        if (nickname.empty()) {
            std::cout << "Nickname cannot be empty. Please enter a valid nickname: ";
            continue;
        }
        if (nickname.length() > 15) {
            std::cout << "Nickname too long. Please enter a nickname with 15 characters or fewer: ";
            continue;
        }
        if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0_") != std::string::npos) {
            std::cout << "Nickname contains invalid characters. Please use only letters or underscores: ";
            continue;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n\n";
            continue;
        }
        break;
    }

    // convert nickname to uppercase
    std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::toupper);
    creature.setName(nickname);

    // display customized creature
    std::cout << creature.name() << " is ready for battle!\n\n";
    creature.printAscii();
}