#include "reposition_elements.hpp"

void reposition_elements() {
    MonoSpaceLabel* arrow = static_cast<MonoSpaceLabel*>(gd::m_menuLayer->getChildByTag(ARROW));
    MonoSpaceLabel* input = static_cast<MonoSpaceLabel*>(gd::m_menuLayer->getChildByTag(INPUT));
    BetterTextArea* history = static_cast<BetterTextArea*>(gd::m_menuLayer->getChildByTag(HISTORY));
    CursorNode* cursor = static_cast<CursorNode*>(gd::m_menuLayer->getChildByTag(CURSOR));
    CCSize charSize = arrow->getCharSize();
    float historyHeight = CCDirector::sharedDirector()->getWinSize().height - history->getContentSize().height - PADDING;
    float arrowHeight = arrow->getContentSize().height;

    input->setString("");
    arrow->setPosition({
        arrow->getPositionX(),
        historyHeight - arrowHeight > PADDING ? historyHeight : PADDING + arrowHeight
    });
    input->setPosition({
        input->getPositionX(),
        arrow->getPositionY()
    });
    history->setPosition({
        PADDING,
        arrow->getPositionY() - CHAR_SCALE
    });
    cursor->setPosition({
        input->getPositionX(),
        input->getPositionY() - charSize.height - cursor->getContentSize().height
    });
    cursor->toggle();

    m_silenced = false;
}