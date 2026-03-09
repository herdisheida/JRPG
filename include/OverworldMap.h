#ifndef OVERWORLDMAP_H
#define OVERWORLDMAP_H

#include <set>
#include <utility>
#include <random>
#include <iostream>

struct Position {
    int row;
    int col;

    bool operator<(const Position& other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

class OverworldMap {
    private:
        int rows_;
        int cols_;
        Position playerPos_;
        std::set<Position> wildPositions_;
        std::mt19937 rng_;

    public:
        OverworldMap(int rows, int cols);

        void initialize(int wildCount);
        void print() const;

        bool movePlayer(char input);
        bool hasEncounter() const;
        void clearEncounter();

    private:
        bool isInside(int row, int col) const;
};

#endif