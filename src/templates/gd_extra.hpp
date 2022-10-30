#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gd.h>
#include <cocos2d.h>

using std::uintptr_t;
using namespace gd;
using namespace cocos2d;
using hook_t = std::tuple<bool, uintptr_t, LPVOID, LPVOID*>;

namespace gd {
    inline MenuLayer* m_menuLayer = nullptr;
    inline std::vector<hook_t> m_hooks {};
}
