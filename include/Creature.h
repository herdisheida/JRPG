#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "Health.h"
#include "Move.h"

struct Stats {
    int attack;
    int defense;
    int speed;
};

class Creature {
protected:
    std::string name_;
    Health health_;
    Stats stats_;
    std::vector<Move> moves_;

public:
    Creature(const std::string& name, int maxHp, Stats stats, std::vector<Move> moves)
        : name_(name), health_(maxHp), stats_(stats), moves_(std::move(moves)) {}

    virtual ~Creature() = default;

    virtual std::string species() const = 0;

    const std::string& name() const { return name_; }
    const Health& health() const { return health_; }
    Health& health() { return health_; }
    const Stats& stats() const { return stats_; }
    const std::vector<Move>& moves() const { return moves_; }

    bool isFainted() const { return health_.isFainted(); }
};

class Sparkit : public Creature {
public:
    Sparkit()
        : Creature(
              "SPARKIT",
              28,
              {9, 4, 8},
              {
                  Move("Static Zap", 8, 95),
                  Move("Quick Scratch", 6, 100),
                  Move("Thunder Bite", 10, 85)
              }) {}

    std::string species() const override { return "Sparkit"; }
};


class Piplup : public Creature {
    public:
        Piplup()
            : Creature(
                "PIPLUP",
                28,
                {9, 4, 8},
                {
                    Move("Bubble", 8, 95),
                    Move("Tacklee", 6, 100),
                    Move("Water Pulse", 10, 85)
                }) {}

        std::string species() const override { return "Piplup"; }
};


class Pikachu : public Creature {
    public:
        Pikachu()
            : Creature(
                "PIKACHU",
                35,
                {10, 5, 9},
                {
                    Move("Thunderbolt", 9, 95),
                    Move("Quick Attack", 6, 100),
                    Move("Iron Tail", 12, 85)
                }) {}

        std::string species() const override { return "Pikachu"; }
};


#endif