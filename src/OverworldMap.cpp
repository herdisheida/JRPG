#include "../include/OverworldMap.h"
#include <string>


const std::string PLAYER_SYMBOL = "P";
const std::string WILD_SYMBOL = "w";
const std::string HEART_SYMBOL = "\u2665";
const std::string MYSTERY_SYMBOL = "?";
const std::string EMPTY_SYMBOL = ".";



OverworldMap::OverworldMap(int rows, int cols)
    : rows_(rows),
      cols_(cols),
      playerPos_{0, 0},
      rng_(std::random_device{}()) {}

void OverworldMap::initialize(int wildCount, int heartCount, int mysteryCount) {
    playerPos_ = {0, 0};
    wildPositions_.clear();
    heartPositions_.clear();
    mysteryPositions_.clear();

    std::uniform_int_distribution<int> rowDist(0, rows_ - 1);
    std::uniform_int_distribution<int> colDist(0, cols_ - 1);

    // place wild creatures
    while (static_cast<int>(wildPositions_.size()) < wildCount) {
        Position p{rowDist(rng_), colDist(rng_)};
        if (!(p == playerPos_)) {
            wildPositions_.insert(p);
        }
    }

    // place hearts
    while (static_cast<int>(heartPositions_.size()) < heartCount) {
        Position p{rowDist(rng_), colDist(rng_)};
        if (!(p == playerPos_) &&
            wildPositions_.count(p) == 0) {
            heartPositions_.insert(p);
        }
    }

    // place mysteries
    while (static_cast<int>(mysteryPositions_.size()) < mysteryCount) {
        Position p{rowDist(rng_), colDist(rng_)};
        if (!(p == playerPos_) &&
            wildPositions_.count(p) == 0 &&
            heartPositions_.count(p) == 0) {
            mysteryPositions_.insert(p);
        }
    }
}

bool OverworldMap::isInside(int row, int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

bool OverworldMap::movePlayer(char input) {
    int newRow = playerPos_.row;
    int newCol = playerPos_.col;

    switch (input) {
        case 'w': case 'W': --newRow; break;
        case 's': case 'S': ++newRow; break;
        case 'a': case 'A': --newCol; break;
        case 'd': case 'D': ++newCol; break;
        default:
            std::cout << "\nInvalid input. Use W A S D.\n";
            return false;
    }

    if (!isInside(newRow, newCol)) {
        std::cout << "\nYou cannot move outside the map!\n";
        return false;
    }

    playerPos_ = {newRow, newCol};
    return true;
}


// wild enemy encounter funcs
bool OverworldMap::hasEncounter() const {
    return wildPositions_.count(playerPos_) > 0;
}
void OverworldMap::clearEncounter() {
    wildPositions_.erase(playerPos_);
}

// heart funcs
bool OverworldMap::hasHeart() const {
    return heartPositions_.count(playerPos_) > 0;
}
void OverworldMap::clearHeart() {
    heartPositions_.erase(playerPos_);
}

// mystery funcs
bool OverworldMap::hasMystery() const {
    return mysteryPositions_.count(playerPos_) > 0;
}
void OverworldMap::clearMystery() {
    mysteryPositions_.erase(playerPos_);
}
bool OverworldMap::hasMysteriesLeft() const {
    return !mysteryPositions_.empty();
}

// win or lose conditions
bool OverworldMap::hasWildsLeft() const {
    return !wildPositions_.empty();
}
bool OverworldMap::hasHeartsLeft() const {
    return !heartPositions_.empty();
}

void OverworldMap::printInstructions() const {
    std::cout << "\n\n============ Instructions ============\n";
    std::cout << "(Q) to quit\n";
    std::cout << "(W A S D) to move\n\n";
    std::cout << "Map encounters:\n";
    std::cout << "    " << PLAYER_SYMBOL  << " = Player (you)\n";
    std::cout << "    " << WILD_SYMBOL    << " = Wild Creature (enemy)\n";
    std::cout << "    " << HEART_SYMBOL   << " = Heart (heal effect)\n";
    std::cout << "    " << MYSTERY_SYMBOL << " = Mystery... (unknown effect)\n";
    std::cout << "    " << EMPTY_SYMBOL   << " = Empty\n";
    std::cout << "=======================================\n";
}

void OverworldMap::print() const {
    std::cout << "\n\n======== OVERWORLD MAP =======\n";

    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            Position current{r, c};

            if (current == playerPos_) {
                std::cout << PLAYER_SYMBOL << " ";
            } else if (wildPositions_.count(current) > 0) {
                std::cout << WILD_SYMBOL << " ";
            } else if (heartPositions_.count(current) > 0) {
                std::cout << HEART_SYMBOL << " "; // heart symbol
            } else if (mysteryPositions_.count(current) > 0) {
                std::cout << MYSTERY_SYMBOL << " ";
            } else {
                std::cout << EMPTY_SYMBOL << " ";
            }
        }
        std::cout << '\n';
    }
}