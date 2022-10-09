#pragma once

#include "../includes.hpp"
#include "../bindings/MenuLayerExtended.hpp"
#include "../utils/BetterTextArea.hpp"
#include "../configs/StaticConfig.hpp"

DEFINE_HOOK(bool, MenuLayer, init) {
    GameSoundManager::sharedState()->stopBackgroundMusic();
    GJAccountManager* account = GJAccountManager::sharedState();
    CCDirector* director = CCDirector::sharedDirector();
    CCSize winSize = director->getWinSize();
    CCSize marginedSize = winSize - CCSize(PADDING, PADDING);
    BetterTextArea<false>* history = BetterTextArea<false>::create(FONT, START_TEXT, CHAR_SCALE, marginedSize.width);
    CCLabelBMFont* arrow = CCLabelBMFont::create((account->m_sUsername + "> ").c_str(), FONT);
    CCTextInputNode* input = CCTextInputNode::create("", self, FONT, marginedSize.width, 10);

    history->setLinePadding(1);
    arrow->setScale(CHAR_SCALE);
    input->setMaxLabelScale(CHAR_SCALE);
    input->setAllowedChars(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\"'`<>()[]{}!?\\/.,:;+-*=");

    arrow->setAnchorPoint({ 0, 0.5f });
    input->m_pPlaceholderLabel->setAnchorPoint({ 0, 0.6f });
    input->m_pTextField->setAnchorPoint({ 0, 0.6f });

    const float historyHeight = history->getHeight() + history->getLinePadding() + history->getLineHeight();

    history->setPosition({ PADDING, marginedSize.height });
    arrow->setPosition({ PADDING, marginedSize.height - historyHeight });
    input->setPosition({ arrow->getContentSize().width * 0.45f, marginedSize.height - historyHeight + PADDING * 0.1f });

    self->addChild(history);
    self->addChild(arrow);
    self->addChild(input);

    return true;
}

HOOK(0x1907B0, MenuLayer, init)