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

Higher difficulties have more wild enemies and fewer healing items.

### Overworld

The game has a small overworld map.

The map shows:

| Symbol  | Meaning              | Effect when encountering             |
| ------- | -------------------- | ------------------------------------ |
| P       | Player               |                                      |
| M       | Wild enemy creatures | Battle (enemy vs player)             |
| \u2665; | Healing locations    | Heal Player                          |
| ?       | Mystery locations    | Mystery Effect                       |
| .       | Path                 | Player can move on these (no effect) |

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
- **Resistances**: how much damage it takes from certain types (effective, normal, resistant)

### Action Types

Creatures can perform different types of actions during battle:

- **Attack**: deals damage to the opponent
- **Special**: a attack with a special effect, such as inflicting a status condition (e.g. burn, freeze, paralysis)
- **Heal**: restores the user's health
- **Defend**: reduces the damage of the next incoming attack
- **Flee**: attempts to escape the battle

### Damage Types

Moves can have different damage types, for example:

- Fire
- Water
- Physical
- Magical

Creatures can have resistances to these types.

Example multipliers:

- 0.5 → takes half damage (resistant)
- 1.0 → normal damage
- 1.5 → takes extra damage (weak)

### Damage Calculation

Damage depends on several things:

1.  Attacker's **Attack stats**
2.  **Action Power scale**
3.  Defender's **Defense stats**
4.  A small random variation
5.  Damage type **resistance**
6.  Enemies **Defence stats** or **Defend Action**
7.  Critical hits

This makes battles less predictable and more interesting

#####

## For Programmers // TODO

This program is a small turn-based battle game inspired by JRPGs such as Pokémon.

### Gameplay

- The player chooses a creature to battle with.
- Name and ASCII art of the creature is displayed.
- The player battles against a randomly generated enemy creature.
- Overworld map with player and wild creatures is displayed. (healing in overworld) ---- overworld map shows: enemies, player, healing, mystery
- difficulty : easy, medium, hard (more wild creatures, less healing items) // player can choose difficulty at the start of the game

### Battle Mechanics

Each creature has:

### Action types

The game supports four action types:

- **Attack**: deals damage to the opponent
- **Special**: a attack with a special effect, such as inflicting a status condition (e.g. burn, freeze, paralysis)
- **Heal**: restores the user's health
- **Defend**: reduces the damage of the next incoming attack
- **Flee**: attempts to escape the battle

### Critical hits

Attack actions have a critical hit chance.  
If a critical hit occurs, the final damage is doubled.

### Damage types and resistances

Attack actions have a damage type, such as:

- Fire
- Water
- Physical
- Magical

Each creature has resistance multipliers against these types.

FX:

- `0.5` means the creature resists that type and takes half damage
- `1.0` means normal damage
- `1.5` means weakness and the creature takes extra damage

### Damage formula

For attacks, the game uses a formula based on:

- attacker Attack
- action Power
- defender Defense
- small random variation
- type resistance multiplier
- defending reduction
- critical hit multiplier

### How battle works

- The creature with the higher Speed acts first.
- On your turn, you choose one move from a menu.
- On the enemy turn, the enemy chooses a move automatically.
- A move may miss depending on its accuracy.
- Damage is calculated using the attacker’s Attack, the move’s Power, and the defender’s Defense.
- A small random variation is added to damage to make battles less predictable.
- When a creature’s Health reaches 0, it faints and the battle ends.

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
