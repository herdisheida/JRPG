#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Controller.h"
#include "../util/Random.h"


class EnemyController : public Controller {
    public:
        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;
            std::uniform_int_distribution<int> dist(0, static_cast<int>(self.actions().size()) - 1);
            return dist(Random::rng());  // use the global RNG from Random namespace
        }

};


#endif