#ifndef CREATURE_H
#define CREATURE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <iostream>
#include <iomanip>

#include "../battle/Action.h"
#include "../util/Health.h" 
#include "../util/Type.h"


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
        virtual std::string Roles() const { return name_; };

        virtual std::vector<std::string> asciiArt() const { return { name_ }; }
        void printAscii(const Creature& c, int offset = 0) {
            for (const auto& line : c.asciiArt()) {
                std::cout << std::setw(offset) << "" << line << "\n";
            }
        }

        const std::string& name() const { return name_; }
        void setName(const std::string& name) { name_ = name; }

        const Health& health() const { return health_; }
        Health& health() { return health_; }
        void healToFull() { health_.healToFull(); }
        void changeMaxHp(int amount) { health_.changeMax(amount); }

        bool isFainted() const { return health_.isFainted(); }
    
        const Stats& stats() const { return stats_; }
        Stats& stats() { return stats_; }

        const std::vector<Action>& actions() const { return actions_; }

        float resistanceTo(DamageType type) const {
            auto it = resistances_.find(type);
            if (it != resistances_.end()) {
                return it->second;
            }
            return 1.0f;
        }

        const std::map<DamageType, float>& resistances() const {
            return resistances_;
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



#endif

