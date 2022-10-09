#pragma once
#pragma warning( push )
#pragma warning( disable : 4251 )

#include <gd.h>
#include <cocos2d.h>

using namespace gd;
using namespace cocos2d;
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

        void setFont(std::string text) {
            this->font = font;

            this->updateContents();
        }

        std::string getFont() {
            return this->font;
        }

        void setText(std::string text) {
            this->text = text;

            this->updateContents();
        }

        std::string getText() {
            return this->text;
        }

        std::vector<CCLabel<TTF>*> getLines() {
            return this->lines;
        }

        void setWidth(float width) {
            this->artificialWidth = true;

            this->setContentSize({ width, this->getContentSize().height });
        }

        float getWidth() {
            return this->getContentSize().width;
        }

        float getHeight() {
            return this->getContentSize().height;
        }

        void setScale(float scale) {
            this->scale = scale;

            this->updateContents();
        }

        float getScale() {
            return this->scale;
        }

        float getLineHeight() {
            return this->lineHeight;
        }

        void setLinePadding(float padding) {
            this->linePadding = padding;

            this->updateContents();
        }

        float getLinePadding() {
            return this->linePadding;
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

        std::string font;
        std::string text;
        std::vector<CCLabel<TTF>*> lines;
        float scale;
        float lineHeight;
        float linePadding;
        bool artificialWidth;
        bool ttf;

        BetterTextArea(std::string font, std::string text, std::vector<CCLabel<TTF>*> lines, float scale, float width, bool artificialWidth) {
            const unsigned int lineCount = lines.size();

            this->font = font;
            this->text = text;
            this->lines = lines;
            this->scale = scale;
            this->lineHeight = lines.back()->getContentSize().height * scale;
            this->linePadding = 0;
            this->artificialWidth = artificialWidth;

            this->setContentSize({ width, this->lineHeight * lineCount + this->linePadding * (lineCount - 1) });

            for (unsigned int i = 0; i < lineCount; i++) {
                this->addChild(lines.at(i));
            }
        }

        void updateContents() {
            this->lines = _getLines<TTF>(this->font, this->text, this->scale, this->linePadding);
            this->lineHeight = this->lines.back()->getContentSize().height * this->scale;

            const unsigned int lineCount = this->lines.size();

            this->setContentSize({
                this->artificialWidth ? this->getWidth(): _maxLineWidth<TTF>(this->lines),
                this->lineHeight * lineCount + this->linePadding * (lineCount - 1)
            });

            this->removeAllChildren();

            for (unsigned int i = 0; i < lineCount; i++) {
                this->addChild(lines.at(i));
            }
        }
    };
}