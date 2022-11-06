#include "Help.hpp"

Help::Help(): Command("help", "Provides a description of a provided command and its flags", { "command", "The command to evaluate" }, {
}) {}

void Help::run(TerminalCout& cout, flags_t flags) {
    std::string global = flags.at("*");
    Command* command;

    if (global.empty()) {
        command = Command::m_commands.at("help");
    } else if (Command::m_commands.find(global) == Command::m_commands.end()) {
        throw std::invalid_argument("Command not found");
    } else {
        command = Command::m_commands.at(global);
    }

    cout << "USAGE: " << command->m_name;

    if (command->m_globalArgs.first.size()) {
        cout << " [" << command->m_globalArgs.first << "]";
    }

    cout << TerminalCout::endl << command->m_description << TerminalCout::blank;

    if (command->m_globalArgs.first.size() && command->m_globalArgs.second.size()) {
        cout << "GLOBAL ARGS"
            << TerminalCout::endl
            << Command::endPadding(TerminalCout::tab + command->m_globalArgs.first, 30)
            << command->m_globalArgs.second
            << TerminalCout::blank;
    }

    cout << "FLAGS";

    for (const auto& [ type, charFlag, wordFlag, description ] : command->m_flags) {
        cout << TerminalCout::endl << Command::endPadding(TerminalCout::tab + "-" + charFlag + ", --" + wordFlag, 30) << description;
    }
}