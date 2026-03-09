#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Move {
    std::string name;
    int power;
    int accuracy; // 0-100

    Move(const std::string& n = "Tackle", int p = 5, int a = 100)
        : name(n), power(p), accuracy(a) {}
};

#endif