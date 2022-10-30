#pragma once

#include "../includes.hpp"

#define REGISTER_COMMAND(class) static class* CONCAT_LITERAL(class, __LINE__) = new class();