#pragma once

#include "../includes.hpp"

namespace gd {
    struct CursorNode : public CCNode {
        static CursorNode* create(float width);

        void toggle();
        void reset();
        void draw() override;
        void update(float delta) override;
    private:
        bool m_disabled;
        float m_delta;

        CursorNode(float width);
    };
}