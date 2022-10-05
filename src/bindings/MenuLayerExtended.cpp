#include "MenuLayerExtended.hpp"

void gd::MenuLayerExtended::onPlay(CCObject* sender) {
    reinterpret_cast<void(__thiscall*)(MenuLayer*, CCObject*)>(gd::base + 0x191B50)(this, sender);
}