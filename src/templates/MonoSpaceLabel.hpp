#pragma once
#pragma warning( push )
#pragma warning( disable : 4251 )

#include <gd.h>
#include <cocos2d.h>

using namespace gd;
using namespace cocos2d;

namespace gd {
    struct MonoSpaceLabel : public cocos2d::CCLabelBMFont {
        static MonoSpaceLabel* create(const char* text, const char* font, float scale = 1);

        CCSize getCharSize(bool scale = true);
    private:
        bool init(const char* text, const char* font, float scale);
        void updateLabel() override;
    };
}

#pragma warning( pop )