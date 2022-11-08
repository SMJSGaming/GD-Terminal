#pragma once

#include "../../includes.hpp"
#include "../../templates/TerminalCout.hpp"
#include "../../templates/CommandExecuter.hpp"

struct Quit : public Command {
    Quit();
protected:
    void run(TerminalCout& cout, flags_t flags) override;
};

REGISTER_COMMAND(Quit);