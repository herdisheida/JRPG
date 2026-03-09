#include <iostream>
#include <memory>

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

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    cout << "=== Mini JRPG Battle ===\n\n";

    // get player creature
    auto playerCreature = chooseCreature("Choose your creature:");
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
            auto enemyCreature = createRandomWildCreature();

            Battle battle(*playerCreature, *enemyCreature, playerController, enemyController);
            battle.run();

            map.clearEncounter();
        }
    }
}
