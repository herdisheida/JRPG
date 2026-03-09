#include "../include/Battle.h"

#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

Battle::Battle(
                std::unique_ptr<Creature> playerCreature,
               std::unique_ptr<Creature> enemyCreature,
               std::unique_ptr<Controller> playerController,
               std::unique_ptr<Controller> enemyController)
    : playerCreature_(std::move(playerCreature)),
      enemyCreature_(std::move(enemyCreature)),
      playerController_(std::move(playerController)),
      enemyController_(std::move(enemyController)) {}

void Battle::printStatus() const {
    cout << "\n"
              << playerCreature_->name() << " (" << playerCreature_->health().current()
              << "/" << playerCreature_->health().max() << ")"
              << " | "
              << enemyCreature_->name() << " (" << enemyCreature_->health().current()
              << "/" << enemyCreature_->health().max() << ")\n";
}

void Battle::doAttack(Creature& attacker, Creature& defender, int moveIndex) {
    static std::mt19937 rng(std::random_device{}());

    const Move& move = attacker.moves().at(moveIndex);

    std::uniform_int_distribution<int> hitRoll(1, 100);
    if (hitRoll(rng) > move.accuracy) {
        cout << attacker.name() << " uses " << move.name << " but misses!\n";
        return;
    }

    std::uniform_int_distribution<int> variance(0, 2);

    int rawDamage = attacker.stats().attack + move.power - defender.stats().defense;
    int damage = std::max(1, rawDamage + variance(rng));

    defender.health().damage(damage);

    cout << attacker.name() << " uses " << move.name
              << " dealing " << damage << " damage!\n";
}

void Battle::run() {
    cout << "A wild " << enemyCreature_->name() << " appears!\n";
    cout << "You send out " << playerCreature_->name() << "!\n";

    while (!playerCreature_->isFainted() && !enemyCreature_->isFainted()) {
        printStatus();

        bool playerGoesFirst =
            playerCreature_->stats().speed >= enemyCreature_->stats().speed;

        if (playerGoesFirst) {
            int playerMove = playerController_->chooseMove(*playerCreature_, *enemyCreature_);
            doAttack(*playerCreature_, *enemyCreature_, playerMove);

            if (enemyCreature_->isFainted()) {
                cout << enemyCreature_->name() << " has fainted! "
                          << playerCreature_->name() << " wins!\n";
                break;
            }

            int enemyMove = enemyController_->chooseMove(*enemyCreature_, *playerCreature_);
            cout << "\n" << enemyCreature_->name() << "'s turn!\n";
            doAttack(*enemyCreature_, *playerCreature_, enemyMove);

            if (playerCreature_->isFainted()) {
                cout << playerCreature_->name() << " has fainted! "
                          << enemyCreature_->name() << " wins!\n";
                break;
            }
        } else {
            int enemyMove = enemyController_->chooseMove(*enemyCreature_, *playerCreature_);
            cout << "\n" << enemyCreature_->name() << "'s turn!\n";
            doAttack(*enemyCreature_, *playerCreature_, enemyMove);

            if (playerCreature_->isFainted()) {
                cout << playerCreature_->name() << " has fainted! "
                          << enemyCreature_->name() << " wins!\n";
                break;
            }

            int playerMove = playerController_->chooseMove(*playerCreature_, *enemyCreature_);
            doAttack(*playerCreature_, *enemyCreature_, playerMove);

            if (enemyCreature_->isFainted()) {
                cout << enemyCreature_->name() << " has fainted! "
                          << playerCreature_->name() << " wins!\n";
                break;
            }
        }
    }

    printStatus();
}