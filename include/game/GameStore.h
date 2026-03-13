#ifndef GAMESTORE_H
#define GAMESTORE_H

#include <string>
#include <vector>

#include "../creatures/Creature.h"
#include "../overworld/OverworldMap.h"

class GameStore {
    public:

        // save a game to a numbered save file (save1.txt, save2.txt, etc.)
        static bool saveGame(const std::string& saveName, const Creature& player, const OverworldMap& map);


        // load a game from a save file
        static bool loadGame(const std::string& saveName, Creature& player, OverworldMap& map);

        // list saved games (returns filenames)
        static std::vector<std::string> listSaves();

};

#endif