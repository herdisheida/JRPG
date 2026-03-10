#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Controller.h"



class EnemyController : public Controller {
    private:
        std::mt19937 rng_;

    public:
        EnemyController() : rng_(std::random_device{}()) {}

        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;
            std::uniform_int_distribution<int> dist(0, static_cast<int>(self.actions().size()) - 1);
            return dist(rng_);
        }
};


#endif