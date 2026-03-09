#include <iostream>
#include <memory>

#include <algorithm> // for std::transform
#include <cctype>    // for ::toupper

#include "include/Battle.h"
#include "include/Controller.h"
#include "include/Creature.h"
#include "include/OverworldMap.h"


using namespace std;

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
        cout << "\n";

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

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    cout << "=== Mini JRPG Battle ===\n\n";
    auto playerCreature = chooseCreature("Choose your creature:");
    customizeCreature(*playerCreature);


    PlayerController playerController;
    EnemyController enemyController;

    // initalize overworld
    OverworldMap map(5, 7);
    map.initialize(6);

    while (true) {
        map.print();

        char input;
        std::cout << "\nMove with W A S D, or Q to quit: ";
        std::cin >> input;

        if (input == 'q' || input == 'Q') {
            break;
        }

        if (!map.movePlayer(input)) {
            continue;
        }

        map.print();

        if (map.hasEncounter()) {
            if (playerCreature->isFainted()) {
                cout << "\nYour creature has fainted and cannot battle.\n";
                // move player back to previous position to avoid repeated encounters
                switch (input) {
                    case 'w': case 'W': map.movePlayer('s'); break;
                    case 's': case 'S': map.movePlayer('w'); break;
                    case 'a': case 'A': map.movePlayer('d'); break;
                    case 'd': case 'D': map.movePlayer('a'); break;
                }
                continue; // skip battle
            }

            auto enemyCreature = createRandomWildCreature();

            Battle battle(*playerCreature, *enemyCreature, playerController, enemyController);
            battle.run();

            map.clearEncounter();
        }
    }
}
