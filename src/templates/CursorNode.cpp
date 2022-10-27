#include "CursorNode.hpp"

CursorNode* gd::CursorNode::create(float width) {
    CursorNode* instance = new CursorNode(width);

    if (instance) {
        instance->autorelease();

        return instance;
    } else {
        CC_SAFE_DELETE(instance);
        
        return nullptr;
    }
}

gd::CursorNode::CursorNode(float width) {
    this->m_delta = 0.0f;

    this->scheduleUpdate();
    this->setContentSize({ width, width / 2 });
}

void gd::CursorNode::draw() {
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ccDrawSolidRect({ 0, 0 }, this->getContentSize(), { 1.0f, 1.0f, 1.0f, 1.0f });
}

void gd::CursorNode::update(float delta) {
    this->m_delta += delta;

    if (this->m_delta >= 0.8f) {
        this->m_delta = 0.0f;

        this->setVisible(!this->isVisible());
    }
}