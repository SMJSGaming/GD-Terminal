#pragma once

#include <array>
#include "../includes.hpp"
#include "../bindings/MenuLayerExtended.hpp"
#include "../templates/Command.hpp"
#include "../templates/BetterTextArea.hpp"
#include "../templates/CursorNode.hpp"
#include "../configs/StaticConfig.hpp"

DEFINE_HOOK(bool, MenuLayer, init) {
    GameSoundManager::sharedState()->stopBackgroundMusic();
    CCSize marginedSize = CCDirector::sharedDirector()->getWinSize() - CCSize(PADDING, PADDING);
    BetterTextArea<false>* history = BetterTextArea<false>::create(FONT, START_TEXT, CHAR_SCALE, marginedSize.width);
    CCLabelBMFont* arrow = CCLabelBMFont::create((GJAccountManager::sharedState()->m_sUsername + ">").c_str(), FONT);
    CCLabelBMFont* input = CCLabelBMFont::create("", FONT);
    CCSize arrowSize = arrow->getContentSize();
    CCSize charSize = CCSize(arrowSize.width / strlen(arrow->getString()), arrowSize.height) * CHAR_SCALE;
    CursorNode* cursor = CursorNode::create(charSize.width);

    history->setLinePadding(1);

    history->setTag(HISTORY);
    arrow->setTag(ARROW);
    input->setTag(INPUT);
    input->setTag(CURSOR);

    arrow->setScale(CHAR_SCALE);
    input->setScale(CHAR_SCALE);

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
        arrow->getPositionX() + arrowSize.width * CHAR_SCALE,
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