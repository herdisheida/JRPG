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

    // roll a random integer in the range [min, max]
    inline int range(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng());
    }

}

#endif