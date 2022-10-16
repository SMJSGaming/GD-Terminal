#pragma once

#include "../templates/Command.hpp"

struct Echo : public Command {
    Echo();
protected:
    std::string run(flags_t flags);
};