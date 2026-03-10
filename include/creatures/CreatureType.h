#ifndef CREATURETYPE_H
#define CREATURETYPE_H

#include "Creature.h"


constexpr int HIGH_ACCURACY = 95;
constexpr int MEDIUM_ACCURACY = 85;
constexpr int LOW_ACCURACY = 70;


// custom creatures :D

// healer: lower attack and many weakness, but can heal itself
class Piplup : public Creature {
public:
    Piplup()
        : Creature(
            "PIPLUP",
            110, // HP
            {8, 12, 10},  // attack, defense, speed
            {                                                // power, accuracy, crit chance
                Action("Bubble",         ActionKind::Attack,  7, MEDIUM_ACCURACY,   5         , DamageType::Water),
                Action("Healing Beam",   ActionKind::Heal,   10, LOW_ACCURACY,      0         , DamageType::Magical),
                Action("Slack Off",      ActionKind::Heal,   40, MEDIUM_ACCURACY,   0         , DamageType::Physical),
                Action("Water Pulse",    ActionKind::Attack, 20, LOW_ACCURACY,     10         , DamageType::Water)
            },
            {
                {DamageType::Physical, 1.5f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.5f},
                // {DamageType::Grass,    1.5f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Piplup"; }

    // print ascii creature
    virtual void printAscii() override {
        std::cout << "         __          " << "\n";
        std::cout << "      -=(o '.        " << "\n";
        std::cout << "         '.-.\\      " << "\n";
        std::cout << "         /|  \\\\    " << "\n";
        std::cout << "         '|  ||      " <<  "\n";
        std::cout << "         _\\_):,_.   " << "\n";
                
    }
};


// balanced: no big weakness, no extreme strength
class Pikachu : public Creature {
public:
    Pikachu()
        : Creature(
            "PIKACHU",
            100,
            {12, 8, 15},  // attack, defense, speed
            {
                Action("Thunderbolt",   ActionKind::Attack, 14, MEDIUM_ACCURACY, 20         , DamageType::Magical),
                Action("Quick Attack",  ActionKind::Attack,  9, HIGH_ACCURACY,   10         , DamageType::Physical),
                Action("Iron Tail",     ActionKind::Attack, 12, MEDIUM_ACCURACY, 15         , DamageType::Physical),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0         , DamageType::Physical)
            },
            {
                // resistance
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                // {DamageType::Grass,    1.0f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Pikachu"; }

    // print ascii creature
    virtual void printAscii() override {
        std::cout << "       _._     _,-'""`-._           " << "\n";
        std::cout << "      (,-.`._,'(       |\\`-/|      " << "\n";
        std::cout << "          `-.-' \\ )-`( , o o)      " << "\n";
        std::cout << "                `-    \\`_`\"'-\\   " << "\n";
    }
};


// tank: high HP, high defense, slower, lower accuracy
class Charizard : public Creature {
public:
    Charizard()
        : Creature(
            "CHARIZARD",
            160,
            {14, 16, 6},  // attack, defense, speed
            {
                Action("Fire Fang",     ActionKind::Attack, 14, MEDIUM_ACCURACY, 10         , DamageType::Fire),
                Action("Slash",         ActionKind::Attack,  9, HIGH_ACCURACY,   10         , DamageType::Physical),
                Action("Fire Blitz",    ActionKind::Attack, 22, LOW_ACCURACY,    20         , DamageType::Fire),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0         , DamageType::Physical)
            },
            {
                // resistance
                {DamageType::Physical, 0.5f},
                {DamageType::Fire,     0.5f},
                {DamageType::Water,    1.0f},
                // {DamageType::Grass,    0.5f},
                {DamageType::Magical,  1.5f}
            }) {}

    std::string species() const override { return "Charizard"; }

    // print ascii creature
    virtual void printAscii() override {
        std::cout << "       oo`'._..---.___..-   " << "\n";
        std::cout << "      (_,-.        ,..'`    " << "\n";
        std::cout << "           `'.    ;         " << "\n";
        std::cout << "              : :`          " << "\n";
        std::cout << "             _;_;           " << "\n";
    }
};


// glass cannon: huge attack, fast, but fragile
class Lucario : public Creature {
public:
    Lucario()
        : Creature(
            "LUCARIO",
            100,
            {30, 4, 40},  // attack, defense, speed
            {
                Action("Swords Dance",  ActionKind::Attack, 12, HIGH_ACCURACY,   5         , DamageType::Physical),
                Action("Ice Punch",     ActionKind::Attack, 18, MEDIUM_ACCURACY, 15         , DamageType::Water),
                Action("Shadow Claw",   ActionKind::Attack, 22, MEDIUM_ACCURACY, 20         , DamageType::Physical)
            },
            {
                // resistance
                {DamageType::Physical, 1.5f},
                {DamageType::Fire,     1.5f},
                {DamageType::Water,    1.5f},
                // {DamageType::Grass,    1.5f},
                {DamageType::Magical,  1.0f}
            }) {}

    std::string species() const override { return "Lucario"; }

    // print ascii creature
    virtual void printAscii() override {
        std::cout << "                  /)-_-(\\  " << "\n";
        std::cout << "                   (o o)    " << "\n";
        std::cout << "           .-----__/\\o/    " << "\n";
        std::cout << "          /  __      /      " << "\n";
        std::cout << "      \\__/\\ /  \\_\\ |/   " << "\n";
        std::cout << "           \\     ||        " << "\n";
        std::cout << "           //     ||        " << "\n";
        std::cout << "           |\\     |\\      " << "\n";
    }
};



// wizard: weaker direct damage, annoying status utility
class Gengar : public Creature {
public:
    Gengar()
        : Creature(
            "GENGAR",
            100,
            {15, 5, 14},  // attack, defense, speed
            {
                Action("Dark Pulse",    ActionKind::Attack, 10, MEDIUM_ACCURACY, 10         , DamageType::Magical),
                Action("Hypnosis",      ActionKind::Status,  0, MEDIUM_ACCURACY,  0         , DamageType::Magical, StatusEffect::Paralyzed, 1),
                Action("Curse",         ActionKind::Status,  0, MEDIUM_ACCURACY,  0         , DamageType::Magical, StatusEffect::Poison, 3),
                Action("Defend",        ActionKind::Defend,  0, HIGH_ACCURACY,    0         , DamageType::Physical)
            },
            {
                // resistance
                {DamageType::Physical, 1.2f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                // {DamageType::Grass,    0.5f},
                // {DamageType::Electric, 1.0f},
                {DamageType::Magical,   1.2f}
            }) {}

    std::string species() const override { return "Gengar"; }

    // print ascii creature
    virtual void printAscii() override {
        std::cout << "               ,             " << "\n";
        std::cout << "             .--')           " << "\n";
        std::cout << "            /    /           " << "\n";
        std::cout << "           |    /            " << "\n";
        std::cout << "        /`.\\   (_.'\\       " << "\n";
        std::cout << "        \\          /        " << "\n";
        std::cout << "         '--. .---'          " << "\n";
        std::cout << "           ( \" )            " << "\n";
        std::cout << "            '-'              " << "\n";
    }
};


#endif
