#pragma once

#define _CONCAT_LITERAL(a, b) a##b
#define CONCAT_LITERAL(a, b) _CONCAT_LITERAL(a, b)

#include "templates/gd_extra.hpp"
#include "registers/Hook.hpp"
#include "registers/RegisterCommand.hpp"