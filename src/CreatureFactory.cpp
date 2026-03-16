#include <memory>

#include "../include/creatures/CreatureFactory.h"
#include "../include/creatures/CreatureType.h"
#include "../include/creatures/Creature.h"


std::unique_ptr<Creature> CreatureFactory::create(const std::string& species) {
    if (species == "Pikachu") return std::make_unique<Pikachu>();
    if (species == "Piplup") return std::make_unique<Piplup>();
    if (species == "Charizard") return std::make_unique<Charizard>();
    if (species == "Lucario") return std::make_unique<Lucario>();
    if (species == "Gengar") return std::make_unique<Gengar>();
    return nullptr; // unknown species
}