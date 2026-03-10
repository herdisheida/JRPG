#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random {
    // random number generator
    inline std::mt19937& rng() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    // roll a percentage chance, returns true if the roll is successful
    inline bool rollPercent(int chance) {
        std::uniform_int_distribution<int> dist(1, 100);
        return dist(rng()) <= chance;
    }

}

#endif