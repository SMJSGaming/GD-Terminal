#pragma once

#include "../includes.hpp"

namespace gd {
    struct CursorNode : public CCNode {
        static CursorNode* create(float width);

        void draw() override;
        void update(float delta) override;
    private:
        float m_delta;

        CursorNode(float width);
    };
}