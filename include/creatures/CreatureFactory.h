#ifndef CREATURE_FACTORY_H
#define CREATURE_FACTORY_H

#include <memory>
#include <string>
#include "Creature.h"
#include "CreatureType.h"

class CreatureFactory {
public:
    static std::unique_ptr<Creature> create(const std::string& species);
};

#endif