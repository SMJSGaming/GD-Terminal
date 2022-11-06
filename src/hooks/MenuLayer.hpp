#pragma once

#include "../includes.hpp"
#include "../statics/static_config.hpp"
#include "../templates/MonoSpaceLabel.hpp"
#include "../templates/BetterTextArea.hpp"
#include "../templates/CursorNode.hpp"

DEFINE_HOOK(bool, MenuLayer, init);
GD_HOOK(0x1907B0, MenuLayer, init);