#pragma once

#include "../includes.hpp"

DEFINE_HOOK(void, CCEGLView, onGLFWKeyCallback, GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (terminal::m_menuLayer && (action == 1 || action == 2)) {
        MonoSpaceLabel* arrow = static_cast<MonoSpaceLabel*>(terminal::m_menuLayer->getChildByTag(ARROW));
        MonoSpaceLabel* input = static_cast<MonoSpaceLabel*>(terminal::m_menuLayer->getChildByTag(INPUT));
        BetterTextArea* history = static_cast<BetterTextArea*>(terminal::m_menuLayer->getChildByTag(HISTORY));
        CursorNode* cursor = static_cast<CursorNode*>(terminal::m_menuLayer->getChildByTag(CURSOR));
        CCSize charSize = arrow->getCharSize();
        std::string command = input->getString();

        // OMG why does command prompt have so many control edge cases???? I want to literally grab Bill Gates and yeet him into the Grand Canyon.
        switch (key) {
            case GLFW_KEY_ENTER: {
                if (!((GLFW_MOD_CONTROL | GLFW_MOD_ALT) & mods)) {
                    if (command.size()) {
                        terminal::m_history.push_back(command);
                        history->pushLine((arrow->getString() + command).c_str(), false);
                        history->pushLine(Command::initialize(command).c_str(), false);
                        history->pushLine(" ");
                        input->setString("");

                        terminal::m_cursorIndex = 0;

                        terminal::m_historyIndex = terminal::m_history.size();
                    } else {
                        history->pushLine((arrow->getString() + command).c_str());
                    }

                    float historyHeight = CCDirector::sharedDirector()->getWinSize().height - history->getContentSize().height - PADDING;
                    float arrowHeight = arrow->getContentSize().height;

                    arrow->setPosition({
                        arrow->getPositionX(),
                        historyHeight - arrowHeight > PADDING ? historyHeight : PADDING + arrowHeight
                    });
                    input->setPosition({
                        input->getPositionX(),
                        arrow->getPositionY()
                    });
                    cursor->setPositionY(input->getPositionY() - charSize.height - cursor->getContentSize().height);
                }
            } break;
            case GLFW_KEY_RIGHT: {
                const unsigned int commandSize = command.size();

                if (terminal::m_cursorIndex < commandSize && !((GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (GLFW_MOD_CONTROL & mods) {
                        terminal::m_cursorIndex = commandSize;
                    } else {
                        terminal::m_cursorIndex++;
                    }
                }
            } break;
            case GLFW_KEY_LEFT: {
                if (terminal::m_cursorIndex && !((GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (GLFW_MOD_CONTROL & mods) {
                        terminal::m_cursorIndex = 0;
                    } else {
                        terminal::m_cursorIndex--;
                    }
                }
            } break;
            case GLFW_KEY_UP: {
                if (terminal::m_historyIndex > 0 && !((GLFW_MOD_CONTROL | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    std::string history = terminal::m_history.at(--terminal::m_historyIndex);
                    
                    terminal::m_cursorIndex = history.size();

                    input->setString(history.c_str());
                }
            } break;
            case GLFW_KEY_DOWN: {
                const unsigned int historySize = terminal::m_history.size();

                if (!((GLFW_MOD_CONTROL | GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods)) {
                    if (historySize && terminal::m_historyIndex < historySize - 1) {
                        std::string history = terminal::m_history.at(++terminal::m_historyIndex);

                        terminal::m_cursorIndex = history.size();

                        input->setString(history.c_str());
                    } else {
                        terminal::m_historyIndex = historySize;
                        terminal::m_cursorIndex = 0;

                        input->setString("");
                    }
                }
            } break;
            case GLFW_KEY_BACKSPACE: {
                if (terminal::m_cursorIndex && command.size()) {
                    if (GLFW_MOD_CONTROL & mods) {
                        if (!((GLFW_MOD_SHIFT | GLFW_MOD_ALT) & mods)) {
                            input->setString(command.erase(0, terminal::m_cursorIndex).c_str());

                            terminal::m_cursorIndex = 0;
                        }
                    } else {
                        input->setString(command.erase(terminal::m_cursorIndex-- - 1, 1).c_str());
                    }
                }
            } break;
            case GLFW_KEY_DELETE: {
                if (terminal::m_cursorIndex != command.size()) {
                    if (GLFW_MOD_CONTROL & mods) {
                        if (!((GLFW_MOD_SHIFT | GLFW_MOD_ALT) & mods)) {

                        }
                    } else {
                        input->setString(command.erase(terminal::m_cursorIndex, 1).c_str());
                    }
                }
            } break;
            case GLFW_KEY_V: {
                if ((GLFW_MOD_CONTROL & mods) && !((GLFW_MOD_ALT | GLFW_MOD_SHIFT) & mods) && OpenClipboard(NULL)) {
                    const char* pasted = static_cast<const char*>(GetClipboardData(CF_TEXT));

                    if (pasted) {
                        input->setString(command.insert(terminal::m_cursorIndex, pasted).c_str());

                        terminal::m_cursorIndex += strlen(pasted);
                    }

                    CloseClipboard();

                    break;
                }
            }
            default: {
                if (key >= 0 && key <= 255 && ((GLFW_MOD_ALT | GLFW_MOD_CONTROL) & mods) != (GLFW_MOD_ALT | GLFW_MOD_CONTROL)) {
                    if (mods & GLFW_MOD_CONTROL) {
                        key = toupper(key);

                        input->setString(command.insert(terminal::m_cursorIndex++, 1, '^').c_str());
                    } else if (!(mods & GLFW_MOD_SHIFT)) {
                        key = tolower(key);
                    }

                    input->setString(command.insert(terminal::m_cursorIndex++, 1, key).c_str());
                }
            }
        }

        history->setPosition({
            PADDING,
            arrow->getPositionY() - CHAR_SCALE
        });
        cursor->setPosition({
            input->getPositionX() + terminal::m_cursorIndex * charSize.width,
            cursor->getPositionY()
        });
    } else {
        CCEGLView_onGLFWKeyCallback(self, window, key, scancode, action, mods);
    }
}

COCOS_HOOK(0xC3E20, CCEGLView, onGLFWKeyCallback)