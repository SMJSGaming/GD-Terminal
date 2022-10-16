#pragma once

#include "../includes.hpp"

using documented_flag_t = std::tuple<char, std::string, std::string>;
using documented_flags_t = std::vector<documented_flag_t>;
using flags_t = std::map<std::string, std::string>;

struct Command {
    static std::string initialize(std::string line);

    std::string name;
    std::string description;
    documented_flags_t flags;

    Command(std::string name, std::string description, documented_flags_t flags);
private:
    static std::unordered_map<std::string, Command*> commands;
protected:
    virtual std::string run(flags_t flags)=0;
};