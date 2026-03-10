# JRPG

This program is a small turn-based battle game inspired by classic JRPG games such as Pokémon.

---

DELETE LATER

---

TODO: programming requirements

- You must use at least one of the following: inheritance, templates, variants. Failure to do so will result in a 0.
- MAkefile

TODO: readme requeriemtns
A required part of the assignment is to provide a README file
describing what you have implemented. The README should be
rich in information, enough that we can read it to know what to
expect from playing the game and reading your code. Make two
main sections. One section should describe the program for users,
that is, players of the game. The other section should describe the
program to programmers that wish to read your code, understand
the design and possibly extend your program. Failure to provide a
README file satisfying these requirements will result in a 0.

## glósur

1. Health.h handles current/max HP

2. Move.h describes an attack

3. Creature.h is the base class for monsters different monster types inherit from Creature

4. Controller.h is an abstract interface
   - PlayerController.h asks the user what to do
   - EnemyController.h, enemy moves (attacks etc)

5. Battle.h runs the turn loop

6. main.cpp creates the player and enemy, then starts the battle

---

DELETE LATER

---

## How to compile and run

1. Compile:

```
make
```

2. Run:
   _(for better experience -> large terminal window for ascii art and text)_

```
./game
```

3. Clean build files:

```
make clean
```

## User guide for Players // TODO

### Introduction

In this game you control a creature and fight against enemy creatures.
The battles are turn-based, so each side takes turns performing actions.

At the start of the game you choose a difficulty level.

| lvl    |
| ------ |
| Easy   |
| Medium |
| Hard   |

### Overworld

The game has a small overworld map.

The map shows:

| Symbol                 | Meaning               | Effect when encountering             |
| ---------------------- | --------------------- | ------------------------------------ |
| P                      | Player                |                                      |
| w                      | Wild Creature (enemy) | A battle starts (player vs enemy)    |
| `\u2665` : ascii heart | Healing locations     | Heal Player                          |
| ?                      | Mystery locations     | Mystery Effect                       |
| .                      | Path                  | Player can move on these (no effect) |

### Battle System

When you encounter an enemy creature, a battle starts.

During battle:

- The name and ASCII art of the enemy creature are shown
- Both creatures take turns performing actions (attacks, heal, etc.)
- The creature with the higher Speed goes first
- The battle continues until one creature’s health reaches 0 or the player flees

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

The program uses inheritance to create different types of creatures and controllers.

File structure:

- `main.cpp`: entry point of the program, sets up the game and starts the battle loop

- `src/`: contains the implementation files
  - `Battle.cpp`: implementation of the battle system
  - `Overworld.cpp`: implementation of the overworld map (movement, encounters, etc)

- `include/`: contains the header files
  - `controllers/`: contains controller classes
    - `Controller.h`: base class for controllers
    - `PlayerController.h`: handles player input and actions
    - `EnemyController.h`: handles enemy AI and actions
  - `creatures/`: contains creature classes
    - `Creature.h`: base class for all creatures
    - `CreatureType.h`: defines different creature types (pikachu, piplup, etc)

  - `Action.h`: defines **actions** that creatures use in battle
  - `Battle.h`: declare Battle class
  - `GameSettings.h`: declares game settings and configurations
  - `Health.h`: handles health value
  - `OverworldMap.h`: declare OverworldMap class
  - `Random.h`: utility for random number generation
  - `Status.h`: defines statuses effects like paralysis, poison, etc
  - `Type.h`: defines damage types like fire, water, etc
