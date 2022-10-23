#pragma once
#pragma warning( push )
#pragma warning( disable : 4251 )

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gd.h>
#include <cocos2d.h>

using std::uintptr_t;
using namespace gd;
using namespace cocos2d;
using hook_t = std::tuple<bool, uintptr_t, LPVOID, LPVOID*>;

namespace gd {
    extern std::vector<hook_t> m_hooks;
}

namespace terminal {
    extern std::vector<std::string> m_history;
}

#pragma warning( pop )