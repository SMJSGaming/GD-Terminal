#pragma once

#include "../includes.hpp"

namespace gd {
    struct BetterTextArea : public CCNode {
        static BetterTextArea* create(const char* font, const char* text, float scale = 1);

        std::vector<MonoSpaceLabel*> getLines();
        CCSize getCharSize(bool scale = true);
        void pushLine(const char* text, bool update = true);
        void setFont(const char* font);
        const char* getFont();
        void setString(const char* text);
        const char* getString();
        void setScale(float scale);
        float getScale();
        void setLinePadding(float padding);
        float getLinePadding();
    private:
        std::vector<MonoSpaceLabel*> m_lines;
        std::string m_text;
        const char* m_font;
        float m_scale;
        float m_linePadding;

        BetterTextArea(const char* font, const char* text, float scale);
        void updateContents();
    };
}