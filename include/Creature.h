#ifndef CREATURE_H
#define CREATURE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Action.h"
#include "Health.h"
#include "Type.h"

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
class Piplup : public Creature {
public:
    Piplup()
        : Creature(
            "PIPLUP",
            80,
            {10, 4, 10},
            {
                Action("Bubble",      ActionKind::Attack,  8, 95, 10, DamageType::Water),
                Action("Sleep Powder", ActionKind::Status, 0, 75, 0, DamageType::Physical, StatusEffect::Sleep, 1),
                Action("Water Pulse", ActionKind::Attack, 10, 85, 15, DamageType::Water)
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

class Pikachu : public Creature {
public:
    Pikachu()
        : Creature(
            "PIKACHU",
            110,
            {10, 5, 15},
            {
                Action("Thunderbolt",  ActionKind::Attack,  9, 95, 20, DamageType::Electric),
                Action("Quick Attack", ActionKind::Attack,  6, 100, 10, DamageType::Physical),
                Action("Iron Tail",    ActionKind::Attack, 12, 85, 15, DamageType::Physical),
                Action("Defend",       ActionKind::Defend, 0, 100, 0, DamageType::Physical),
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

class Charizard : public Creature {
public:
    Charizard()
        : Creature(
            "CHARIZARD",
            100,
            {30, 10, 5},
            {
                Action("Fire Fang",  ActionKind::Attack, 20, 70, 15, DamageType::Fire),
                Action("Slash",      ActionKind::Attack, 10, 60, 10, DamageType::Physical),
                Action("Fire Blitz", ActionKind::Attack, 60, 20, 25, DamageType::Fire),
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

class Lucario : public Creature {
public:
    Lucario()
    : Creature(
            "LUCARIO",
            120,
            {20, 10, 50},
            {
                Action("Swords Dance", ActionKind::Defend,  0, 100, 0, DamageType::Physical),
                Action("Ice Punch",    ActionKind::Attack, 20, 60, 15, DamageType::Physical),
                Action("Shadow Claw",  ActionKind::Attack, 10, 70, 20, DamageType::Physical),
                Action("Defend",       ActionKind::Defend, 0, 100, 0, DamageType::Physical),

            },
            {
                {DamageType::Physical, 2.0f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Grass,    0.5f},
                {DamageType::Electric, 0.5f},
                {DamageType::Flying,   1.0f}
            }) {}

    std::string species() const override { return "Lucario"; }
};




#endif
