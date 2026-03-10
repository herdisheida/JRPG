#include "../include/overworld/EnemyField.h"



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
