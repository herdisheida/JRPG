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
        std::set<Position> wildPositions_;    // enemy encounter pos
        std::set<Position> heartPositions_;   // healing item pos
        std::set<Position> mysteryPositions_;
        std::mt19937 rng_;

    public:
        OverworldMap(int rows, int cols);

        void initialize(int wildCount, int heartCount, int mysteryCount);
        void print() const;
        void printInstructions() const;

        Position getPlayerPos() const { return playerPos_; }
        void movePlayerBack(char input); // to previous position -> move player opposite direction of input

        // movement and encounter funcs
        bool movePlayer(char input);
        bool hasEncounter() const;
        void clearEncounter();

        // heart funcs
        bool hasHeart() const;
        void clearHeart();

        // mystery funcs
        bool hasMystery() const;
        void clearMystery();
        bool hasMysteriesLeft() const;
    
        // win or lose conditions
        bool hasWildsLeft() const;  // win condition: defeat all wild creatures
        bool hasHeartsLeft() const; // lose condition: run out of healing items and faint in battle

    private:
        bool isInside(int row, int col) const;


};

#endif