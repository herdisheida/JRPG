#ifndef GAMESTORE_H
#define GAMESTORE_H

#include <string>
#include "../creatures/Creature.h"
#include "../overworld/OverworldMap.h"
#include "../overworld/EnemyField.h"

namespace GameStore {

// save a game to a JSON file
void saveGame(
    const std::string& filename,
    const Creature& player,
    const OverworldMap& map,
    const EnemyField& enemies
);

// load a game from a JSON file
bool loadGame(
    const std::string& filename,
    Creature& player,
    OverworldMap& map,
    EnemyField& enemies
);

// list all save files
std::vector<std::string> listSaves(const std::string& folder = "./saves/");


}

#endif