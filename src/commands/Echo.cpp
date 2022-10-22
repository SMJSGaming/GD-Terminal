#include "Echo.hpp"
#include "../registers/RegisterCommand.hpp"

Echo::Echo(): Command("echo", "Prints the provided arguments", {
    { 'r', "reverse", "Prints the line in reverse" },
    { 'u', "uppercase", "Prints the line in uppercase" },
    { 'l', "lowercase", "Prints the line in lowercase" },
    { 'n', "number", "Prints the line a provided number of times" }
}) {}

std::string Echo::run(flags_t flags) {
    std::string line;
    bool reverse = false;
    bool uppercase = false;
    bool lowercase = false;
    unsigned int number = 1;

    for (const auto& [ flag, value ] : flags) {
        switch (flag[0]) {
            case 'r': {
                reverse = true;
            } break;
            case 'u': {
                lowercase = false;
                uppercase = true;
            } break;
            case 'l': {
                uppercase = false;
                lowercase = true;
            } break;
            case 'n': {
                number = std::stoi(value);
            } break;
            default: {
                line += value + ' ';
            }
        }
    }

    if (reverse) {
        std::reverse(line.begin(), line.end());
    }

    if (uppercase) {
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
    } else if (lowercase) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    }

    for (unsigned int i = 1; i < number; i++) {
        line += '\n' + line;
    }

    return line;
}

//REGISTER_COMMAND(Echo);