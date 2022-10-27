#pragma once

#include "../includes.hpp"

namespace gd {
    struct MonoSpaceLabel : public cocos2d::CCLabelBMFont {
        static MonoSpaceLabel* create(const char* font, const char* text, float scale);

        CCSize getCharSize(bool scale = true);
    private:
        bool init(const char* font, const char* text, float scale);
        void updateLabel() override;
    };
}