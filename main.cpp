#include <iostream>
#include <memory>
#include <random>
#include <algorithm> // for std::transform
#include <cctype>    // for ::toupper

#include "include/Battle.h"

#include "include/controllers/EnemyController.h"
#include "include/controllers/PlayerController.h"

#include "include/creatures/Creature.h"
#include "include/creatures/CreatureType.h"

#include "include/OverworldMap.h"
#include "include/GameSettings.h"
#include "include/Random.h"


using std::cout;
using std::cin;


Difficulty chooseDifficulty() {
    while (true) {
        cout << "Choose difficulty:\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "> ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n\n";
            continue;
        }

        switch (choice) {
            case 1: return Difficulty::Easy;
            case 2: return Difficulty::Medium;
            case 3: return Difficulty::Hard;
            default:
                cout << "Invalid choice.\n\n";
        }
    }
}



std::unique_ptr<Creature> chooseCreature(const std::string& prompt) {
    while (true) {
        cout << prompt << "\n";
        cout << "1. Pikachu\n";
        cout << "2. Piplup\n";
        cout << "3. Charizard\n";
        cout << "4. Lucario\n";
        cout << "5. Gengar\n";

        cout << "> ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n\n";
            continue;
        }

        switch (choice) {
            case 1: return std::make_unique<Pikachu>();
            case 2: return std::make_unique<Piplup>();
            case 3: return std::make_unique<Charizard>();
            case 4: return std::make_unique<Lucario>();
            case 5: return std::make_unique<Gengar>();
            default:
                cout << "Invalid choice.\n\n";
        }
    }
}

std::unique_ptr<Creature> createRandomWildCreature() {
    int roll = std::rand() % 5;

    switch (roll) {
        case 0: return std::make_unique<Pikachu>();
        case 1: return std::make_unique<Piplup>();
        case 2: return std::make_unique<Charizard>();
        case 3: return std::make_unique<Lucario>();
        default: return std::make_unique<Gengar>();
    }
}

// choose and set nickname for player creature
void customizeCreature(Creature& creature) {
    cout << "\nGive " << creature.species() << " a nickname: ";
    std::string nickname;
    std::getline(cin, nickname);
    
    while (std::getline(cin, nickname)) {
        if (nickname.empty()) {
            cout << "Nickname cannot be empty. Please enter a valid nickname: ";
            continue;
        }
        if (nickname.length() > 15) {
            cout << "Nickname too long. Please enter a nickname with 15 characters or fewer: ";
            continue;
        }
        if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0_") != std::string::npos) {
            cout << "Nickname contains invalid characters. Please use only letters or underscores: ";
            continue;
        }

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n\n";
            continue;
        }
        break;
    }

    // convert nickname to uppercase
    std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::toupper);
    creature.setName(nickname);

    // display customized creature
    cout << creature.name() << " is ready for battle!\n\n";
    creature.printAscii();
}

void printVictoryMsg() {
    cout << "\n\n\n=========================================\n";
    cout << "\nCongratulations!\n";
    cout <<" You've defeated all the wild creatures and won the game!\n";
}

void printLoseMsg() {
    cout << "\n\n\n=========================================\n";
    cout << "\nGame Over!\n";
    cout << "Your creature has fainted and there are no healing items left.\n";
    cout << "Better luck next time!\n";
}

void moveToPreviousPosition(OverworldMap& map, char input) {
    switch (input) {
        case 'w': case 'W': map.movePlayer('s'); break;
        case 's': case 'S': map.movePlayer('w'); break;
        case 'a': case 'A': map.movePlayer('d'); break;
        case 'd': case 'D': map.movePlayer('a'); break;
    }
}

