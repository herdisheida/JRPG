#include <stddef.h> // for size_t
#include <string>
#include <iostream>
#include <fstream>
#include <random> // for
#include <set>    // for set


#include "../include/overworld/OverworldMap.h"
#include "../include/util/UIHelpers.h"


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


// -- helpers --
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
            std::cout << UIHelper::getErrorStr("\nInvalid input.") << " Use W A S D.\n";
            return false;
    }

    if (!isInside(newRow, newCol)) {
        std::cout << UIHelper::getErrorStr("\nYou cannot move outside the map!\n");
        return false;
    }

    playerPos_ = {newRow, newCol};
    return true;
}

void OverworldMap::movePlayerBack(char input) {
    int newRow = playerPos_.row;
    int newCol = playerPos_.col;

    switch(input) {
        case 'w': case 'W': ++newRow; break;  // up    : move back down
        case 's': case 'S': --newRow; break;  // down  : move back up
        case 'a': case 'A': ++newCol; break;  // left  : move back right
        case 'd': case 'D': --newCol; break;  // right : move back left
        default: return; // invalid input, do nothing
    }

    if (isInside(newRow, newCol)) {
        playerPos_ = {newRow, newCol};
    }
}




// -- encounters --

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


// -- printing --

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




// -- saving and loading game --

// searilze the map to a file
void OverworldMap::serialize(std::ofstream& file) const {
    // save dimensions
    file << rows_ << " " << cols_ << "\n";

    // save player position
    file << playerPos_.row << " " << playerPos_.col << "\n";

    // save wild positions
    file << wildPositions_.size() << "\n";
    for (auto& pos : wildPositions_) {
        file << pos.row << " " << pos.col << "\n";
    }
    // save heart positions
    file << heartPositions_.size() << "\n";
    for (auto& pos : heartPositions_) {
        file << pos.row << " " << pos.col << "\n";
    }
    // save mystery positions
    file << mysteryPositions_.size() << "\n";
    for (auto& pos : mysteryPositions_) {
        file << pos.row << " " << pos.col << "\n";
    }
}

// deserilaze the map from a file
void OverworldMap::deserialize(std::ifstream& file) {
    // load dimensions
    file >> rows_ >> cols_;

    // load player position
    file >> playerPos_.row >> playerPos_.col;

    // load wild positions
    size_t wildCount;
    file >> wildCount;
    wildPositions_.clear();
    for (size_t i = 0; i < wildCount; ++i) {
        Position pos;
        file >> pos.row >> pos.col;
        wildPositions_.insert(pos);
    }
    // load heart positions
    size_t heartCount;
    file >> heartCount;
    heartPositions_.clear();
    for (size_t i = 0; i < heartCount; ++i) {
        Position pos;
        file >> pos.row >> pos.col;
        heartPositions_.insert(pos);
    }
    // load mystery positions
    size_t mysteryCount;
    file >> mysteryCount;
    mysteryPositions_.clear();
    for (size_t i = 0; i < mysteryCount; ++i) {
        Position pos;
        file >> pos.row >> pos.col;
        mysteryPositions_.insert(pos);
    }

    file.ignore(); // consume newline at end
}