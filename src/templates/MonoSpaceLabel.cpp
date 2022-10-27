#include "MonoSpaceLabel.hpp"

MonoSpaceLabel* gd::MonoSpaceLabel::create(const char* text, const char* font, float scale) {
    MonoSpaceLabel* instance = new MonoSpaceLabel();

    if (instance && instance->init(text, font, scale)) {
        instance->autorelease();

        return instance;
    } else {
        CC_SAFE_DELETE(instance);

        return nullptr;
    }
}

CCSize gd::MonoSpaceLabel::getCharSize(bool scale) {
    // H has an average character width making it perfect for reference
    return CCLabelBMFont::create("H", this->getFntFile())->getContentSize() * (scale ? this->getScale() : 1);
}

bool gd::MonoSpaceLabel::init(const char* text, const char* font, float scale) {
    const bool result = this->initWithString(text, font, -1, kCCTextAlignmentCenter);
    
    this->setScale(scale);

    return result;
}

void gd::MonoSpaceLabel::updateLabel() {
    this->CCLabelBMFont::updateLabel();

    CCSize charSize = this->getCharSize(false);
    unsigned int index = 0;
    CCObject* child;

    CCARRAY_FOREACH(m_pChildren, child) {
        CCSprite* sprite = static_cast<CCSprite*>(child);

        sprite->setPositionX(index++ * charSize.width);
    }

    this->setContentSize({ charSize.width * index, charSize.height });
}