int main() {
    cout << "=== Mini JRPG Battle ===\n\n";

    Difficulty difficulty = chooseDifficulty();
    GameSettings settings = settingsForDifficulty(difficulty);
    cout << "\nDifficulty: " << difficultyToString(difficulty) << "\n\n";

    auto playerCreature = chooseCreature("Choose your creature:");
    customizeCreature(*playerCreature);


    PlayerController playerController;
    EnemyController enemyController;

    // initalize overworld
    OverworldMap map(settings.rows, settings.cols);
    map.initialize(settings.wildCount, settings.heartCount, settings.mysteryCount);


    // main game loop - player moves around map and encounters wild creatures
    while (true) {
        map.print();

        // win or lose conditions
        if (!map.hasWildsLeft()) {
            printVictoryMsg();
            break;
        }
        if (playerCreature->isFainted()) {
            if (!map.hasHeartsLeft()) {
                printLoseMsg();
                break;
            } else {
                std::cout << "\n" << playerCreature->name() << " has fainted. Find a heart to recover!\n";
            }
        }

        // move player
        char input;
        std::cout << "\nEnter move: (I for instructions)\n";
        std::cout << "> ";

        std::string line;
        getline(cin, line);
        std::cout << "\n\n\n\n\n\n\n\n"; // add spacing after input
        if (line.length() > 1) {
            cout << "\nInvalid input. Please enter a single character.\n";
            continue;
        }
        input = line[0];
        
        if (input == 'q' || input == 'Q') { break; }
        if (input == 'i' || input == 'I') {
            map.printInstructions();
            continue;
        }
        if (!map.movePlayer(input)) { continue; }

        // heart encounter
        if (map.hasHeart()) {
            std::cout << "\n" << playerCreature->name() << " found a healing heart!\n";
            playerCreature->healToFull();
            map.clearHeart();
            std::cout << playerCreature->name() << " was restored to full HP!\n";
        }

        // mystery encounter
        if (map.hasMystery()) {
            std::cout << "\n" << playerCreature->name() << " found a mystery box!\n";

            std::uniform_int_distribution<int> dist(0, 3); // 4 possible outcomes
            int outcome = dist(Random::rng());

            if (outcome == 0) {
                // positive effect: increase max HP
                playerCreature->changeMaxHp(10);
                std::cout << playerCreature->name() << " gained +10 max HP!\n";
            } else if (outcome == 1) {
                // negative effect: decrease max HP
                playerCreature->changeMaxHp(-10);
                std::cout << playerCreature->name() << " lost 10 max HP...\n";
            } else if (outcome == 2) {
                // DEATH EFFECT: faint immediately
                playerCreature->health().damage(playerCreature->health().current());
                std::cout << "Oh no! It was a trap! " << playerCreature->name() << " took massive damage and fainted!\n";
            } else if (outcome == 3) {
                // negative effect: decrease stats (attack, defense, speed)
                playerCreature->stats().attack = std::max(1, playerCreature->stats().attack - 5);
                playerCreature->stats().defense = std::max(1, playerCreature->stats().defense - 5);
                playerCreature->stats().speed = std::max(1, playerCreature->stats().speed - 5);
                std::cout << playerCreature->name() << "'s stats were reduced!\n";
            } else {
                // no effect
                std::cout << playerCreature->name() << " found nothing special.\n";
            }

            std::cout << "New HP: "
                    << playerCreature->health().current()
                    << "/" << playerCreature->health().max() << "\n";

            map.clearMystery();
        }

        // wild battle encounter
        if (map.hasEncounter()) {
            if (playerCreature->isFainted()) {
                cout << "\nYour creature has fainted and cannot battle.\n";
                // move player back to previous position to avoid repeated encounters
                moveToPreviousPosition(map, input);
                continue; // skip battle
            }

            auto enemyCreature = createRandomWildCreature();

            Battle battle(*playerCreature, *enemyCreature, playerController, enemyController);
            battle.run();

            if (enemyCreature->isFainted()) {
                // only remove enemy after victory
                map.clearEncounter();
            } else {
                moveToPreviousPosition(map, input);
            }
        }
    }
}
