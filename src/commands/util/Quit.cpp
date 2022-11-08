#include "Quit.hpp"

Quit::Quit(): Command("quit", "Closes the game", {}, {
    { FlagType::BOOL_TYPE, 's', "save", "When overwritten with false or 0, the game will close without saving. It's true by default" },
}) {}

void Quit::run(TerminalCout& cout, flags_t flags) {
    bool save = true;

    for (const auto& [ flag, value ] : flags) {
        if (flag[0] == 's') {
            save = Command::parseBool(value);
        }
    }

    if (save) {
        GameManager::sharedState()->save();
    }

    exit(0);

    // If you see this then something *really* went wrong
    cout << "Quitting...";
}