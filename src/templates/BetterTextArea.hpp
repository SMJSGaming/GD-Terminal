#pragma once

#include "../includes.hpp"

template<bool TTF>
using CCLabel = std::conditional_t<TTF, CCLabelTTF, CCLabelBMFont>;

template<bool TTF>
std::vector<CCLabel<TTF>*> _getLines(std::string font, std::string text, float scale, float padding) {
    std::vector<CCLabel<TTF>*> lines;
    std::stringstream stream(text);
    std::string line;

    for (float top = 0; std::getline(stream, line); top -= padding) {
        CCLabel<TTF>* label;

        if constexpr (TTF) {
            label = CCLabelTTF::create(line.c_str(), font.c_str(), scale);
        } else {
            label = CCLabelBMFont::create(line.c_str(), font.c_str());

            label->setScale(scale);
        }

        label->setAnchorPoint({ 0, 0.5f });
        label->setPosition({ 0, top });
        lines.push_back(label);

        top -= label->getContentSize().height * scale;
    }

    return lines;
}

template<bool TTF>
float _maxLineWidth(std::vector<CCLabel<TTF>*> lines) {
    return (*std::max_element(lines.begin(), lines.end(), [](CCLabel<TTF>* a, CCLabel<TTF>* b) {
        return a->getContentSize().width < b->getContentSize().width;
    }))->getContentSize().width;
}

namespace gd {
    template<bool TTF>
    struct BetterTextArea : public CCNode {

        static BetterTextArea* create(std::string font, std::string text, float scale) {
            std::vector<CCLabel<TTF>*> lines = _getLines<TTF>(font, text, scale, 0);

            return BetterTextArea::create<TTF>(font, text, lines, scale, _maxLineWidth<TTF>(lines), false, false);
        }

        static BetterTextArea* create(std::string font, std::string text, float scale, float width) {
            return BetterTextArea::create<TTF>(font, text, _getLines<TTF>(font, text, scale, 0), scale, width, true);
        }

        void setFont(std::string font) {
            this->m_font = font;

            this->updateContents();
        }

        std::string getFont() {
            return this->m_font;
        }

        void setText(std::string text) {
            this->m_text = text;

            this->updateContents();
        }

        std::string getText() {
            return this->m_text;
        }

        std::vector<CCLabel<TTF>*> getLines() {
            return this->m_lines;
        }

        void setWidth(float width) {
            this->m_artificialWidth = true;

            this->setContentSize({ width, this->getContentSize().height });
        }

        float getWidth() {
            return this->getContentSize().width;
        }

        float getHeight() {
            return this->getContentSize().height;
        }

        void setScale(float scale) {
            this->m_scale = scale;

            this->updateContents();
        }

        float getScale() {
            return this->m_scale;
        }

        float getLineHeight() {
            return this->m_lineHeight;
        }

        void setLinePadding(float padding) {
            this->m_linePadding = padding;

            this->updateContents();
        }

        float getLinePadding() {
            return this->m_linePadding;
        }

    private:
        template<bool TTF>
        static BetterTextArea* create(std::string font, std::string text, std::vector<CCLabel<TTF>*> lines, float scale, float width, bool artificialWidth) {
            BetterTextArea* textArea = new BetterTextArea<TTF>(font, text, lines, scale, width, artificialWidth);

            if (textArea) {
                textArea->autorelease();

                return textArea;
            } else {
                CC_SAFE_DELETE(textArea);
                
                return nullptr;
            }
        }

        std::string m_font;
        std::string m_text;
        std::vector<CCLabel<TTF>*> m_lines;
        float m_scale;
        float m_lineHeight;
        float m_linePadding;
        bool m_artificialWidth;

        BetterTextArea(std::string font, std::string text, std::vector<CCLabel<TTF>*> lines, float scale, float width, bool artificialWidth) {
            const unsigned int lineCount = lines.size();

            this->m_font = font;
            this->m_text = text;
            this->m_lines = lines;
            this->m_scale = scale;
            this->m_lineHeight = lines.back()->getContentSize().height * scale;
            this->m_linePadding = 0;
            this->m_artificialWidth = artificialWidth;

            this->setContentSize({ width, this->m_lineHeight * lineCount + this->m_linePadding * (lineCount - 1) });

            for (unsigned int i = 0; i < lineCount; i++) {
                this->addChild(this->m_lines.at(i));
            }
        }

        void updateContents() {
            this->m_lines = _getLines<TTF>(this->m_font, this->m_text, this->m_scale, this->m_linePadding);
            this->m_lineHeight = this->m_lines.back()->getContentSize().height * this->m_scale;

            const unsigned int lineCount = this->m_lines.size();

            this->setContentSize({
                this->m_artificialWidth ? this->getWidth(): _maxLineWidth<TTF>(this->m_lines),
                this->m_lineHeight * lineCount + this->m_linePadding * (lineCount - 1)
            });

            this->removeAllChildren();

            for (unsigned int i = 0; i < lineCount; i++) {
                this->addChild(this->m_lines.at(i));
            }
        }
    };
}