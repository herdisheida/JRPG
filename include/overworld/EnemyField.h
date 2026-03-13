#ifndef ENEMYFIELD_H
#define ENEMYFIELD_H

#include <vector>
#include <memory>
#include <string>
#include <utility> // std::pair

#include "../creatures/Creature.h"

struct Position;

// keep track of enemies currently on the map
class EnemyField {
    private:
        // map position to enemy
        std::map<Position, std::unique_ptr<Creature>> enemies_;

    public:
        // Get the enemy at a position, or nullptr if none
        Creature* getEnemyAt(Position pos);

        // add a new enemy at a position
        void addEnemyAt(Position pos, std::unique_ptr<Creature> enemy);

        // remove enemy if fainted
        void removeFainted();

        // list all enemies on the field
        void listEnemies() const;

        // save and load enemyField to file
        void serialize(std::ofstream& file) const;
        void deserialize(std::ifstream& file);

};

// get or create wild enemies (persisteent)
Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos);


#endif
