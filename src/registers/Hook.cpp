#include "Hook.hpp"

Hook::Hook(hook_t hook) {
    gd::m_hooks.push_back(hook);
}