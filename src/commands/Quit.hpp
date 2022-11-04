#pragma once

#include "../includes.hpp"
#include "../templates/TerminalCout.hpp"
#include "../templates/Command.hpp"

struct Quit : public Command {
    Quit();
protected:
    std::string run(flags_t flags) override;
};

REGISTER_COMMAND(Quit);