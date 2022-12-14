#include "CCEGLView.hpp"

IMPLEMENT_HOOK(void, CCEGLView, onGLFWKeyCallback, GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (gd::m_menuLayer && (action == 1 || action == 2) && !m_silenced) {
        MonoSpaceLabel* arrow = static_cast<MonoSpaceLabel*>(gd::m_menuLayer->getChildByTag(ARROW));
        MonoSpaceLabel* input = static_cast<MonoSpaceLabel*>(gd::m_menuLayer->getChildByTag(INPUT));
        BetterTextArea* history = static_cast<BetterTextArea*>(gd::m_menuLayer->getChildByTag(HISTORY));
        CursorNode* cursor = static_cast<CursorNode*>(gd::m_menuLayer->getChildByTag(CURSOR));
        CCSize charSize = arrow->getCharSize();
        std::string command = input->getString();

        // OMG why does command prompt have so many control edge cases???? I want to literally grab Bill Gates and yeet him into the Grand Canyon.
        switch (key) {
            case GLFW_KEY_ENTER: {
                if (!((GLFW_MOD_CONTROL | GLFW_MOD_ALT) & mods)) {
                    m_silenced = true;

                    if (command.size()) {
                        m_history.push_back(command);
                        history->pushLine((arrow->getString() + command).c_str(), false);
                        cursor->toggle();

                        m_cursorIndex = 0;
                        m_historyIndex = m_history.size();

                        CommandExecuter::initialize(command);
                    } else {
                        history->pushLine((arrow->getString() + command).c_str());

                        reposition_elements();
                    }

                    return;
                }
            } break;
            case GLFW_KEY_RIGHT: {
                const unsigned int commandSize = command.size();

                if (m_cursorIndex < commandSize && !((GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (GLFW_MOD_CONTROL & mods) {
                        m_cursorIndex = commandSize;
                    } else {
                        m_cursorIndex++;
                    }
                }
            } break;
            case GLFW_KEY_LEFT: {
                if (m_cursorIndex && !((GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (GLFW_MOD_CONTROL & mods) {
                        m_cursorIndex = 0;
                    } else {
                        m_cursorIndex--;
                    }
                }
            } break;
            case GLFW_KEY_UP: {
                if (m_historyIndex > 0 && !((GLFW_MOD_CONTROL | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    std::string history = m_history.at(--m_historyIndex);
                    
                    m_cursorIndex = history.size();

                    input->setString(history.c_str());
                }
            } break;
            case GLFW_KEY_DOWN: {
                const unsigned int historySize = m_history.size();

                if (!((GLFW_MOD_CONTROL | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (historySize && m_historyIndex < historySize - 1) {
                        std::string history = m_history.at(++m_historyIndex);

                        m_cursorIndex = history.size();

                        input->setString(history.c_str());
                    } else {
                        m_historyIndex = historySize;
                        m_cursorIndex = 0;

                        input->setString("");
                    }
                }
            } break;
            case GLFW_KEY_BACKSPACE: {
                if (m_cursorIndex && command.size()) {
                    if (GLFW_MOD_CONTROL & mods) {
                        if (!((GLFW_MOD_SHIFT | GLFW_MOD_ALT) & mods)) {
                            input->setString(command.erase(0, m_cursorIndex).c_str());

                            m_cursorIndex = 0;
                        }
                    } else {
                        input->setString(command.erase(m_cursorIndex-- - 1, 1).c_str());
                    }
                }
            } break;
            case GLFW_KEY_DELETE: {
                if (m_cursorIndex != command.size()) {
                    if (GLFW_MOD_CONTROL & mods) {
                        if (!((GLFW_MOD_SHIFT | GLFW_MOD_ALT) & mods)) {

                        }
                    } else {
                        input->setString(command.erase(m_cursorIndex, 1).c_str());
                    }
                }
            } break;
            case GLFW_KEY_V: {
                if ((GLFW_MOD_CONTROL & mods) && !((GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods) && OpenClipboard(NULL)) {
                    const char* pasted = static_cast<const char*>(GetClipboardData(CF_TEXT));

                    if (pasted) {
                        input->setString(command.insert(m_cursorIndex, pasted).c_str());

                        m_cursorIndex += strlen(pasted);
                    }

                    CloseClipboard();

                    break;
                }
            }
            default: {
                if (key >= 0 && key <= 255 && ((GLFW_MOD_ALT | GLFW_MOD_CONTROL) & mods) != (GLFW_MOD_ALT | GLFW_MOD_CONTROL)) {
                    const bool isSpecialKey = CAPITALIZATION_QWERTY.find(key) != CAPITALIZATION_QWERTY.end();

                    if (mods & GLFW_MOD_CONTROL && !isSpecialKey) {
                        key = toupper(key);

                        input->setString(command.insert(m_cursorIndex++, 1, '^').c_str());
                    } else if (!(mods & GLFW_MOD_SHIFT)) {
                        key = tolower(key);
                    } else if (isSpecialKey) {
                        key = CAPITALIZATION_QWERTY.at(key);
                    }

                    input->setString(command.insert(m_cursorIndex++, 1, key).c_str());
                }
            }
        }

        history->setPosition({
            PADDING,
            arrow->getPositionY() - CHAR_SCALE
        });
        cursor->setPosition({
            input->getPositionX() + m_cursorIndex * charSize.width,
            cursor->getPositionY()
        });
        cursor->reset();
    } else {
        CCEGLView_onGLFWKeyCallback(self, window, key, scancode, action, mods);
    }
}