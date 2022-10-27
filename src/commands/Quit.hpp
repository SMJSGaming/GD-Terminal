#pragma once

#include "../templates/Command.hpp"

struct Quit : public Command {
    Quit();
protected:
    std::string run(flags_t flags) override;
};