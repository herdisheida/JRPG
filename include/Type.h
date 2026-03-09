#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class DamageType {
    Fire,
    Water,
    Grass,

    Electric,
    Physical,
    Flying,
};

inline std::string toString(DamageType type) {
    switch (type) {
        case DamageType::Fire:     return "Fire";
        case DamageType::Water:    return "Water";
        case DamageType::Grass:    return "Grass";

        case DamageType::Electric: return "Electric";
        case DamageType::Physical: return "Physical";
        case DamageType::Flying:   return "Flying";
        
        default:                   return "Unknown";
    }
}

#endif