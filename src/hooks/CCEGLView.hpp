#pragma once

#include "../includes.hpp"
#include "../statics/static_config.hpp"
#include "../statics/special_char_caps.hpp"
#include "../templates/MonoSpaceLabel.hpp"
#include "../templates/BetterTextArea.hpp"
#include "../templates/CursorNode.hpp"
#include "../templates/CommandExecuter.hpp"
#include "../templates/TerminalCout.hpp"
#include "../methods/reposition_elements.hpp"

static std::vector<std::string> m_history {};
static unsigned int m_cursorIndex = 0;
static unsigned int m_historyIndex = 0;

DEFINE_HOOK(void, CCEGLView, onGLFWKeyCallback, GLFWwindow* window, int key, int scancode, int action, int mods);
COCOS_HOOK(0xC3E20, CCEGLView, onGLFWKeyCallback);