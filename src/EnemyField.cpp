#include <stddef.h>
#include <fstream>
#include <string>
#include <utility>

#include "../include/overworld/EnemyField.h"
#include "../include/overworld/OverworldMap.h"
#include "../include/creatures/CreatureFactory.h"
#include "../include/creatures/Creature.h"
#include "../include/util/Health.h"
#include "../include/util/Random.h"



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


void EnemyField::serialize(std::ofstream& file) const {
    file << enemies_.size() << "\n";
    for (const auto& [pos, enemy] : enemies_) {
        file << pos.row << " " << pos.col << " " << enemy->species() << " " << enemy->health().current() << " " << enemy->health().max() << "\n";
    }
}

void EnemyField::deserialize(std::ifstream& file) {
    size_t count;
    file >> count;

    enemies_.clear();

    for (size_t i = 0; i < count; ++i) {
        Position pos;
        std::string species;
        int hp, maxHp;

        file >> pos.row >> pos.col >> species >> hp >> maxHp;

        auto enemy = CreatureFactory::create(species);
        enemy->health().set(hp, maxHp);

        enemies_[pos] = std::move(enemy);
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
