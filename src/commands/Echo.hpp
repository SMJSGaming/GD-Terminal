#pragma once

#include "../includes.hpp"

struct Echo : public Command {
    Echo();
protected:
    std::string run(flags_t flags) override;
};

REGISTER_COMMAND(Echo);