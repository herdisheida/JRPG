#include "../include/util/UIHelpers.h"

#include <iomanip> // for std::setw
#include "../include/creatures/Creature.h"


void printAscii(std::vector<std::string> ascii, int offset) {
    for (const auto& line : ascii) {
        std::cout << std::setw(offset) << "" << line << "\n";
    }
}

// print a simple text-based health bar
void printHealthBar(const Creature& creature, int offset) {
    // calculate green and red ratio
    int barWidth = 15;
    float hpRatio = static_cast<float>(creature.health().current()) / creature.health().max();
    int greenBars = static_cast<int>(hpRatio * barWidth);
    int redBars = barWidth - greenBars;

    std::string bar;
    for (int i = 0; i < greenBars; i++)
        bar += "🟩";
    for (int i = 0; i < redBars; i++)
        bar += "🟥";

    int totalBarLength = barWidth * 2 + 4; // each bar is 2 characters wide + 2 for brackets + 2 spaces
    std::string hpInfo = "HP: " + std::to_string(creature.health().current()) + "/" + std::to_string(creature.health().max());
    std::cout << std::string(offset, ' ') << creature.name() << std::string(totalBarLength - creature.name().length() - hpInfo.length(), ' ') << hpInfo << "\n\n";
    std::cout << std::string(offset, ' ') << "[ " << bar << " ]\n\n";
}
