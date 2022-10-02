#pragma once

// As the wise man Dani once said. Shut.
#pragma warning( push )
#pragma warning( disable : 4251 )

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MinHook.h>
#include <gd.h>
#include <cocos2d.h>

using std::uintptr_t;
using namespace gd;
using namespace cocos2d;
using hook_t = std::tuple<uintptr_t, LPVOID, LPVOID*>;

namespace Mod {
    extern std::vector<hook_t> hooks;
}

#include "registers/Hook.hpp"
#include "registers/StaticIncludes.hpp"

#pragma warning( pop )