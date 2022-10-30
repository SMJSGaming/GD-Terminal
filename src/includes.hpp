#pragma once

#define _CONCAT_LITERAL(a, b) a##b
#define CONCAT_LITERAL(a, b) _CONCAT_LITERAL(a, b)

#include "templates/gd_extra.hpp"
#include "configs/StaticConfig.hpp"
#include "templates/Command.hpp"
#include "templates/MonoSpaceLabel.hpp"
#include "templates/BetterTextArea.hpp"
#include "templates/CursorNode.hpp"
#include "registers/Hook.hpp"
#include "registers/RegisterCommand.hpp"