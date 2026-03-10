#ifndef STATUS_H
#define STATUS_H

#include <string>

enum class StatusEffect {
    None,
    Paralyze,   // Prevents action for a few turns
    Poison,      // Deals damage at the end of each turn

    // future status ideas:
    Burn,        // Deals damage at the end of each turn and lowers attack
    Freeze,      // Prevents action until thawed

};


inline std::string statusToString(StatusEffect status) {
    switch (status) {
        case StatusEffect::None:       return "";
        case StatusEffect::Paralyze:  return  "Paralyzed";
        case StatusEffect::Poison:     return "Poisoned";
        case StatusEffect::Burn:       return "Burned";
        case StatusEffect::Freeze:     return "Frozen";
        default:                       return "Unknown";
    }
}

inline std::string takeDamageString(StatusEffect status) {
    switch (status) {
        case StatusEffect::None:       return "";
        case StatusEffect::Poison:     return "poison damage";
        case StatusEffect::Burn:       return "burn damage";
        case StatusEffect::Freeze:     return "freeze damage";
        default:                       return "unknown damage";
    }
}

#endif