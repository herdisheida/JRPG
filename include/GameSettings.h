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
    switch (difficulty) {
        case Difficulty::Easy:
            return {4, 5, 6, 8};   // fewer wilds, more hearts
        case Difficulty::Medium:
            return {6, 3, 6, 8};   // balanced
        case Difficulty::Hard:
            return {8, 1, 6, 8};   // more wilds, fewer hearts
    }
    return {6, 3, 5, 7}; // fallback (the OG)
}

#endif