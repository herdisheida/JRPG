#ifndef GAMESTORE_H
#define GAMESTORE_H

#include <string>
#include <vector>

#include "../overworld/OverworldMap.h"
#include "../overworld/EnemyField.h"


class Creature;

class GameStore {
    public:

        // save a game to a numbered save file (save1.txt, save2.txt, etc.)
        static bool saveGame(const std::string& saveName, const Creature& player, const OverworldMap& map, const EnemyField& enemyField);

        // load a game from a save file
        static bool loadGame(const std::string& saveName, std::unique_ptr<Creature>& player, OverworldMap& map, EnemyField& enemyField);
        // update save index: add save name to index file if not already present
        static void updateSaveIndex(const std::string& saveName);

        // list saved games (returns filenames)
        static std::vector<std::string> listSaves();

};

#endif