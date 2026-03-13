#include <iostream>
#include <iomanip> // for std::setw
#include <limits>


#include "../include/game/CreatureSelection.h"
#include "../include/creatures/CreatureType.h"




std::unique_ptr<Creature> chooseCreature(const std::string& prompt) {
    while (true) {
        std::cout << prompt << "\n\n";

        // column width for names
        constexpr int nameWidth = 12;

        std::cout << std::left; // left-align the first column

        std::cout << "1. " << std::setw(nameWidth) << "Pikachu"   << " - " << Pikachu().Roles()   << "\n";
        std::cout << "2. " << std::setw(nameWidth) << "Piplup"    << " - " << Piplup().Roles()    << "\n";
        std::cout << "3. " << std::setw(nameWidth) << "Charizard" << " - " << Charizard().Roles() << "\n";
        std::cout << "4. " << std::setw(nameWidth) << "Lucario"   << " - " << Lucario().Roles()   << "\n";
        std::cout << "5. " << std::setw(nameWidth) << "Gengar"    << " - " << Gengar().Roles()    << "\n";

        std::cout << std::right; // reset alignment to default

        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // avoid buffering issues
            std::cout << UIHelper::getErrorStr("Invalid input.\n\n");
            continue;
        }

        switch (choice) {
            case 1: return std::make_unique<Pikachu>();
            case 2: return std::make_unique<Piplup>();
            case 3: return std::make_unique<Charizard>();
            case 4: return std::make_unique<Lucario>();
            case 5: return std::make_unique<Gengar>();
            default:
                std::cout << UIHelper::getErrorStr("Invalid choice.\n\n");
        }
    }
}


// choose and set nickname for player creature
void customizeCreature(Creature& creature) {
    std::string nickname = UIHelper::getStringInput("Give " + creature.species() + " a nickname: ", "nickname");

    // convert nickname to uppercase
    std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::toupper);
    creature.setName(nickname);

    // display chosen creature
    printCreatureSummary(creature);
}

void printCreatureSummary(const Creature& creature) {
    std::cout << "\n\n================= " << creature.name() << " is ready for battle!" << " =================\n\n";

    creature.printCreature(); // print ascii art with offset
    std::cout << "\n";

    // health
    std::cout << "Health: " << creature.health().max() << " HP\n";

    // stats
    const Stats& stats = creature.stats();

    std::cout << "\nStats\n";
    std::cout << "    Attack  : " << stats.attack  << "\n";
    std::cout << "    Defense : " << stats.defense << "\n";
    std::cout << "    Speed   : " << stats.speed   << "\n";

    // resistances
    std::cout << "\nType Weakness\n";

    for (const auto& [type, multiplier] : creature.resistances()) {

        std::cout << "  " << toString(type) << ": ";
        if (multiplier > 1.0f)
            std::cout << "Weak (" << multiplier << "x)";
        else if (multiplier < 1.0f)
            std::cout << "Resistant (" << multiplier << "x)";
        else
            std::cout << "Normal";
        std::cout << "\n";
    }
    std::cout << "=====================================\n\n";
}
