#include <iostream>
#include <algorithm>
#include <cctype>

#include "../include/Helpers.h"
#include "../include/Random.h"
#include "../include/creatures/CreatureType.h"




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

        switch (choice) {
            case 1: return Difficulty::Easy;
            case 2: return Difficulty::Medium;
            case 3: return Difficulty::Hard;
            default:
                std::cout << "Invalid choice.\n\n";
        }
    }
}

std::unique_ptr<Creature> chooseCreature(const std::string& prompt) {
    while (true) {
        std::cout << prompt << "\n";
        std::cout << "1. Pikachu\n";
        std::cout << "2. Piplup\n";
        std::cout << "3. Charizard\n";
        std::cout << "4. Lucario\n";
        std::cout << "5. Gengar\n";

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

Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos) {
    Creature* enemy = field.getEnemyAt(pos);
    if (enemy) return enemy; // enemy already exists here

    // create new random enemy
    int roll = Random::range(0, 4); // 5 possible creatures
    std::unique_ptr<Creature> newEnemy;

    switch (roll) {
        case 0: newEnemy  = std::make_unique<Pikachu>(); break;
        case 1: newEnemy  = std::make_unique<Piplup>(); break;
        case 2: newEnemy  = std::make_unique<Charizard>(); break;
        case 3: newEnemy  = std::make_unique<Lucario>(); break;
        default: newEnemy = std::make_unique<Gengar>(); break;
    }

    enemy = newEnemy.get();
    field.addEnemyAt(pos, std::move(newEnemy));
    return enemy;
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

char getPlayerMove() {
    char input;
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