#include "BetterTextArea.hpp"

BetterTextArea* gd::BetterTextArea::create(const char* font, const char* text, float scale) {
    BetterTextArea* instance = new BetterTextArea(font, text, scale);

    if (instance && instance->init()) {
        instance->autorelease();

        return instance;
    } else {
        CC_SAFE_DELETE(instance);

        return nullptr;
    }
}

gd::BetterTextArea::BetterTextArea(const char* font, const char* text, float scale) {
    this->m_font = font;
    this->m_text = text;
    this->m_scale = scale;

    this->updateContents();
}

std::vector<gd::MonoSpaceLabel*> gd::BetterTextArea::getLines() {
    return this->m_lines;
}

CCSize gd::BetterTextArea::getCharSize(bool scale) {
    return MonoSpaceLabel::create("", this->m_font, this->m_scale)->getCharSize(scale);
}

void gd::BetterTextArea::pushLine(const char* text, bool update) {
    this->m_text.append("\n").append(text);

    if (update) {
        this->updateContents();
    }
}

void gd::BetterTextArea::setFont(const char* font) {
    this->m_font = font;

    this->updateContents();
}

const char* gd::BetterTextArea::getFont() {
    return this->m_font;
}

void gd::BetterTextArea::setString(const char* text) {
    this->m_text = text;

    this->updateContents();
}

const char* gd::BetterTextArea::getString() {
    return this->m_text.c_str();
}

void gd::BetterTextArea::setScale(float scale) {
    this->m_scale = scale;

    this->updateContents();
}

float gd::BetterTextArea::getScale() {
    return this->m_scale;
}

void gd::BetterTextArea::setLinePadding(float padding) {
    this->m_linePadding = padding;

    this->updateContents();
}

float gd::BetterTextArea::getLinePadding() {
    return this->m_linePadding;
}

void gd::BetterTextArea::updateContents() {
    CCSize charSize = this->getCharSize();
    std::stringstream stream(this->m_text);
    std::string line;

    this->m_lines.clear();

    while (std::getline(stream, line)) {
        MonoSpaceLabel* label = MonoSpaceLabel::create(line.c_str(), this->m_font, this->m_scale);

        label->setAnchorPoint({ 0, 0.5f });
        
        this->m_lines.push_back(label);
    }

    const unsigned int lineCount = this->m_lines.size();

    this->removeAllChildren();
    this->setContentSize({ 
        (*std::max_element(this->m_lines.begin(), this->m_lines.end(), [](MonoSpaceLabel* a, MonoSpaceLabel* b) {
            return a->getContentSize().width < b->getContentSize().width;
        }))->getContentSize().width * this->m_scale,
        charSize.height * lineCount + this->m_linePadding * (lineCount - 1)
    });

    for (unsigned int i = 0; i < lineCount; i++) {
        MonoSpaceLabel* label = this->m_lines.at(i);

        label->setPosition({ 0, this->getContentSize().height - charSize.height * i - this->m_linePadding * i });

        this->addChild(label);
    }
}