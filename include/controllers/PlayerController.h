#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Controller.h"



class PlayerController : public Controller {
    private:
        void printActionOptions(const Creature& self) const {
            const auto& actions = self.actions();
            std::cout << "Choose an action:\n\n";

            // std::cout << "----------------------------------\n";
            for (size_t i = 0; i < actions.size(); ++i) {
                std::cout << (i + 1) << ". " << actions[i].name;

                if (actions[i].kind == ActionKind::Attack) { std::cout << " (Power " << actions[i].power << ")"; }
                if (actions[i].kind == ActionKind::Status) { std::cout << " (" << statusToString(actions[i].statusEffect) << " " << actions[i].statusDuration << " turn)"; }
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

#endif
