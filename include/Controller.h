#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <limits>
#include <random>
#include "Creature.h"

class Controller {
    public:
        virtual ~Controller() = default;
        virtual int chooseAction(const Creature& self, const Creature& opponent) = 0;
};

class PlayerController : public Controller {
    public:
        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            std::cout << "\n" << self.name() << "'s turn!\n";
            std::cout << "Choose an action:\n";

            const auto& actions = self.actions();
            for (size_t i = 0; i < actions.size(); ++i) {
                std::cout << (i + 1) << ". " << actions[i].name
                        << " [" << actionKindToString(actions[i].kind) << "]";

                if (actions[i].kind == ActionKind::Attack) {
                    std::cout << " Power:" << actions[i].power
                            << " Accuracy:" << actions[i].accuracy
                            << "% Type:" << toString(actions[i].damageType);
                } else if (actions[i].kind == ActionKind::Heal) {
                    std::cout << " Heal:" << actions[i].power;
                }

                std::cout << "\n";
            }

            int choice;
            while (true) {
                std::cout << "> ";
                std::cin >> choice;

                if (std::cin.fail() || choice < 1 || choice > static_cast<int>(actions.size())) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid choice. Try again.\n";
                } else {
                    return choice - 1;
                }
            }
        }
};

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