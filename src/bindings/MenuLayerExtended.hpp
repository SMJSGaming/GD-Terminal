#pragma once

#include "../includes.hpp"

namespace gd {
    struct MenuLayerExtended : public MenuLayer {
        void onPlay(CCObject* sender) {
            reinterpret_cast<void(__thiscall*)(MenuLayer*, CCObject*)>(gd::base + 0x191B50)(this, sender);
        }
    };
}