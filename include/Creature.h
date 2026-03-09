#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "Health.h"
#include "Attack.h"

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
        std::vector<Attack> attacks_;

    public:
        Creature(const std::string& name, int maxHp, Stats stats, std::vector<Attack> attacks)
            : name_(name), health_(maxHp), stats_(stats), attacks_(std::move(attacks)) {}

        virtual ~Creature() = default;

        virtual std::string species() const = 0;

        const std::string& name() const { return name_; }
        const Health& health() const { return health_; }
        Health& health() { return health_; }
        const Stats& stats() const { return stats_; }
        const std::vector<Attack>& moves() const { return attacks_; }

        bool isFainted() const { return health_.isFainted(); }
};

class Piplup : public Creature {
    public:
        Piplup()
            : Creature(
                "PIPLUP",
                28,
                {9, 4, 8},
                {
                    Attack("Bubble", 8, 95),
                    Attack("Tacklee", 6, 100),
                    Attack("Water Pulse", 10, 85)
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
                    Attack("Thunderbolt", 9, 95),
                    Attack("Quick Attack", 6, 100),
                    Attack("Iron Tail", 12, 85)
                }) {}

        std::string species() const override { return "Pikachu"; }
};


#endif