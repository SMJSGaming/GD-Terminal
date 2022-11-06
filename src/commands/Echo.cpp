#include "Echo.hpp"

Echo::Echo(): Command("echo", "Prints the provided arguments", {
    { FlagType::VOID_TYPE, 'r', "reverse", "Prints the line in reverse" },
    { FlagType::VOID_TYPE, 'u', "uppercase", "Prints the line in uppercase" },
    { FlagType::VOID_TYPE, 'l', "lowercase", "Prints the line in lowercase" },
    { FlagType::INT_TYPE, 'n', "number", "Prints the line a provided number of times" }
}) {}

void Echo::run(TerminalCout& cout, flags_t flags) {
    std::string line = flags.at("*");
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
                number = Command::parseInt(value);
            } break;
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

    for (unsigned int i = 0; i < number; i++) {
        if (i) {
            cout << TerminalCout::endl << line;
        } else {
            cout << line;
        }
    }
}