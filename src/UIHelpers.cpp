
#include <iomanip> // for std::setw
#include <sstream>
#include <string>
#include <stddef.h>
#include <iostream>
#include <limits>

#include "../include/creatures/Creature.h"
#include "../include/util/UIHelpers.h"
#include "../include/util/Colors.h"
#include "../include/util/Health.h"
#include "../include/util/Status.h"


void UIHelper::waitForEnter(const std::string& prompt) {
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // waits for user to press Enter
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
    std::string hpInfo = UIHelper::getColored("HP: " + std::to_string(creature.health().current()) + "/" + std::to_string(creature.health().max()), Color::BOLD);
    std::string statusInfo = UIHelper::getColored(statusToString(creature.status()), Color::BOLD);

    std::cout << std::string(offset, ' ') << UIHelper::getColored(creature.name(), Color::BOLD) << std::string(totalBarLength - creature.name().length() - hpInfo.length(), ' ') << hpInfo << "\n\n";
    std::cout << std::string(offset, ' ') << "[ " << bar << " ]  " << UIHelper::getColored(statusInfo, Color::UNDERLINE);
    std::cout << "\n\n";
}

// print string with offset
void UIHelper::printWithOffset(const std::string& text, int offset) {
    std::istringstream in(text);
    std::string line;

    while (std::getline(in, line)) {
        std::cout << std::string(offset, ' ') << line << "\n";
    }
}

// center text in a field of given width
std::string UIHelper::center(const std::string& s, size_t width) {
    if (s.size() >= width) return s.substr(0, width);
    size_t left = (width - s.size()) / 2;
    size_t right = width - s.size() - left;
    return std::string(left, ' ') + s + std::string(right, ' ');
}



// get string input (max 15 chars, only letters and underscores)
std::string UIHelper::getStringInput(const std::string& prompt, std::string nameOfInput) {
    std::cout << '\n' << prompt << "\n> ";
    std::string input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << UIHelper::getErrorStr('\n' + nameOfInput + " cannot be empty.") << " Please enter a valid " << nameOfInput << ". \n> ";
            continue;
        }
        if (input.length() >= 15) {
            std::cout << UIHelper::getErrorStr('\n' + nameOfInput + " too long.") << " Please enter a " << nameOfInput << " with 15 characters or fewer. \n> ";
            continue;
        }
        if (input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") != std::string::npos) {
            std::cout << UIHelper::getErrorStr('\n' + nameOfInput + " contains invalid characters.") << " Please use only letters or underscores. \n> ";
            continue;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << UIHelper::getErrorStr("Invalid input.\n\n");
            continue;
        }
        break;
    }
    return input;
}




// color helpers
std::string UIHelper::getColored(const std::string& text, Color::Code color, int offset) {
    return std::string(offset, ' ') + Color::colorize(text, color);
}
std::string UIHelper::getSuccessStr(const std::string& text, int offset) {
    return getColored(text, Color::BRIGHT_GREEN, offset);
}
std::string UIHelper::getErrorStr(const std::string& text, int offset) {
    return getColored(text, Color::BRIGHT_RED, offset);
}
