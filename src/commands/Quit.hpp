#pragma once

#include "../includes.hpp"

struct Quit : public Command {
    Quit();
protected:
    std::string run(flags_t flags) override;
};

REGISTER_COMMAND(Quit);