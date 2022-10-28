#include "gd_extra.hpp"

std::vector<hook_t> gd::m_hooks {};

MenuLayer* terminal::m_menuLayer = nullptr;
std::vector<std::string> terminal::m_history {};
unsigned int terminal::m_cursorIndex = 0;
unsigned int terminal::m_historyIndex = 0;