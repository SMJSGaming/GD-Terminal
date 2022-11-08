#pragma once

#include "../includes.hpp"
#include "../statics/static_config.hpp"
#include "../templates/Command.hpp"
#include "../templates/TerminalCout.hpp"
#include "../methods/reposition_elements.hpp"

struct CommandExecuter : public CCObject {
    static TerminalCout m_cout;
    static inline std::unordered_map<std::string, Command*> m_commands {};

    static void initialize(std::string line);

    void update(float) override;
private:
    static CommandExecuter* create(Command* command, flags_t flags);
    static void handleQuotedString(FlagType type, std::string word, char& quote, std::string& flagValue);
    static void finished(bool willTransition);

    Command* m_command;

    CommandExecuter(Command* command, flags_t flags);
};