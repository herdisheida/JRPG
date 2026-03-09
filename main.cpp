#include <iostream>
#include <memory>
#include <random>
#include <algorithm> // for std::transform
#include <cctype>    // for ::toupper

#include "include/Battle.h"
#include "include/Controller.h"
#include "include/Creature.h"
#include "include/OverworldMap.h"
#include "include/GameSettings.h"


using namespace std;

std::mt19937 rng(std::random_device{}());

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
    cout << "\nGive your creature a nickname: ";
    std::string nickname;
    cin >> nickname;

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
        std::cout << "\nMove with W A S D, or Q to quit: ";
        std::cin >> input;

        if (input == 'q' || input == 'Q') { break; }
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
            int outcome = dist(rng);

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
