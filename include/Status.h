#ifndef STATUS_H
#define STATUS_H

#include <string>

enum class StatusEffect {
    None,
    Paralyzed,   // Prevents action for a few turns
    Poison,  // Deals damage at the end of each turn
};

inline std::string statusToString(StatusEffect status) {
    switch (status) {
        case StatusEffect::None:   return "None";
        case StatusEffect::Paralyzed:  return "Paralyzed";
        case StatusEffect::Poison: return "Poisoned";
        default:                   return "Unknown";
    }
}

#endif