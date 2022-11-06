#pragma once

#include <concepts>
#include "../includes.hpp"
#include "TerminalCout.hpp"

enum FlagType {
    VOID_TYPE,
    BOOL_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
    STRING_TYPE
};

using documented_flag_t = std::tuple<FlagType, char, std::string, std::string>;
using documented_flags_t = std::vector<documented_flag_t>;
using flags_t = std::unordered_map<std::string, std::string>;

struct Command {
    static void initialize(TerminalCout& cout, std::string line);

    std::string m_name;
    std::string m_description;
    std::pair<std::string, std::string> m_globalArgs;
    documented_flags_t m_flags;

    Command(std::string name, std::string description, std::pair<std::string, std::string> globalArgs, documented_flags_t flags);
protected:
    static inline std::unordered_map<std::string, Command*> m_commands {};

    static bool parseBool(std::string value);
    static int parseInt(std::string value);
    static float parseFloat(std::string value);
    static std::string startPadding(std::string string, unsigned int width);
    static std::string endPadding(std::string string, unsigned int width);

    virtual void run(TerminalCout& cout, flags_t flags);
private:
    static void handleQuotedString(FlagType type, std::string word, char& quote, std::string& flagValue); 
};