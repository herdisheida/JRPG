#ifndef COLORS_H
#define COLORS_H

#include <string>
#include <ostream>

namespace Color {

    // text color codes
    enum Code {
        // reset
        RESET = 0,

        // decoration
        BOLD = 1,
        UNDERLINE = 4,
        
        // colors
        YELLOW = 33, // warning
        BRIGHT_RED = 91, // error
        BRIGHT_GREEN = 92, // success
        MAGENTA = 35,
    };

    // return ANSI escape string for a color code
    inline std::string get(Code code) {
        return "\033[" + std::to_string(code) + "m";
    }

    // color a string with a specific color
    inline std::string colorize(const std::string& text, Code color) {
        return get(color) + text + get(RESET);
    }
}

#endif