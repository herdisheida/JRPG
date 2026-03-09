# JRPG

PA4 - JRPG

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

---

## Introduction

This program is a small turn-based battle game inspired by JRPGs such as Pokémon.

<!-- TODO make the enemy randomized  and maybe stats randomised -->

When the game starts, the player chooses a creature and then chooses an enemy creature to fight.  
Each creature has its own stats:

- Health
- Attack
- Defense
- Speed

Each creature also has a set of moves with different power and accuracy values.

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

```
./game
```

3. Clean build files:

```
make clean
```
