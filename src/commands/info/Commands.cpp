#include "Commands.hpp"

Commands::Commands(): Command("commands", "Lists all registered commands", {}, {}) {}

void Commands::run(TerminalCout& cout, flags_t flags) {
    cout << "COMMANDS:";

    for (const auto& [ name, command ] : CommandExecuter::m_commands) {
        cout << TerminalCout::endl << Command::endPadding(name, 30) << command->m_description;
    }
}