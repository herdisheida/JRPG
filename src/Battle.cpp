#include <iostream>
#include <iomanip> // for std::setw

#include "../include/battle/Battle.h"
#include "../include/controllers/Controller.h"
#include "../include/util/Random.h"


const int ENEMY_OFFSET = 80; // where enemy info appears  (top right)
const int PLAYER_OFFSET = 10; // where player info appears (bottom left)
const int PLAYER_HP_OFFSET = 3; // where player hp appears (bottom left)
const int MSG_OFFSET = 0; // where action messages appear (between player and enemy)



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


// print a simple text-based health bar
void Battle::printHealthBar(const Creature& creature, int offset) const {
    // calculate green and red ratio
    int barWidth = 15;
    float hpRatio = static_cast<float>(creature.health().current()) / creature.health().max();
    int greenBars = static_cast<int>(hpRatio * barWidth);
    int redBars = barWidth - greenBars;

    std::string bar;
    for (int i = 0; i < greenBars; i++)
        bar += "🟩";
    for (int i = 0; i < redBars; i++)
        bar += "🟥";

    int totalBarLength = barWidth * 2 + 4; // each bar is 2 characters wide + 2 for brackets + 2 spaces
    std::string hpInfo = "HP: " + std::to_string(creature.health().current()) + "/" + std::to_string(creature.health().max());
    std::cout << std::string(offset, ' ') << creature.name() << std::string(totalBarLength - creature.name().length() - hpInfo.length(), ' ') << hpInfo << "\n\n";
    std::cout << std::string(offset, ' ') << "[ " << bar << " ]\n\n";
}

void Battle::printBattleScreen(const Creature& player, const Creature& enemy, const std::string& p_msg, const std::string& e_msg, int& round) const {
    std::cout << "\n\n========================================================= Round " << round++ << " =========================================================\n\n";

    // print enemy top right 
    printHealthBar(enemy, ENEMY_OFFSET);
    enemy.printAscii(ENEMY_OFFSET);


    // print player bottom left
    player.printAscii(PLAYER_OFFSET);
    std::cout << "\n";
    printHealthBar(player, PLAYER_HP_OFFSET);

    // print previous action (enemy and player moves) message
    if (!p_msg.empty() && !player.isFainted()) std::cout << "\n" << std::string(MSG_OFFSET, ' ') << p_msg;
    if (!e_msg.empty() && !enemy.isFainted() && !fled_) std::cout << "\n" << std::string(MSG_OFFSET, ' ') << e_msg << "\n\n";
}


std::string Battle::executeAction(Creature& actor, Creature& target, const Action& action, bool isPlayer) {
    if (!Random::rollPercent(action.accuracy)) {
        return actor.name() + " uses " + action.name + " but it misses! ";
    }

    std::string msg;

    switch (action.kind) {
        case ActionKind::Attack: {
            int baseDamage = actor.stats().attack + action.power - target.stats().defense; // attack + move power - target defense
            baseDamage = std::max(1, baseDamage);

            std::uniform_int_distribution<int> variance(-5, 5); // random variance -5 to 5
            int damage = baseDamage + variance(Random::rng());

            float typeMultiplier = target.resistanceTo(action.damageType); // type effectiveness
            damage = static_cast<int>(damage * typeMultiplier);

            if (target.isDefending()) {
                damage = std::max(1, damage / 2);
            }

            bool critical = Random::rollPercent(action.critChance);
            if (critical) {
                damage *= 2;
            }

            damage = std::max(1, damage);
            target.health().damage(damage);

            // build msg
            msg = actor.name() + " uses " + action.name + " dealing " + std::to_string(damage) + " " + toString(action.damageType) + " damage";

            if (critical) msg += " - Critical hit!";

            if (typeMultiplier < 1.0f) msg += " Not very effective. ";
            if (typeMultiplier > 1.0f) msg += " Super effective! ";
            if (target.isDefending()) msg += " - Enemy defended and took less damage! ";
            break;
        }

        case ActionKind::Heal: {
            actor.health().heal(action.power);
            msg = actor.name() + " uses " + action.name + " and restores " + std::to_string(action.power) + " HP! ";
            break;
        }

        case ActionKind::Defend: {
            actor.setDefending(true);
            msg = actor.name() + " uses " + action.name + " and braces for the next hit! ";
            break;
        }

        case ActionKind::Flee: {
            int fleeChance = isPlayer ? 60 : 20;
            if (Random::rollPercent(fleeChance)) {
                fled_ = true;
                msg = isPlayer ? actor.name() + " successfully fled from battle!" : actor.name() + " ran away safely ";
            } else {
                msg = actor.name() + " tried to flee, but couldn't escape! ";
            }
            break;
        }

        case ActionKind::Status: {
            if (target.hasStatus()) {
                msg =  target.name() + " already has a status effect! ";
                break;
            }

            target.setStatus(action.statusEffect, action.statusDuration);

            msg = actor.name() + " uses " + action.name + "! "
                    + target.name() + " is now "
                    + statusToString(action.statusEffect) + " for "
                    + std::to_string(action.statusDuration) + " turn(s)! ";
            break;
        }
    }
    return msg;
}

