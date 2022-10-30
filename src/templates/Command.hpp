#pragma once

#include "../includes.hpp"

using documented_flag_t = std::tuple<char, std::string, std::string>;
using documented_flags_t = std::vector<documented_flag_t>;
using flags_t = std::map<std::string, std::string>;

struct Command {
    static inline std::unordered_map<std::string, Command*> m_commands {};

    static std::string initialize(std::string line);

    Command(std::string name, std::string description, documented_flags_t flags);
private:
    static std::string handleQuotedString(std::string word, char& quote, std::string& flagValue); 

    std::string m_name;
    std::string m_description;
    documented_flags_t m_flags;
protected:
    virtual std::string run(flags_t flags);
};