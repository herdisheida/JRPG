#ifndef BATTLE_H
#define BATTLE_H

#include <memory>
#include <string>

#include "../controllers/Controller.h"
#include "../creatures/Creature.h"

class Battle {
    // doesn't work after adding overwolrd
    // private:
    //     std::unique_ptr<Creature> playerCreature_;
    //     std::unique_ptr<Creature> enemyCreature_;
    //     std::unique_ptr<Controller> playerController_;
    //     std::unique_ptr<Controller> enemyController_;
    //     bool fled_;
    private:
        Creature& playerCreature_;
        Creature& enemyCreature_;
        Controller& playerController_;
        Controller& enemyController_;
        bool fled_;

    public:
        // Battle(
        //     std::unique_ptr<Creature> playerCreature,
        //     std::unique_ptr<Creature> enemyCreature,
        //     std::unique_ptr<Controller> playerController,
        //     std::unique_ptr<Controller> enemyController);
        Battle(
            Creature& playerCreature,
            Creature& enemyCreature,
            Controller& playerController,
            Controller& enemyController
        );

        void run();

    private:
        void printStatus() const;
        void printHealthBar(const Creature& creature) const; // health bar with 🟩 and 🟥 colors

        // returns the action result message
        std::string takeTurn(Creature& actor, Creature& target, Controller& controller, bool isPlayer);

        // returns the action result message
        std::string executeAction(Creature& actor, Creature& target, const Action& action, bool isPlayer);
        std::string applyStatusEffect(Creature& target);
};

#endif