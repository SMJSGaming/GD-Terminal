#pragma once

#include "../includes.hpp"

DEFINE_HOOK(bool, MenuLayer, init) {
    GameSoundManager::sharedState()->stopBackgroundMusic();

    terminal::m_menuLayer = self;
    MonoSpaceLabel* input = MonoSpaceLabel::create("", FONT, CHAR_SCALE);
    MonoSpaceLabel* arrow = MonoSpaceLabel::create((GJAccountManager::sharedState()->m_sUsername + ">").c_str(), FONT, CHAR_SCALE);
    CCSize marginedSize = CCDirector::sharedDirector()->getWinSize() - CCSize(PADDING, PADDING);
    CCSize charSize = arrow->getCharSize();
    BetterTextArea<false>* history = BetterTextArea<false>::create(FONT, START_TEXT, CHAR_SCALE, marginedSize.width);
    CursorNode* cursor = CursorNode::create(charSize.width);

    history->setLinePadding(1);

    history->setTag(HISTORY);
    arrow->setTag(ARROW);
    input->setTag(INPUT);
    cursor->setTag(CURSOR);

    arrow->setAnchorPoint({ 0, 0.5f });
    input->setAnchorPoint({ 0, 0.5f });

    history->setPosition({
        PADDING,
        marginedSize.height
    });
    arrow->setPosition({
        PADDING,
        marginedSize.height - history->getHeight()
    });
    input->setPosition({
        arrow->getPositionX() + arrow->getContentSize().width * CHAR_SCALE,
        arrow->getPositionY()
    });
    cursor->setPosition({
        input->getPositionX(),
        input->getPositionY() - charSize.height * 0.5f
    });

    self->addChild(history);
    self->addChild(arrow);
    self->addChild(input);
    self->addChild(cursor);

    return true;
}

DEFINE_HOOK(void, MenuLayer, keyDown, enumKeyCodes key) {
    // Making it empty to stop the default behavior
}

GD_HOOK(0x1907B0, MenuLayer, init)
GD_HOOK(0x1922C0, MenuLayer, keyDown)