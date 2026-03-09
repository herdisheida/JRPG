#ifndef BATTLE_H
#define BATTLE_H

#include <memory>
#include "Controller.h"
#include "Creature.h"

class Battle {
    private:
        std::unique_ptr<Creature> playerCreature_;
        std::unique_ptr<Creature> enemyCreature_;
        std::unique_ptr<Controller> playerController_;
        std::unique_ptr<Controller> enemyController_;
        bool fled_;

    public:
        Battle(std::unique_ptr<Creature> playerCreature,
            std::unique_ptr<Creature> enemyCreature,
            std::unique_ptr<Controller> playerController,
            std::unique_ptr<Controller> enemyController);

        void run();

    private:
        void printStatus() const;
        bool takeTurn(Creature& actor, Creature& target, Controller& controller, bool isPlayer);
        void executeAction(Creature& actor, Creature& target, const Action& action, bool isPlayer);
};

#endif