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

    public:
        Battle(
            std::unique_ptr<Creature> playerCreature,
            std::unique_ptr<Creature> enemyCreature,
            std::unique_ptr<Controller> playerController,
            std::unique_ptr<Controller> enemyController);

        void run(); // game loop

    private:
        void printStatus() const;
        void doAttack(Creature& attacker, Creature& defender, int moveIndex);
};

#endif