#ifndef ATTACK_H
#define ATTACK_H

#include <string>

struct Attack {
    std::string name;
    int power;    // base damage
    int accuracy; // does it hit? 0-100

    Attack(const std::string& n = "Tackle", int p = 5, int a = 100)
        : name(n), power(p), accuracy(a) {}
};

#endif