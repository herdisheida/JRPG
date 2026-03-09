#include "../include/Battle.h"

#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

using std::cout;
using std::setw;
using std::left;


namespace {
    // random number generator
    std::mt19937& rng() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    bool rollPercent(int chance) {
        std::uniform_int_distribution<int> dist(1, 100);
        return dist(rng()) <= chance;
    }
}

Battle::Battle(
    Creature& playerCreature,
    Creature& enemyCreature,
    Controller& playerController,
    Controller& enemyController)
    : playerCreature_(playerCreature),
        enemyCreature_(enemyCreature),
        playerController_(playerController),
        enemyController_(enemyController),
        fled_(false) {}

void Battle::printStatus() const {
    cout << "\n==================================\n";

    cout << left << setw(8)  << "Your:"
         << setw(12) << playerCreature_.name()
         << "HP " << playerCreature_.health().current()
         << "/" << playerCreature_.health().max() << "\n";

    cout << left << setw(8)  << "Enemy:"
         << setw(12) << enemyCreature_.name()
         << "HP " << enemyCreature_.health().current()
         << "/" << enemyCreature_.health().max() << "\n";

    cout << "==================================\n";
}

void Battle::executeAction(Creature& actor, Creature& target, const Action& action, bool isPlayer) {
    if (!rollPercent(action.accuracy)) {
        cout << actor.name() << " uses " << action.name << " but it misses!\n";
        return;
    }

    switch (action.kind) {
        case ActionKind::Attack: {
            int baseDamage = actor.stats().attack + action.power - target.stats().defense;
            baseDamage = std::max(1, baseDamage);

            std::uniform_int_distribution<int> variance(0, 2);
            int damage = baseDamage + variance(rng());

            float typeMultiplier = target.resistanceTo(action.damageType);
            damage = static_cast<int>(damage * typeMultiplier);

            if (target.isDefending()) {
                damage = std::max(1, damage / 2);
            }

            bool critical = rollPercent(action.critChance);
            if (critical) {
                damage *= 2;
            }

            damage = std::max(1, damage);
            target.health().damage(damage);

            cout << actor.name() << " uses " << action.name
                      << " dealing " << damage << " " << toString(action.damageType)
                      << " damage";

            if (critical) {
                cout << " - Critical hit!";
            }

            if (typeMultiplier < 1.0f) {
                cout << " It's not very effective.";
            } else if (typeMultiplier > 1.0f) {
                cout << " It's super effective!";
            }

            if (target.isDefending()) {
                cout << " - The target was defending and took less damage!";
            }

            cout << "\n";
            break;
        }

        case ActionKind::Heal: {
            actor.health().heal(action.power);
            cout << actor.name() << " uses " << action.name
                      << " and restores " << action.power << " HP!\n";
            break;
        }

        case ActionKind::Defend: {
            actor.setDefending(true);
            cout << actor.name() << " uses " << action.name
                      << " and braces for the next hit!\n";
            break;
        }

        case ActionKind::Flee: {
            int fleeChance = isPlayer ? 60 : 20;
            if (rollPercent(fleeChance)) {
                fled_ = true;
                if (isPlayer) {
                    cout << actor.name() << " successfully fled from battle!\n";
                } else {
                    cout << actor.name() << " ran away safely\n";
                }
            } else {
                cout << actor.name() << " tried to flee, but couldn't escape!\n";
            }
            break;
        }

        case ActionKind::Status: {
            if (target.hasStatus()) {
                std::cout << target.name() << " already has a status effect!\n";
                break;
            }

            target.setStatus(action.statusEffect, action.statusDuration);

            std::cout << actor.name() << " uses " << action.name
                    << "! " << target.name() << " is now "
                    << statusToString(action.statusEffect) << " for "
                    << action.statusDuration << " turn(s)!\n";
            break;
        }
    }
}

bool Battle::takeTurn(Creature& actor, Creature& target, Controller& controller, bool isPlayer) {
    // creature is paralized
    if (actor.status() == StatusEffect::Paralyzed) {
        std::cout << actor.name() << " is paralyzed and cannot act!\n";

        actor.reduceStatusTurns();
        if (!actor.hasStatus()) std::cout << actor.name() << " woke up!\n";
        return true;
    }

    int chosen = controller.chooseAction(actor, target);

    // player flee option
    int actionCount = static_cast<int>(actor.actions().size());
    if (isPlayer && chosen == actionCount) {
        Action fleeAction("Flee", ActionKind::Flee, 0, 100, 0, DamageType::Physical);
        executeAction(actor, target, fleeAction, true);

        if (fled_) {
            return false;
        }
        return true;
    }

    // creature action
    const Action& action = actor.actions().at(chosen);
    executeAction(actor, target, action, isPlayer);

    applyStatusEffect(actor); // at end of turn

    if (fled_ || actor.isFainted() || target.isFainted()) {
        return false;
    }

    return true;
}

void Battle::applyStatusEffect(Creature& creature) {
    if (creature.status() == StatusEffect::Poison) {
        int poisonDamage = 5;
        creature.health().damage(poisonDamage);

        std::cout << creature.name() << " suffers " << poisonDamage << " poison damage!\n";

        creature.reduceStatusTurns();
        if (!creature.hasStatus()) std::cout << creature.name() << " is no longer poisoned.\n";
    }
}


void Battle::run() {
    cout << "\n\n\nA wild " << enemyCreature_.name() << " appears!\n\n";
    enemyCreature_.printAscii();
    cout << "\nYou send out " << playerCreature_.name() << "!\n";

    printStatus();
    bool printedAfterRound = false;
    int round = 1;


    while (!playerCreature_.isFainted() && !enemyCreature_.isFainted() && !fled_) {

        cout << "\n\n------------------ Round " << round++ << " ------------------\n\n";

        printedAfterRound = false;
        bool playerFirst = playerCreature_.stats().speed >= enemyCreature_.stats().speed;

        if (playerFirst) {
            // player goes first
            if (!takeTurn(playerCreature_, enemyCreature_, playerController_, true)) {
                break;
            }
            if (enemyCreature_.isFainted() || fled_) {
                break;
            }

            // enemy goes second
            if (!takeTurn(enemyCreature_, playerCreature_, enemyController_, false)) {
                break;
            }
            if (playerCreature_.isFainted() || fled_) {
                break;
            }
        } else {

            // enemy goes first
            if (round == 2) cout << "\n" << enemyCreature_.name() << " is faster and takes the first move!\n"; // only print this message once at the start of battle
            
            if (!takeTurn(enemyCreature_, playerCreature_, enemyController_, false)) {
                break;
            }
            if (playerCreature_.isFainted() || fled_) {
                break;
            }

            // player goes second
            if (!takeTurn(playerCreature_, enemyCreature_, playerController_, true)) {
                break;
            }
            if (enemyCreature_.isFainted() || fled_) {
                break;
            }
        }

        // print status after each round
        printStatus();
        printedAfterRound = true;

        // reset defending state at end of round
        playerCreature_.setDefending(false);
        enemyCreature_.setDefending(false);
    }

    if (!printedAfterRound && !fled_) { printStatus(); }
    
    if (fled_) {
        cout << "The battle is over.\n";
    } else if (playerCreature_.isFainted()) {
        // Enemy wins
        cout << playerCreature_.name() << " has fainted! " << enemyCreature_.name() << " wins!\n";
    } else if (enemyCreature_.isFainted()) {
        // Player wins
        cout << enemyCreature_.name() << " has fainted! " << playerCreature_.name() << " wins!\n";
    }
}