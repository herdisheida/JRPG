#ifndef CREATURE_H
#define CREATURE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Action.h"
#include "Health.h"
#include "Type.h"


constexpr int HIGH_ACCURACY = 95;
constexpr int MEDIUM_ACCURACY = 85;
constexpr int LOW_ACCURACY = 70;

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
        std::vector<Action> actions_;
        std::map<DamageType, float> resistances_;
        bool defending_;

        StatusEffect status_;
        int statusTurns_;

    public:
        Creature(const std::string& name,
                int maxHp,
                Stats stats,
                std::vector<Action> actions,
                std::map<DamageType, float> resistances)
            : name_(name),
            health_(maxHp),
            stats_(stats),
            actions_(std::move(actions)),
            resistances_(std::move(resistances)),
            defending_(false),
            status_(StatusEffect::None),
            statusTurns_(0) {}

        virtual ~Creature() = default;
        virtual std::string species() const = 0;

        const std::string& name() const { return name_; }
        const Health& health() const { return health_; }
        Health& health() { return health_; }

        const Stats& stats() const { return stats_; }
        const std::vector<Action>& actions() const { return actions_; }

        bool isFainted() const { return health_.isFainted(); }

        float resistanceTo(DamageType type) const {
            auto it = resistances_.find(type);
            if (it != resistances_.end()) {
                return it->second;
            }
            return 1.0f;
        }

        bool isDefending() const { return defending_; }
        void setDefending(bool value) { defending_ = value; }


        // status helpers
        StatusEffect status() const { return status_; }
        int statusTurns() const { return statusTurns_; }

        bool hasStatus() const { return status_ != StatusEffect::None; }

        void setStatus(StatusEffect status, int turns) {
            status_ = status;
            statusTurns_ = turns;
        }

        void clearStatus() {
            status_ = StatusEffect::None;
            statusTurns_ = 0;
        }

        void reduceStatusTurns() {
            if (statusTurns_ > 0) {
                --statusTurns_;
            }
            if (statusTurns_ <= 0) {
                clearStatus();
            }
        }
};


// custom creatures :D

// healer: lower attack, but can heal itself
class Piplup : public Creature {
public:
    Piplup()
        : Creature(
            "PIPLUP",
            105,
            {8, 8, 10},  // attack, defense, speed
            {
                Action("Bubble",        ActionKind::Attack, 7, HIGH_ACCURACY,   5, DamageType::Water),
                Action("Healing Beam",  ActionKind::Heal,  20, HIGH_ACCURACY,   0, DamageType::Physical),
                Action("Water Pulse",   ActionKind::Attack, 10, MEDIUM_ACCURACY, 10, DamageType::Water)
            },
            {
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     0.5f},
                {DamageType::Water,    0.5f},
                {DamageType::Grass,    1.5f},
                {DamageType::Electric, 1.5f},
                {DamageType::Flying,   1.0f}
            }) {}

    std::string species() const override { return "Piplup"; }
};


// balanced: no big weakness, no extreme strength
class Pikachu : public Creature {
public:
    Pikachu()
        : Creature(
            "PIKACHU",
            100,
            {12, 8, 15},  // attack, defense, speed
            {
                Action("Thunderbolt",   ActionKind::Attack, 14, MEDIUM_ACCURACY, 20, DamageType::Electric),
                Action("Quick Attack",  ActionKind::Attack,  9, HIGH_ACCURACY,   10, DamageType::Physical),
                Action("Iron Tail",     ActionKind::Attack, 12, MEDIUM_ACCURACY, 15, DamageType::Physical),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0, DamageType::Physical)
            },
            {
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Grass,    1.0f},
                {DamageType::Electric, 0.5f},
                {DamageType::Flying,   1.0f}
            }) {}

    std::string species() const override { return "Pikachu"; }
};


// tank: high HP, high defense, slower, lower accuracy
class Charizard : public Creature {
public:
    Charizard()
        : Creature(
            "CHARIZARD",
            160,
            {14, 16, 6},  // attack, defense, speed
            {
                Action("Fire Fang",     ActionKind::Attack, 14, MEDIUM_ACCURACY, 10, DamageType::Fire),
                Action("Slash",         ActionKind::Attack,  9, HIGH_ACCURACY,   10, DamageType::Physical),
                Action("Fire Blitz",    ActionKind::Attack, 22, LOW_ACCURACY,    20, DamageType::Fire),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0, DamageType::Physical)
            },
            {
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     0.5f},
                {DamageType::Water,    1.5f},
                {DamageType::Grass,    0.5f},
                {DamageType::Electric, 1.0f},
                {DamageType::Flying,   0.5f}
            }) {}

    std::string species() const override { return "Charizard"; }
};


// glass cannon: huge attack, fast, but fragile
class Lucario : public Creature {
public:
    Lucario()
        : Creature(
            "LUCARIO",
            75,
            {22, 4, 40},  // attack, defense, speed
            {
                Action("Swords Dance",  ActionKind::Attack, 12, HIGH_ACCURACY,   5, DamageType::Physical),
                Action("Ice Punch",     ActionKind::Attack, 18, MEDIUM_ACCURACY, 15, DamageType::Physical),
                Action("Shadow Claw",   ActionKind::Attack, 22, MEDIUM_ACCURACY, 20, DamageType::Physical)
            },
            {
                {DamageType::Physical, 1.3f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Grass,    0.5f},
                {DamageType::Electric, 0.5f},
                {DamageType::Flying,   1.2f}
            }) {}

    std::string species() const override { return "Lucario"; }
};



// wizard: weaker direct damage, annoying status utility
class Gengar : public Creature {
public:
    Gengar()
        : Creature(
            "GENGAR",
            85,
            {10, 5, 14},  // attack, defense, speed
            {
                Action("Dark Pulse",    ActionKind::Attack, 10, MEDIUM_ACCURACY, 10, DamageType::Physical),
                Action("Hypnosis",      ActionKind::Status,  0, MEDIUM_ACCURACY,  0, DamageType::Physical, StatusEffect::Paralyzed, 1),
                Action("Curse",         ActionKind::Status,  0, MEDIUM_ACCURACY,  0, DamageType::Physical, StatusEffect::Poison, 3),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0, DamageType::Physical)
            },
            {
                {DamageType::Physical, 1.2f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Grass,    0.5f},
                {DamageType::Electric, 1.0f},
                {DamageType::Flying,   1.2f}
            }) {}

    std::string species() const override { return "Gengar"; }
};

#endif
