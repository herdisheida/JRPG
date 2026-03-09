#include "../include/OverworldMap.h"

OverworldMap::OverworldMap(int rows, int cols)
    : rows_(rows),
      cols_(cols),
      playerPos_{0, 0},
      rng_(std::random_device{}()) {}

void OverworldMap::initialize(int wildCount) {
    playerPos_ = {0, 0};
    wildPositions_.clear();

    std::uniform_int_distribution<int> rowDist(0, rows_ - 1);
    std::uniform_int_distribution<int> colDist(0, cols_ - 1);

    while (static_cast<int>(wildPositions_.size()) < wildCount) {
        Position p{rowDist(rng_), colDist(rng_)};

        if (!(p == playerPos_)) {
            wildPositions_.insert(p);
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
            std::cout << "Invalid input. Use W A S D.\n";
            return false;
    }

    if (!isInside(newRow, newCol)) {
        std::cout << "You cannot move outside the map!\n";
        return false;
    }

    playerPos_ = {newRow, newCol};
    return true;
}

bool OverworldMap::hasEncounter() const {
    return wildPositions_.count(playerPos_) > 0;
}

void OverworldMap::clearEncounter() {
    wildPositions_.erase(playerPos_);
}

void OverworldMap::print() const {
    std::cout << "\n======== OVERWORLD MAP =======\n";
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            Position current{r, c};

            if (current == playerPos_) {
                std::cout << "P ";
            } else if (wildPositions_.count(current) > 0) {
                std::cout << "W ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "symbols: P = Player, W = Wild Creature, . = Empty\n";
}