std::string Battle::takeTurn(Creature& actor, Creature& target, Controller& controller, bool isPlayer) {
    std::string msg;

    // creature is paralized
    if (actor.status() == StatusEffect::Paralyze) {
        msg = actor.name() + " is paralyzed and cannot act! ";

        actor.reduceStatusTurns();
        if (!actor.hasStatus()) msg += actor.name() + " woke up! ";
        return msg;
    }

    int chosen = controller.chooseAction(actor, target);

    // player flee option
    int actionCount = static_cast<int>(actor.actions().size());
    if (isPlayer && chosen == actionCount) {
        Action fleeAction("Flee", ActionKind::Flee, 0, 100, 0, DamageType::Physical);
        msg += executeAction(actor, target, fleeAction, true);
        return msg;
    }

    // creature action
    const Action& action = actor.actions().at(chosen);
    msg += executeAction(actor, target, action, isPlayer);

    msg += applyStatusEffect(actor); // at end of turn

    if (fled_ || actor.isFainted() || target.isFainted()) {
        return msg;
    }

    return msg;
}

// Damage creature with status effect
std::string Battle::applyStatusEffect(Creature& creature) {
    std::string msg;

    if (creature.status() != StatusEffect::None) {

        int damage;
        if (creature.status() == StatusEffect::Poison) {
            damage = creature.health().max() / 8; // poison damage is 1/8 of max HP
        } else {
            damage = 20; // default damage for other status effects
        }

        creature.health().damage(damage);
        msg += " " + creature.name() + " suffers " + std::to_string(damage) + " " + takeDamageString(creature.status()) + "! ";

        std::string statusStr = statusToString(creature.status()); // save before reducing status
        creature.reduceStatusTurns();
        if (!creature.hasStatus()) msg += creature.name() + " is no longer " + statusStr + ". ";
    }

    return msg;
}


void Battle::run() {
    std::cout << "\n\n\n";

    // first print (init status)
    int round = 1;
    printBattleScreen(playerCreature_, enemyCreature_, "", "", round); // initial status
    std::cout << "\n\n" << std::string(MSG_OFFSET, ' ') << "A wild " << enemyCreature_.name() << " appears!\n";


    std::string p_msg, e_msg;
    while (!playerCreature_.isFainted() && !enemyCreature_.isFainted() && !fled_) {
        bool playerFirst = playerCreature_.stats().speed >= enemyCreature_.stats().speed;

        if (playerFirst) {
            p_msg = takeTurn(playerCreature_, enemyCreature_, playerController_, true); // player goes first
            e_msg = takeTurn(enemyCreature_, playerCreature_, enemyController_, false); // enemy goes second
        } else {
            if (round == 2) std::cout << std::string(MSG_OFFSET, ' ') << enemyCreature_.name() << " is FASTER and takes the first moves!\n";
            e_msg = takeTurn(enemyCreature_, playerCreature_, enemyController_, false); // enemy goes first
            p_msg = takeTurn(playerCreature_, enemyCreature_, playerController_, true); // player second
        }

        // print battle each round
        printBattleScreen(playerCreature_, enemyCreature_, p_msg, e_msg, round); // print status with health bars

        if (enemyCreature_.isFainted() || playerCreature_.isFainted() || fled_) return;

        // reset defending state at end of round
        playerCreature_.setDefending(false);
        enemyCreature_.setDefending(false);
    }

    
    if (fled_) {
        std::cout << "The battle is over.\n";
    } else if (playerCreature_.isFainted()) {
        // Enemy wins
        std::cout << playerCreature_.name() << " has fainted! Find a heart to recover!\n";
    } else if (enemyCreature_.isFainted()) {
        // Player wins
        std::cout << enemyCreature_.name() << " has fainted! " << playerCreature_.name() << " wins!\n";
    }
}
