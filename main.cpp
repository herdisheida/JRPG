#include <iostream>
#include <memory>

#include "include/Battle.h"
#include "include/Controller.h"
#include "include/Creature.h"

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

int main() {
    cout << "=== Mini JRPG Battle ===\n\n";

    auto playerCreature = chooseCreature("Choose your creature:");
    auto enemyCreature = chooseCreature("Choose the enemy creature:");

    Battle battle(
        std::move(playerCreature),
        std::move(enemyCreature),
        std::make_unique<PlayerController>(),
        std::make_unique<EnemyController>());

    battle.run();

    return 0;
}