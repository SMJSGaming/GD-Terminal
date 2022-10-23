#pragma once

#include "../includes.hpp"

struct CursorNode : public CCNode {
    static CursorNode* create(float width);

    CursorNode(float width);
    void draw() override;
    void update(float delta) override;
private:
    float m_delta;
};