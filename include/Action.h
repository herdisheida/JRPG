#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "Type.h"

enum class ActionKind {
    Attack,
    Heal,
    Defend,
    Flee
};

struct Action {
    std::string name;
    ActionKind kind;
    int power;          // attack damage or heal amount
    int accuracy;       // 0-100
    int critChance;     // 0-100, only relevant for attacks
    DamageType damageType;

    // default is a basic attack
    Action(const std::string& n = "Tackle",
           ActionKind k = ActionKind::Attack,
           int p = 5,
           int a = 100,
           int c = 5,
           DamageType dt = DamageType::Physical)
        : name(n),
          kind(k),
          power(p),
          accuracy(a),
          critChance(c),
          damageType(dt) {}
};

inline std::string actionKindToString(ActionKind kind) {
    switch (kind) {
        case ActionKind::Attack: return "Attack";
        case ActionKind::Heal:   return "Heal";
        case ActionKind::Defend: return "Defend";
        case ActionKind::Flee:   return "Flee";
        default:                 return "Unknown";
    }
}

#endif