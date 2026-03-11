#ifndef CREATURETYPE_H
#define CREATURETYPE_H

#include "Creature.h"


constexpr int HIGH_ACCURACY = 90;
constexpr int MEDIUM_ACCURACY = 65;
constexpr int LOW_ACCURACY = 20;


// custom creatures :D

// healer: lower attack and many weakness, but can heal itself
class Piplup : public Creature {
public:
    Piplup()
        : Creature(
            "PIPLUP", // name
            160, // HP
            {8, 12, 10},  // attack, defense, speed
            {                                                // power, accuracy, crit chance
                // Action("Bubble",         ActionKind::Attack,  15, MEDIUM_ACCURACY,   5         , DamageType::Water),
                Action("Healing Beam",   ActionKind::Heal,    10, LOW_ACCURACY,      0         , DamageType::Magical),
                Action("Slack Off",      ActionKind::Heal,    40, MEDIUM_ACCURACY,   0         , DamageType::Physical),
                Action("Water Pulse",    ActionKind::Attack,  20, MEDIUM_ACCURACY,   10         , DamageType::Water)
            },
            {
                // resistance
                {DamageType::Physical, 1.5f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.5f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Piplup"; }
    std::string Roles() const override { return "Healer Class: low attack and many weaknesses, but powerful healing abilities"; }

    // print ascii creature
    std::vector<std::string> asciiArt() const override {
        return {
            "   __        ",
            "-=(o '.      ",
            "   '.-.\\    ",
            "   /|  \\\\  ",
            "   '|  ||    ",
            "   _\\_):,_. "
        };
                
    }
};


// balanced: no big weakness, no extreme strength
class Pikachu : public Creature {
public:
    Pikachu()
        : Creature(
            "PIKACHU",
            150,
            {12, 8, 15},  // attack, defense, speed
            {
                Action("Thunderbolt",   ActionKind::Attack,  14, MEDIUM_ACCURACY, 20         , DamageType::Magical),
                Action("Quick Attack",  ActionKind::Attack,  10, HIGH_ACCURACY,   10         , DamageType::Physical,   StatusEffect::Paralyze, 1),
                Action("Iron Tail",     ActionKind::Attack,  12, MEDIUM_ACCURACY, 15         , DamageType::Physical,   StatusEffect::Paralyze, 1),
            },
            {
                // resistance
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Pikachu"; }
    std::string Roles() const override { return "Balanced: all rounder"; }

    // print ascii creature
    virtual std::vector<std::string> asciiArt() const override {
        return {
            " _._     _,-'""`-._         ",
            "(,-.`._,'(       |\\`-/|    ",
            "    `-.-' \\ )-`( , o o)    ",
            "         `-    \\`_`\"'-\\  "
        };
    }

};


// tank: high HP, high defense, slower, lower accuracy
class Charizard : public Creature {
public:
    Charizard()
        : Creature(
            "CHARIZARD",
            200,
            {14, 16, 6},  // attack, defense, speed
            {
                Action("Fire Fang",     ActionKind::Attack, 14, MEDIUM_ACCURACY, 10         , DamageType::Fire),
                Action("Slash",         ActionKind::Attack,  9, HIGH_ACCURACY,   10         , DamageType::Physical),
                Action("Fire Blitz",    ActionKind::Attack, 22, LOW_ACCURACY,    20         , DamageType::Fire,       StatusEffect::Burn, 1),
            },
            {
                // resistance
                {DamageType::Physical, 0.5f},
                {DamageType::Fire,     0.5f},
                {DamageType::Water,    1.0f},
                {DamageType::Magical,  1.5f}
            }) {}

    std::string species() const override { return "Charizard"; }
    std::string Roles() const override { return "Tank: High HP and Defense"; }

    // print ascii creature
    virtual std::vector<std::string> asciiArt() const override {
        return {
            " oo`'._..---.___..- ",
            "(_,-.        ,..'`  ",
            "     `'.    ;       ",
            "        : :`        ",
            "       _;_;         "
        };
    }

};


// glass cannon: huge attack, fast, but fragile
class Lucario : public Creature {
public:
    Lucario()
        : Creature(
            "LUCARIO",
            120,
            {18, 2, 4},  // attack, defense, speed
            {
                Action("Swords Dance",  ActionKind::Attack, 15, HIGH_ACCURACY,   5         , DamageType::Physical),
                Action("Ice Punch",     ActionKind::Attack, 20, LOW_ACCURACY, 15         , DamageType::Water),
                Action("Shadow Claw",   ActionKind::Attack, 22, LOW_ACCURACY, 20         , DamageType::Physical)
            },
            {
                // resistance
                {DamageType::Physical, 1.5f},
                {DamageType::Fire,     1.5f},
                {DamageType::Water,    1.5f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Lucario"; }
    std::string Roles() const override { return "Glass Cannon: High Attack, but Low HP"; }

    // print ascii creature
    virtual std::vector<std::string> asciiArt() const override {
        return {
            "            /)-_-(\\  ",
            "             (o o)    ",
            "     .-----__/\\o/    ",
            "    /  __      /      ",
            "\\__/\\ /  \\_\\ |/   ",
            "     \\     ||        ",
            "     //     ||        ",
            "     |\\     |\\      "
        };
    }
};



// wizard: weaker direct damage, annoying status utility
class Gengar : public Creature {
public:
    Gengar()
        : Creature(
            "GENGAR",
            150,
            {15, 5, 14},  // attack, defense, speed
            {
                Action("Dark Pulse",    ActionKind::Attack, 12, MEDIUM_ACCURACY, 10         , DamageType::Magical),
                Action("Hypnosis",      ActionKind::Status,  0, MEDIUM_ACCURACY,  0         , DamageType::Magical,   StatusEffect::Paralyze, 2),
                Action("Curse",         ActionKind::Status,  0, MEDIUM_ACCURACY,  0         , DamageType::Magical,   StatusEffect::Poison, 3),
            },
            {
                // resistance
                {DamageType::Physical, 1.5f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Magical,  1.5f}
            }) {}

    std::string species() const override { return "Gengar"; }
    std::string Roles() const override { return "Wizard: High utility with status effects, but lower direct damage"; }
    
    // print ascii creature
    std::vector<std::string> asciiArt() const override {
        return {
            "               ,             ",
            "             .--')           ",
            "            /    /           ",
            "           |    /            ",
            "        /`.\\   (_.'\\       ",
            "        \\          /        ",
            "         '--. .---'          ",
            "           ( \" )            ",
            "            '-'              "
        };
    }
};


#endif
