#pragma once

#include "../includes.hpp"
#include "../bindings/MenuLayerExtended.hpp"

DEFINE_HOOK(void, MenuLayer, draw) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenu* menu = CCMenu::create();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");

    menu->addChild(CCMenuItemSpriteExtra::create(sprite, self, menu_selector(MenuLayerExtended::onPlay)));
    menu->setPosition({ winSize.width / 2, winSize.height / 2 });
    self->addChild(menu);
}

HOOK(0x18FBB0, MenuLayer, draw)