#pragma once

#include "../../includes.hpp"
#include "../../templates/TerminalCout.hpp"
#include "../../templates/CommandExecuter.hpp"
#include "../../bindings/GameLevelManagerExt.hpp"

struct Play : public Command, public LevelDownloadDelegate {
    Play();
protected:
    void run(TerminalCout& cout, flags_t flags) override;
    void levelDownloadFinished(GJGameLevel* level) override;
    void levelDownloadFailed(int code) override;
};

REGISTER_COMMAND(Play);