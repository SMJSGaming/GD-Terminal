#pragma once
#pragma warning( push )
#pragma warning( disable : 4251 )

#include <gd.h>
#include <cocos2d.h>

using namespace gd;
using namespace cocos2d;

namespace gd {
    struct MenuLayerExtended : public MenuLayer {
        void onPlay(CCObject* sender);
    };
}