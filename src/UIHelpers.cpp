
#include <iomanip> // for std::setw
#include <sstream>
#include <string>

#include "../include/creatures/Creature.h"
#include "../include/util/UIHelpers.h"


void UIHelper::waitForEnter(const std::string& prompt) {
    std::cout << prompt;
    std::cin.get(); // waits for user to press Enter
}

void UIHelper::printAscii(std::vector<std::string> ascii, int offset) {
    for (const auto& line : ascii) {
        std::cout << std::setw(offset) << "" << line << "\n";
    }
}


// print a simple text-based health bar
void UIHelper::printHealthBar(const Creature& creature, int offset) {
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


void UIHelper::printWithOffset(const std::string& text, int offset) {
    std::istringstream in(text);
    std::string line;

    while (std::getline(in, line)) {
        std::cout << std::string(offset, ' ') << line << "\n";
    }
}

std::string UIHelper::getSpacer(int length) {
    return std::string(length, '=');
}



std::string UIHelper::getColored(const std::string& text, Color::Code color, int offset) {
    return std::string(offset, ' ') + Color::colorize(text, color);
}
std::string UIHelper::getSuccessStr(const std::string& text, int offset) {
    return getColored(text, Color::BRIGHT_GREEN, offset);
}
std::string UIHelper::getErrorStr(const std::string& text, int offset) {
    return getColored(text, Color::BRIGHT_RED, offset);
}
