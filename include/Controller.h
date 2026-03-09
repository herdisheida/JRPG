#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <limits>
#include <random>
#include "Creature.h"

using namespace std;

class Controller {
    public:
        virtual ~Controller() = default;
        virtual int chooseMove(const Creature& self, const Creature& opponent) = 0;
};

class PlayerController : public Controller {
    public:
        int chooseMove(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            cout << "\n" << self.name() << "'s turn!\n";
            cout << "Choose an action:\n";

            const auto& moves = self.moves();
            for (size_t i = 0; i < moves.size(); ++i) {
                cout << (i + 1) << ". " << moves[i].name
                        << " (Power " << moves[i].power
                        << ", Accuracy " << moves[i].accuracy << "%)\n";
            }

            int choice;
            while (true) {
                cout << "> ";
                cin >> choice;

                if (cin.fail() || choice < 1 || choice > static_cast<int>(moves.size())) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid choice. Try again.\n";
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