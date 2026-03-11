#ifndef BATTLE_H
#define BATTLE_H

#include <memory>
#include <string>

#include "../controllers/Controller.h"
#include "../creatures/Creature.h"

class Battle {
    private:
        Creature& playerCreature_;
        Creature& enemyCreature_;
        Controller& playerController_;
        Controller& enemyController_;
        bool fled_;

    public:
        Battle(
            Creature& playerCreature,
            Creature& enemyCreature,
            Controller& playerController,
            Controller& enemyController
        );

        void run();

    private:
        // print whole battle screen (like pokemon battle)
        void printBattleScreen(const Creature& player, const Creature& enemy, const std::string& p_msg, const std::string& e_msg, int& round) const;

        // returns the action result message
        std::string takeTurn(Creature& actor, Creature& target, Controller& controller, bool isPlayer);

        // returns the action result message
        std::string executeAction(Creature& actor, Creature& target, const Action& action, bool isPlayer);
        std::string applyStatusEffect(Creature& target);
};

#endif