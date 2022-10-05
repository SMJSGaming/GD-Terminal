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
    CCSize marginedSize = winSize - CCSize(5, 5);
    BetterTextArea<false>* history = BetterTextArea<false>::create(FONT, START_TEXT, CHAR_SCALE, marginedSize.width);
    CCSize historySize = history->getSize();
    CCLabelBMFont* arrow = CCLabelBMFont::create((account->m_sUsername + ">").c_str(), FONT);
    CCTextInputNode* input = CCTextInputNode::create("", self, FONT, marginedSize.width, 10);

    history->setLinePadding(1);
    arrow->setScale(CHAR_SCALE);
    input->setMaxLabelScale(CHAR_SCALE);
    input->setAllowedChars(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\"'`<>()[]{}!?\\/.,:;+-*=");

    history->setPosition({ 5, marginedSize.height });
    arrow->setPosition({ 5, marginedSize.height - historySize.height });
    input->setPosition({ 5.25f * (account->m_sUsername.length() + 2.0f), marginedSize.height - historySize.height });
    
    arrow->setAnchorPoint({ 0, 0.5f });
    input->m_pPlaceholderLabel->setAnchorPoint({ 0, 0.6f });
    input->m_pTextField->setAnchorPoint({ 0, 0.6f });

    self->addChild(history);
    //self->addChild(arrow);
    //self->addChild(input);

    return true;
}

HOOK(0x1907B0, MenuLayer, init)