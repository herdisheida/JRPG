#include <fstream>
#include <string>


#include "../include/creatures/Creature.h"
#include "../include/overworld/OverworldMap.h"

#include "../include/game/GameStore.h"



// save the game
bool GameStore::saveGame(const std::string& filename, const Creature& player, const OverworldMap& map) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << player.species() << "\n";
    file << player.name() << "\n";
    file << player.health().current() << "\n";

    auto [x, y] = map.getPlayerPos();
    file << x << " " << y << "\n";

    map.serialize(file);

    file.close();
    return true;
}
