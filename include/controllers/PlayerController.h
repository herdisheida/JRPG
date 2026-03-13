#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Controller.h"


#include <iostream>
#include <iomanip> // for std::setw
#include <vector>
#include <sstream>
#include <limits>

#include "../util/Colors.h"

constexpr int ACTION_BOX_OFFSET = 20;
constexpr size_t ACTION_BOX_WIDTH = 26;


class PlayerController : public Controller {
    private:
        std::string buildActionsGrid(const std::vector<Action>& actions) {
            if (actions.size() != 4) return "";

            auto box1 = buildActionBox(actions[0], 1);
            auto box2 = buildActionBox(actions[1], 2);
            auto box3 = buildActionBox(actions[2], 3);
            auto box4 = buildActionBox(actions[3], 4);

            std::ostringstream out;

            // first row
            for (size_t i = 0; i < box1.size(); ++i)
                out << box1[i] << "   " << box2[i] << "\n";

            out << "\n";

            // second row
            for (size_t i = 0; i < box3.size(); ++i)
                out << box3[i] << "   " << box4[i] << "\n";

            return out.str();
        }

        std::vector<std::string> buildActionBox(const Action& a, int number, size_t width = ACTION_BOX_WIDTH) {
            std::vector<std::string> lines;

            std::string effect;

            if      (a.kind == ActionKind::Attack)   effect = "Power: " + std::to_string(a.power);
            else if (a.kind == ActionKind::Heal)     effect = "Heal: " + std::to_string(a.power);
            else if (a.kind == ActionKind::Status)   effect = statusToString(a.statusEffect) + " " + std::to_string(a.statusDuration) + "t";
            
            std::string acc = "Acc: " + std::to_string(a.accuracy) + "%";

            // helper to pad str to fit in ActionBox

            lines.push_back("+"  + std::string(width - 2, '-')                                                    + "+");
            lines.push_back("|"  + UIHelper::center(std::to_string(number) + ". " + a.name, width - 2)    + "|"); 
            lines.push_back("|"  + UIHelper::center(effect, width - 2)                                        + "|");
            lines.push_back("|"  + UIHelper::center(acc, width - 2)                                           + "|");
            lines.push_back("+"  + std::string(width - 2, '-')                                                    + "+");

            return lines;
        }

        // helper to pad str to fit in ActionBox
        std::string pad(const std::string& s, size_t width = ACTION_BOX_WIDTH) {
            if (s.size() >= width)
                return s.substr(0, width);
            return s + std::string(width - s.size(), ' ');
        }


    public:
        int chooseAction(const Creature& self, const Creature& opponent) override {
            (void)opponent;

            // print action grid
            std::cout << "\n" << std::string(ACTION_BOX_OFFSET, ' ') << "Choose an action:\n\n";
            std::string grid = buildActionsGrid(self.actions());
            UIHelper::printWithOffset(grid, ACTION_BOX_OFFSET);
            
            int choice;
            while (true) {
                std::cout << "> ";
                std::cin >> choice;
                std::cout << "\n\n\n\n"; // space after input for readability
                
                int maxChoice = self.actions().size() + 1;

                if (std::cin.fail() || choice < 1 || choice > maxChoice) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << UIHelper::getErrorStr("Invalid choice. Try again.\n");
                } else {
                    // clear leftover newline before returning
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return choice - 1;
                }
            }
        }
};

#endif
