#pragma once

#include "../includes.hpp"
#include "../bindings/MenuLayerExtended.hpp"

DEFINE_HOOK(bool, MenuLayer, init) {
    std::cout << "Hello, world!" << std::endl;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenu* menu = CCMenu::create();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");

    menu->addChild(CCMenuItemSpriteExtra::create(sprite, self, menu_selector(MenuLayerExtended::onPlay)));
    menu->setPosition({ winSize.width / 2, winSize.height / 2 });
    self->addChild(menu);

    return true;
}

HOOK(0x1907B0, MenuLayer, init)