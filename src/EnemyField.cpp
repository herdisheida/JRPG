#include "../include/overworld/EnemyField.h"
#include "../include/util/Random.h"
#include "../include/creatures/CreatureFactory.h"




Creature* EnemyField::getEnemyAt(Position pos) {
    auto it = enemies_.find(pos);
    if (it != enemies_.end()) return it->second.get();
    return nullptr;
}

void EnemyField::addEnemyAt(Position pos, std::unique_ptr<Creature> enemy) {
    // only add if empty
    if (enemies_.find(pos) == enemies_.end()) {
        enemies_[pos] = std::move(enemy);
    }
}

void EnemyField::removeFainted() {
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if (it->second->isFainted()) it = enemies_.erase(it);
        else it++;
    }
}


Creature* getOrCreateRandomWildCreatureAt(EnemyField& field, Position pos) {
    Creature* enemy = field.getEnemyAt(pos);
    if (enemy) return enemy; // enemy already exists here

    // create new random enemy
    int roll = Random::range(0, 4); // 5 possible creatures
    std::string species;

    switch (roll) {
        case 0: species = "Pikachu"; break;
        case 1: species = "Piplup"; break;
        case 2: species = "Charizard"; break;
        case 3: species = "Lucario"; break;
        default: species = "Gengar"; break;
    }

    std::unique_ptr<Creature> newEnemy = CreatureFactory::create(species);
    enemy = newEnemy.get();
    field.addEnemyAt(pos, std::move(newEnemy));
    return enemy;
}
