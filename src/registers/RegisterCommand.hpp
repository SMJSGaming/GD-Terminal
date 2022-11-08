#pragma once

#include "../includes.hpp"

#define REGISTER_COMMAND(class) static auto CONCAT_LITERAL(class, __LINE__) = new class(); \
    static auto CONCAT_LITERAL(CONCAT_LITERAL(class, __LINE__), _key) = CommandExecuter::m_commands.insert({ \
        CONCAT_LITERAL(class, __LINE__)->m_name, CONCAT_LITERAL(class, __LINE__) \
    })