#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Controller.h"
// #include "../util/UIHelpers.h"


#include <iostream>
#include <iomanip> // for std::setw
#include <vector>
#include <sstream>
#include <limits>




class PlayerController : public Controller {
    private:
        std::string buildActionsTable(const std::vector<Action>& actions) const {
            constexpr int numWidth = 4;      // width for numbering
            constexpr int nameWidth = 20;    // width for action name
            constexpr int effectWidth = 25;  // width for power/heal/status
            constexpr int accWidth = 10;     // width for accuracy column

            std::ostringstream out;

            // header
            out << std::left
                    << std::setw(numWidth) << "No."
                    << std::setw(nameWidth) << "Name"
                    << std::setw(effectWidth) << "Effect"
                    << std::setw(accWidth) << "Accuracy"
                    << "\n";

            // separator
            out << std::string(numWidth + nameWidth + effectWidth + accWidth, '-') << "\n";

            // actions
            for (size_t i = 0; i < actions.size(); ++i) {
                const auto& a = actions[i];
                std::string effect;

                if (a.kind == ActionKind::Attack) {
                    effect = "Power " + std::to_string(a.power);
                } else if (a.kind == ActionKind::Heal) {
                    effect = "Heal " + std::to_string(a.power);
                } else if (a.kind == ActionKind::Status) {
                    effect = statusToString(a.statusEffect) + " " + std::to_string(a.statusDuration) + " turn";
                }

                out << std::left
                        << std::setw(numWidth)     << (i + 1)
                        << std::setw(nameWidth)    << a.name
                        << std::setw(effectWidth)  << effect
                        << std::setw(accWidth)     << (std::to_string(a.accuracy) + "%")
                        << "\n";
            }

            // add Flee as last option
            out << std::left
                    << std::setw(numWidth) << (actions.size() + 1)
                    << std::setw(nameWidth) << "Flee"
                    << "\n";

            return out.str();
        }

        void printActionOptions(const Creature& self) const {
            constexpr int MSG_OFFSET = 0; // where action messages appear (between player and enemy)
            const auto& actions = self.actions();
            std::cout << "\n" << std::string(MSG_OFFSET, ' ') << "Choose an action:\n\n";
            std::string actionsTable = buildActionsTable(actions);
            UIHelper::printWithOffset(actionsTable, MSG_OFFSET);
        }

    public:
        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            printActionOptions(self);

            int choice;
            while (true) {
                std::cout << "> ";
                std::cin >> choice;
                std::cout << "\n\n\n\n"; // space after input for readability
                
                int maxChoice = self.actions().size() + 1;

                if (std::cin.fail() || choice < 1 || choice > maxChoice) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid choice. Try again.\n";
                } else {
                    // clear leftover newline before returning
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return choice - 1;
                }
            }
        }
};

#endif
