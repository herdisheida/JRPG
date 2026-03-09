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


// custom creatures :D
class Charizard : public Creature {
public:
    Charizard()
        : Creature(
              "CHARIZARD",
              100,
              {20, 10, 2},
              {
                  Move("Fire Fang", 20, 70),
                  Move("Slash", 10, 60),
                  Move("Fire Blitz", 60, 20)
              }) {}

    std::string species() const override { return "Charizard"; }
};


class Piplup : public Creature {
    public:
        Piplup()
            : Creature(
                "PIPLUP",
                80,
                {10, 4, 10},
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
                110,
                {10, 5, 15},
                {
                    Move("Thunderbolt", 9, 95),
                    Move("Quick Attack", 6, 100),
                    Move("Iron Tail", 12, 85)
                }) {}

        std::string species() const override { return "Pikachu"; }
};

class Lucario : public Creature {
public:
    Lucario()
        : Creature(
              "LUCARIO",
              120,
              {20, 10, 50},
              {
                  Move("Swords Dance", 30, 80),
                  Move("Ice Punch", 20, 60),
                  Move("Shadow Claw", 10, 70)
              }) {}

    std::string species() const override { return "Lucario"; }
};


#endif