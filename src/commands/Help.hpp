#pragma once

#include "../includes.hpp"
#include "../templates/TerminalCout.hpp"
#include "../templates/Command.hpp"

struct Help : public Command {
    Help();
protected:
    void run(TerminalCout& cout, flags_t flags) override;
};

REGISTER_COMMAND(Help);