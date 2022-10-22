#include "Quit.hpp"
#include "../registers/RegisterCommand.hpp"

Quit::Quit(): Command("quit", "Closes the game", {
    { 's', "save", "When overwritten with false or 0, the game will close without saving. It's true by default" },
}) {}

std::string Quit::run(flags_t flags) {
    bool save = true;

    for (const auto& [ flag, value ] : flags) {
        if (flag == "s" || flag == "save") {
            save = !(value == "false" || value == "0");
        }
    }

    if (save) {
        GameManager::sharedState()->save();
    }

    exit(0);

    // If you see this then something *really* went wrong
    return "Quitting...";
}

//REGISTER_COMMAND(Quit);