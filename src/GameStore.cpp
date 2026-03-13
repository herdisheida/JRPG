#include <fstream>
#include <string>


#include "../include/creatures/Creature.h"
#include "../include/creatures/CreatureFactory.h"
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

// list all saved games
std::vector<std::string> GameStore::listSaves() {
    std::vector<std::string> saves;
    std::ifstream file("saves.txt");
    if (!file.is_open()) return saves;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) saves.push_back(line);
    }
    file.close();
    return saves;
}

// load a saved game
bool GameStore::loadGame(const std::string& filename, Creature& player, OverworldMap& map) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string species, name;
    int hp, x, y;

    std::getline(file, species);
    std::getline(file, name);
    file >> hp;
    file >> x >> y;
    file.ignore(); // ignore newline

    player = *CreatureFactory::create(species); // assumes you have this factory
    player.setName(name);
    player.health().set(hp, player.health().max());

    map.deserialize(file);
    map.setPlayerPosition(x, y);

    file.close();
    return true;
}

