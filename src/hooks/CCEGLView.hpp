#pragma once

#include "../includes.hpp"

DEFINE_HOOK(void, CCEGLView, onGLFWKeyCallback, GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (terminal::menuLayer && (action == 1 || action == 2)) {
        CCLabelBMFont* arrow = static_cast<CCLabelBMFont*>(terminal::menuLayer->getChildByTag(ARROW));
        BetterTextArea<false>* history = static_cast<BetterTextArea<false>*>(terminal::menuLayer->getChildByTag(HISTORY));
        CCTextInputNode* input = static_cast<CCTextInputNode*>(terminal::menuLayer->getChildByTag(INPUT));
        CCSize marginedSize = CCDirector::sharedDirector()->getWinSize() - CCSize(PADDING, PADDING);
        std::string command = input->getString();

        switch (key) {
            case GLFW_KEY_ENTER: {
                if (command.size()) {
                    history->setText(
                        history->getText() + 
                        "\n" + 
                        arrow->getString() + 
                        command + 
                        "\n" + 
                        Command::initialize(command) +
                        "\n "
                    );
                } else {
                    history->setText(
                        history->getText() +
                        "\n" +
                        arrow->getString() +
                        command
                    );
                }

                arrow->setPosition({
                    PADDING,
                    marginedSize.height - history->getHeight()
                });
                input->setPosition({
                    arrow->getContentSize().width * 0.45f,
                    marginedSize.height - history->getHeight() + PADDING * 0.1f
                });
            } break;
            case GLFW_KEY_RIGHT: {

            } break;
            case GLFW_KEY_LEFT: {

            } break;
            case GLFW_KEY_UP: {

            } break;
            case GLFW_KEY_DOWN: {

            } break;
            case GLFW_KEY_BACKSPACE: {
                
            } break;
            case GLFW_KEY_DELETE: {

            } break;
        }
    } else {
        CCEGLView_onGLFWKeyCallback(self, window, key, scancode, action, mods);
    }
}

COCOS_HOOK(0xC3E20, CCEGLView, onGLFWKeyCallback)