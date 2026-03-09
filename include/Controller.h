#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <limits>
#include <random>
#include "Creature.h"

class Controller {
    public:
        virtual ~Controller() = default;
        virtual int chooseMove(const Creature& self, const Creature& opponent) = 0;
};

class PlayerController : public Controller {
    public:
        int chooseMove(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            std::cout << "\n" << self.name() << "'s turn!\n";
            std::cout << "Choose an action:\n";

            const auto& moves = self.moves();
            for (size_t i = 0; i < moves.size(); ++i) {
                std::cout << (i + 1) << ". " << moves[i].name
                        << " (Power " << moves[i].power
                        << ", Accuracy " << moves[i].accuracy << "%)\n";
            }

            int choice;
            while (true) {
                std::cout << "> ";
                std::cin >> choice;

                if (std::cin.fail() || choice < 1 || choice > static_cast<int>(moves.size())) {
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

        int chooseMove(const Creature& self, const Creature& opponent) override {
            (void)opponent;
            std::uniform_int_distribution<int> dist(0, static_cast<int>(self.moves().size()) - 1);
            return dist(rng_);
        }
};

#endif