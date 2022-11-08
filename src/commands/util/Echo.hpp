#pragma once

#include "../../includes.hpp"
#include "../../templates/TerminalCout.hpp"
#include "../../templates/CommandExecuter.hpp"

struct Echo : public Command {
    Echo();
protected:
    void run(TerminalCout& cout, flags_t flags) override;
};

REGISTER_COMMAND(Echo);