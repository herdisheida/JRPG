#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class DamageType {
    Fire,
    Water,
    Grass,

    // Electric,
    Magical,
    Physical
};

inline std::string toString(DamageType type) {
    switch (type) {
        case DamageType::Fire:     return "Fire";
        case DamageType::Water:    return "Water";
        case DamageType::Grass:    return "Grass";

        // case DamageType::Electric: return "Electric";
        case DamageType::Magical:   return "Magical";
        case DamageType::Physical: return "Physical";

        default:                   return "Unknown";
    }
}

#endif