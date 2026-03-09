#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <random>

#include "Creature.h"

class Controller {
    public:
        virtual ~Controller() = default;
        virtual int chooseAction(const Creature& self, const Creature& opponent) = 0;
};

class PlayerController : public Controller {
    private:
        void printActionOptions(const Creature& self) const {
            const auto& actions = self.actions();
            std::cout << "Choose an action:\n\n";

            // std::cout << "----------------------------------\n";
            for (size_t i = 0; i < actions.size(); ++i) {
                std::cout << (i + 1) << ". " << actions[i].name;

                if (actions[i].kind == ActionKind::Attack) { std::cout << " (Power " << actions[i].power << ")"; }
                if (actions[i].kind == ActionKind::Heal) { std::cout << " (Heal " << actions[i].power << ")"; }

                std::cout << "\n";
            }
            // std::cout << "----------------------------------\n";
            std::cout << actions.size() + 1 << ". Flee\n";
        }

    public:
        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            std::cout << "\n" << self.name() << "'s turn!\n";
            printActionOptions(self);

            int choice;
            while (true) {
                std::cout << "> ";
                std::cin >> choice;
                std::cout << "\n";
                
                int maxChoice = self.actions().size() + 1;

                if (std::cin.fail() || choice < 1 || choice > maxChoice) {
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