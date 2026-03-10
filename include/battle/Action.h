#ifndef ACTION_H
#define ACTION_H

#include <string>

#include "../util/Type.h"
#include "../util/Status.h"


enum class ActionKind {
    Attack,
    Heal,
    Defend,
    Flee,
    Status
};

struct Action {
    std::string name;
    ActionKind kind;

    int power;          // attack damage or heal amount
    int accuracy;       // 0-100
    int critChance;     // 0-100, only relevant for attacks
    DamageType damageType;

    StatusEffect statusEffect;
    int statusDuration;

    // default is a basic attack
    Action(const std::string& n = "Strike",
           ActionKind k = ActionKind::Attack,
           int p = 5,
           int a = 100,
           int c = 5,
           DamageType dt = DamageType::Physical,
           StatusEffect se = StatusEffect::None,
           int sd = 0)
        : name(n),
          kind(k),
          power(p),
          accuracy(a),
          critChance(c),
          damageType(dt),
          statusEffect(se),
          statusDuration(sd) {}
};

inline std::string actionKindToString(ActionKind kind) {
    switch (kind) {
        case ActionKind::Attack: return "Attack";
        case ActionKind::Heal:   return "Heal";
        case ActionKind::Defend: return "Defend";
        case ActionKind::Flee:   return "Flee";
        case ActionKind::Status: return "Status";
        default:                 return "Unknown";
    }
}

#endif