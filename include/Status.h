#ifndef STATUS_H
#define STATUS_H

#include <string>

enum class StatusEffect {
    None,
    Paralyzed,   // Prevents action for a few turns
    Poison,      // Deals damage at the end of each turn

    // future status ideas:
    Burn,        // Deals damage at the end of each turn and lowers attack
    Freeze,      // Prevents action until thawed

};

inline std::string statusToString(StatusEffect status) {
    switch (status) {
        case StatusEffect::None:       return "";
        case StatusEffect::Paralyzed:  return "Paralyzed";
        case StatusEffect::Poison:     return "Poisoned";
        case StatusEffect::Burn:       return "Burned";
        case StatusEffect::Freeze:     return "Frozen";
        default:                       return "Unknown";
    }
}

#endif