#include "MenuLayer.hpp"

IMPLEMENT_HOOK(bool, MenuLayer, init) {
    GameSoundManager::sharedState()->stopBackgroundMusic();

    gd::m_menuLayer = self;
    MonoSpaceLabel* input = MonoSpaceLabel::create("", FONT, CHAR_SCALE);
    MonoSpaceLabel* arrow = MonoSpaceLabel::create((GJAccountManager::sharedState()->m_sUsername + ">").c_str(), FONT, CHAR_SCALE);
    CCSize marginedSize = CCDirector::sharedDirector()->getWinSize() - CCSize(PADDING, PADDING);
    CCSize charSize = arrow->getCharSize();
    BetterTextArea* history = BetterTextArea::create(FONT, START_TEXT, CHAR_SCALE);
    CursorNode* cursor = CursorNode::create(charSize.width);

    history->setLinePadding(3);

    history->setTag(HISTORY);
    arrow->setTag(ARROW);
    input->setTag(INPUT);
    cursor->setTag(CURSOR);

    history->setAnchorPoint(CCPointZero);
    arrow->setAnchorPoint({ 0, 1 });
    input->setAnchorPoint({ 0, 1 });
    cursor->setAnchorPoint({ 0, 1 });

    arrow->setPosition({
        PADDING,
        marginedSize.height - history->getContentSize().height
    });
    history->setPosition({
        PADDING,
        arrow->getPositionY() - CHAR_SCALE
    });
    input->setPosition({
        arrow->getPositionX() + arrow->getContentSize().width * CHAR_SCALE,
        arrow->getPositionY()
    });
    cursor->setPosition({
        input->getPositionX(),
        input->getPositionY() - charSize.height - cursor->getContentSize().height
    });

    self->addChild(history);
    self->addChild(arrow);
    self->addChild(input);
    self->addChild(cursor);

    return true;
}