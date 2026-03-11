#ifndef CREATURETYPE_H
#define CREATURETYPE_H

#include "Creature.h"


constexpr int HIGH_ACCURACY = 90;
constexpr int MEDIUM_ACCURACY = 65;
constexpr int LOW_ACCURACY = 15;


// custom creatures :D -- TODO reyna balance-a the compettion - þannig einn vinnur eki altaf



// piplup - HEALER
class Piplup : public Creature {
public:
    Piplup()
        : Creature(
            "PIPLUP", // name
            180,         // high HP
            {6, 14, 8},  // very low attack, very high defense, medium speed

            {                                                // power, accuracy, crit chance
                Action("Healing Beam",   ActionKind::Heal,    35, HIGH_ACCURACY,      0         , DamageType::Magical),
                Action("Slack Off",      ActionKind::Heal,    60, MEDIUM_ACCURACY,    0         , DamageType::Physical),
                Action("Water Pulse",    ActionKind::Attack,   8, HIGH_ACCURACY,     10         , DamageType::Water)
            },
            {
                // weak to burst damage types
                {DamageType::Physical, 2.0f},  // 2x damage from (glass cannon counter)
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    0.5f},  // resist water
                {DamageType::Magical,  1.5f}   // 1.5x extra
            }) {}

    std::string species() const override { return "Piplup"; }
    std::string Roles() const override { return "Healer: Can outlast almost anyone, but weak to burst damage"; }

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



// Pikachu - BALANCED
class Pikachu : public Creature {
public:
    Pikachu()
        : Creature(
            "PIKACHU",
            140,  // avg HP
            {12, 10, 18},  // good attack, avg defense, verry fast
            {
                // okey damage but no huge bursts
                Action("Thunderbolt",   ActionKind::Attack,  16, HIGH_ACCURACY,   15         , DamageType::Magical),
                Action("Quick Attack",  ActionKind::Attack,  12, HIGH_ACCURACY,   10         , DamageType::Physical),
                Action("Iron Tail",     ActionKind::Attack,  14, MEDIUM_ACCURACY, 12         , DamageType::Physical),
            },
            {
                // zero extreme weaknesses
                {DamageType::Physical, 1.0f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Magical,  1.2f}  // Slightly weak to magic
            }) {}

    std::string species() const override { return "Pikachu"; }
    std::string Roles() const override { return "Balanced: Jack of all trades, master of none"; }

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


// Charizard - TANK
class Charizard : public Creature {
public:
    Charizard()
        : Creature(
            "CHARIZARD",
            220,          // Massive HP
            {16, 20, 5},  // High attack, MASSIVE defense, very slow
            {
                // POWER but inaccurate
                Action("Fire Fang",     ActionKind::Attack, 18, MEDIUM_ACCURACY, 10         , DamageType::Fire),
                Action("Slash",         ActionKind::Attack, 14, HIGH_ACCURACY,   10         , DamageType::Physical),
                Action("Fire Blitz",    ActionKind::Attack, 35, LOW_ACCURACY,    20         , DamageType::Fire),
            },
            {
                // exremeely resistant to physical, very weak to magic
                {DamageType::Physical, 0.3f},
                {DamageType::Fire,     0.5f},
                {DamageType::Water,    2.0f},
                {DamageType::Magical,  2.5f}  // extremely weak
            }) {}

    std::string species() const override { return "Charizard"; }
    std::string Roles() const override { return "Tank: Physical attacks barely scratch it but magic destroys it"; }

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



// Lucario - GLASS CANNON
class Lucario : public Creature {
public:
    Lucario()
        : Creature(
            "LUCARIO",
            90,          // v low HP
            {28, 4, 16},  // INSANE attack, v-thin defense, very fast
            {
                Action("Swords Dance",  ActionKind::Attack, 15, LOW_ACCURACY,     5       , DamageType::Physical),
                Action("Ice Punch",     ActionKind::Attack, 20, MEDIUM_ACCURACY,  15      , DamageType::Physical),
                Action("Shadow Claw",   ActionKind::Attack, 22, HIGH_ACCURACY,    20      , DamageType::Physical)
            },
            {
                // massive damage from everything
                {DamageType::Physical, 1.8f},
                {DamageType::Fire,     1.5f},
                {DamageType::Water,    1.5f},
                {DamageType::Magical,  2.0f} // magic obliterates it
            }) {}

    std::string species() const override { return "Lucario"; }
    std::string Roles() const override { return "Glass Cannon: Hits like a truck, dies like a fly"; }

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



// Gengar - WIZARD
class Gengar : public Creature {
public:
    Gengar()
        : Creature(
            "GENGAR",
            110,  // Low HP
            {20, 6, 20},  // high magic attack, low defense, VERY fast
            {
                // status effect + magic dmg
                Action("Shadow Ball",  ActionKind::Attack,  22,  HIGH_ACCURACY,     15,    DamageType::Magical),
                Action("Hypnosis",     ActionKind::Status,   0,  MEDIUM_ACCURACY,    0,    DamageType::Magical,    StatusEffect::Paralyze, 3),
                Action("Toxic",        ActionKind::Status,   0,  HIGH_ACCURACY,      0,    DamageType::Magical,    StatusEffect::Poison,   5),
                Action("Hex",          ActionKind::Attack,  30,  MEDIUM_ACCURACY,   10,    DamageType::Magical)
            },
            {
                // resists magic, weak to physical
                {DamageType::Physical, 1.8f},
                {DamageType::Fire,     1.0f},
                {DamageType::Water,    1.0f},
                {DamageType::Magical,  0.5f}
            }) {}

    std::string species() const override { return "Gengar"; }
    std::string Roles() const override { return "Wizard: Magic Damage and status effects"; }
    
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
