# JRPG

---

DELETE LATER

---

TODO: programming requirements

- You must use at least one of the following: inheritance, templates, variants. Failure to do so will result in a 0.
- MAkefile

## How to compile and run

1. Compile:

```
make
```

2. Run:
   _(for better experience -> large terminal window for ascii art and text)_

```
./run
```

3. Clean build files:

```
make clean
```

## User guide for Players // TODO

### Introduction

In this game you control a creature and fight against enemy creatures.
The battles are turn-based, so each side takes turns performing actions.
The goal of the game is to defeat all the enemies on the map!

At the start of the game you choose a difficulty level.

| lvl    |
| ------ |
| Easy   |
| Medium |
| Hard   |

### Overworld

The game has a small overworld map.

The map shows:

| Symbol         | Meaning               | Effect when encountering             |
| -------------- | --------------------- | ------------------------------------ |
| P              | Player                |                                      |
| w              | Wild Creature (enemy) | A battle starts (player vs enemy)    |
| ♥ : (`\u2665`) | Healing locations     | Heal Player                          |
| ?              | Mystery locations     | Mystery Effect                       |
| .              | Path                  | Player can move on these (no effect) |

### Battle System

When you encounter an enemy creature, a battle starts.

During battle:

- The name and ASCII art of the enemy creature are shown
- Both creatures take turns performing actions (attacks, heal, etc.)
- The creature with the higher Speed goes first
- The battle continues until one creature’s health reaches 0 or the player flees
- After the battle, you return to the overworld map (if the wild lives -> you can encounter it again)

### Creature Stats

Each creature has the following stats:

- **Health**: how much damage they can take before fainting (hp = 0)
- **Attack**: increases damage dealt (critical hit chance)
- **Defense**: reduces incoming damage
- **Speed**: decides who moves first in a turn
- **Action**: list of moves the creature can use (attack, heal, etc)
- **Resistances**: how much damage it takes from certain Damage Types (effective, normal, resistant)

### Action Types

Creatures can perform different types of actions during battle:

- **Attack**: deals damage to the opponent
- **Special**: a attack with a special effect, such as inflicting a status condition (e.g. burn, freeze, paralysis)
- **Heal**: restores the user's health
- **Defend**: reduces the damage of the next incoming attack
- **Flee**: attempts to escape the battle

### Damage Types

Attack (actions) can have different damage types, for example:

- Fire
- Water
- Physical
- Magical

Creatures can have resistances to these types or be weak to them, which affects the damage they take.

### Damage Calculation

Damage depends on several things:

1.  Attacker's **Attack stats**
2.  **Action Power scale**
3.  Defender's **Defense stats**
4.  Damage type **resistance**
5.  Enemies **Defence stats** or **Defend Action**
6.  Critical hits
7.  A small random variation

This makes battles less predictable and more interesting

## For Programmers (Code Structure) // TODO

The program uses **inheritance** to create different types of creatures and controllers.

File structure:

- `main.cpp`: entry point of the program; sets up the game and starts the battle loop

- `src/`: implementation files:
  - `Battle.cpp`: battle system loop
  - `CreatureSelection.cpp`: user creature selection screen
  - `Encounters.cpp`: map interactions
  - `EnemyField.cpp`: stores enemies on map if player re-encounters them
  - `GameEnd.cpp`: handles win/lose conditions
  - `GameSettings.cpp`:
  - `Helpers.cpp`: helper functions for `main.cpp`
  - `Input.cpp`: handles player input
  - `Overworld.cpp`: the overworld map (movement, encounters, etc)

- `include/`: header files:
  - `controllers/`: controller classes:
    - `Controller.h`: base class for controllers
    - `PlayerController.h`: handles player actions (input)
    - `EnemyController.h`: handles enemy actions (auto)
  - `creatures/`: creature classes
    - `Creature.h`: base class for creatures
    - `CreatureType.h`: specific creature types (pikachu, piplup, etc)

  - `battle/`:
    - `Action.h`: actions creatures can perform in battle
    - `Battle.h`: declares the Battle class

  - `game/`:
    - `CreatureSelection.h`: player setup (creature selection, nickname)
    - `Encounters.h`: map interactions
    - `GameEnd.h`: win/lose logic
    - `Input.h`: player input

  - `overworld/`:
    - `OverworldMap.h`: map system
    - `EnemyField.h`: persistent enemies

  - `util/`:
    - `GameSettings.h`: game configuration and settings
    - `Helpers.h`: extra helper
    - `Health.h`: handles health values
    - `Random.h`: random number utilities
    - `Status.h`: defines status effects (poison, paralysis, etc)
    - `Type.h`: defines damage types (fire, water, etc)
