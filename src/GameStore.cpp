#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h> // mkdir (mac)
#include <sys/types.h>
#include <memory>

#include "../include/creatures/Creature.h"
#include "../include/creatures/CreatureFactory.h"
#include "../include/overworld/OverworldMap.h"
#include "../include/game/GameStore.h"


// folder and index
constexpr const char* SAVE_FOLDER = "saves";
constexpr const char* INDEX_FILE = "saves/index.txt";

// helper to make sure folder exists
static void ensureSaveFolderExists() {
#ifdef _WIN32
    _mkdir(SAVE_FOLDER);
#else
    mkdir(SAVE_FOLDER, 0777);
#endif
}


// save the game
bool GameStore::saveGame(const std::string& saveName, const Creature& player, const OverworldMap& map) {
    ensureSaveFolderExists();

    std::string filename = std::string(SAVE_FOLDER) + "/" + saveName + ".txt";
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // save player
    file << player.species() << "\n";
    file << player.name() << "\n";
    file << player.health().current() << "\n";
    file << player.health().max() << "\n";

    auto pos = map.getPlayerPos();
    file << pos.row << " " << pos.col << "\n";

    // save map
    map.serialize(file);

    file.close();

    // update index - do nothing if index already has this save
    updateSaveIndex(saveName);
    return true;
}


// update index safely
void GameStore::updateSaveIndex(const std::string& saveName) {
    std::ifstream indexIn(INDEX_FILE);
    bool exists = false;

    if (indexIn.is_open()) {
        std::string line;
        while (std::getline(indexIn, line)) {
            if (line == saveName) {
                exists = true;
                break;
            }
        }
        indexIn.close();
    }

    if (!exists) {
        // append only if not exists    
        std::ofstream indexOut(INDEX_FILE, std::ios::app);
        if (indexOut.is_open()) {
            indexOut << saveName << "\n";
            indexOut.close();
        }
    }
}

// load a saved game
bool GameStore::loadGame(const std::string& saveName, std::unique_ptr<Creature>& player, OverworldMap& map) {
    std::string filename = std::string(SAVE_FOLDER) + "/" + saveName + ".txt";
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string species, name;
    int hp, maxHp, row, col;

    std::getline(file, species);
    std::getline(file, name);
    file >> hp;
    file >> maxHp;
    file >> row >> col;
    file.ignore();

    auto tempPlayer = CreatureFactory::create(species);
    if (!tempPlayer) return false;

    tempPlayer->setName(name);
    tempPlayer->health().set(hp, maxHp);

    player = std::move(tempPlayer);
    map.deserialize(file);
    map.setPlayerPosition(row, col);

    return true;
}


// list all saved games
std::vector<std::string> GameStore::listSaves() {
    std::vector<std::string> saves;
    std::ifstream index(INDEX_FILE);
    if (!index.is_open()) return saves;

    std::string line;
    while (std::getline(index, line)) {
        if (!line.empty()) saves.push_back(line);
    }
    index.close();
    return saves;
}
