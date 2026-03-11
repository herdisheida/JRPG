#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <string>

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

struct GameSettings {
    int wildCount;
    int heartCount;
    int mysteryCount;
    int rows;
    int cols;
};

// convert difficulty to readable text
inline std::string difficultyToString(Difficulty d) {
    switch (d) {
        case Difficulty::Easy:   return "Easy";
        case Difficulty::Medium: return "Medium";
        case Difficulty::Hard:   return "Hard";
    }
    return "Unknown";
}

// return settings depending on difficulty
inline GameSettings settingsForDifficulty(Difficulty difficulty) {
    // { wildCount, heartCount, mysteryCount, rows, cols }
    switch (difficulty) {
        case Difficulty::Easy:
            return { 2, 5, 0, 4, 6 };   // fewer wilds, more hearts
        case Difficulty::Medium:
            return { 3, 2, 4, 6, 8 };   // balanced
        case Difficulty::Hard:
            return { 6, 2, 7, 6, 8 };   // more wilds, fewer hearts
    }
    return { 5, 3, 5, 6, 8 }; // fallback (the OG)
}

// overworld map difficulty selection
Difficulty chooseDifficulty();

#endif
