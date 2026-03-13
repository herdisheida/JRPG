#ifndef GAMESTORE_H
#define GAMESTORE_H

#include <string>
#include <vector>

#include "../creatures/Creature.h"
#include "../overworld/OverworldMap.h"

namespace GameStore {

// save a game to a numbered save file (save1.txt, save2.txt, etc.)
bool saveGame(const std::string& filename, const Creature& player, const OverworldMap& map);

// list saved games (returns filenames)
std::vector<std::string> listSaves();

// load a game from a save file
bool loadGame(const std::string& filename, Creature& player, OverworldMap& map);

}

#endif