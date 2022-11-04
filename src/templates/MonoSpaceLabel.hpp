#pragma once

#include "../includes.hpp"

namespace gd {
    struct MonoSpaceLabel : public cocos2d::CCLabelBMFont {
        static MonoSpaceLabel* create(const char* text, const char* font, float scale = 1);

        CCSize getCharSize(bool scale = true);
    private:
        bool init(const char* text, const char* font, float scale);
        void updateLabel() override;
    };
}
