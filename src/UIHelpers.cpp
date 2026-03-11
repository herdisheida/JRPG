#include "../include/util/Helpers.h"

#include <iomanip> // for std::setw

void printAscii(std::vector<std::string> ascii, int offset) {
    for (const auto& line : ascii) {
        std::cout << std::setw(offset) << "" << line << "\n";
    }
}
