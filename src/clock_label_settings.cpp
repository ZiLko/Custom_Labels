#include "setting_layers.hpp"
#include "label_list_layer.hpp"

bool ClockLabelSettings::setup() {
    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    auto& lb = Labels::get();
    auto sets = lb.labels[labelIndex].settings;
    fontIndex = sets.fontIndex;
    posIndex = sets.posIndex;

    format12H = lb.labels[labelIndex].format12H;
    format24H = lb.labels[labelIndex].format24H;

    this->setTitle("Label Settings");
    auto menu = CCMenu::create();
    menu->setPosition({ 0,0 });

    auto inputBg = CCScale9Sprite::create("square02b_001.png", { 0, 0, 80, 80 });
    inputBg->setScale(0.7f);
    inputBg->setColor({ 0,0,0 });
    inputBg->setOpacity(75);
    inputBg->setPosition(winSize / 2 + ccp(-90, 71));
    inputBg->setContentSize({ 235, 54 });

    labelNameInput = CCTextInputNode::create(150, 30, "Name", "bigFont.fnt");
    labelNameInput->m_textField->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->ignoreAnchorPointForPosition(true);
    labelNameInput->m_placeholderLabel->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->setPosition(winSize / 2 + ccp(-90, 71));
    labelNameInput->setMaxLabelScale(0.7f);
    labelNameInput->setLabelPlaceholderColor(ccc3(110, 119, 160));
    labelNameInput->setMouseEnabled(true);
    labelNameInput->setTouchEnabled(true);

    labelNameInput->setString(sets.name);

    auto title = CCLabelBMFont::create("Name", "bigFont.fnt");
    title->setScale(0.5f);
    title->setPosition(winSize / 2 + ccp(-90, 100));

    m_mainLayer->addChild(title);
    m_mainLayer->addChild(inputBg);
    m_mainLayer->addChild(labelNameInput);

    auto checkOffSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    auto checkOnSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

    auto label = CCLabelBMFont::create("12h Format", "bigFont.fnt");
    label->setScale(0.3f);
    label->setPosition(winSize / 2 + ccp(44, 63));
    m_mainLayer->addChild(label);

    toggle12h = CCMenuItemToggler::create(
        checkOffSprite,
        checkOnSprite,
        this,
        menu_selector(ClockLabelSettings::toggle12H)
    );

    toggle12h->setPosition(winSize / 2 + ccp(44, 86));
    toggle12h->setScale(0.85f);
    toggle12h->toggle(format12H);
    menu->addChild(toggle12h);

    label = CCLabelBMFont::create("24h Format", "bigFont.fnt");
    label->setScale(0.3f);
    label->setPosition(winSize / 2 + ccp(134, 63));
    m_mainLayer->addChild(label);

    toggle24h = CCMenuItemToggler::create(
        checkOffSprite,
        checkOnSprite,
        this,
        menu_selector(ClockLabelSettings::toggle24H)
    );

    toggle24h->setPosition(winSize / 2 + ccp(134, 86));
    toggle24h->setScale(0.85f);
    toggle24h->toggle(format24H);
    menu->addChild(toggle24h);

    auto btnSpr = ButtonSprite::create("Save");
    btnSpr->setScale(0.9f);

    auto btn = CCMenuItemSpriteExtra::create(
        btnSpr,
        this,
        menu_selector(ClockLabelSettings::saveSettings)
    );
    btn->setPosition(winSize / 2 + ccp(0, -118));

    m_mainLayer->addChild(menu);
    menu->addChild(btn);

    colorSprite = ColorChannelSprite::create();
    colorSprite->setColor(sets.color);
    colorSprite->setScale(0.65f);

    btn = CCMenuItemSpriteExtra::create(
        colorSprite,
        this,
        menu_selector(ClockLabelSettings::openColorPicker)
    );
    btn->setPosition(winSize / 2 + ccp(166, -116));
    menu->addChild(btn);

    title = CCLabelBMFont::create("Pos", "goldFont.fnt");
    title->setPosition(winSize / 2 + ccp(-90, 37));
    title->setScale(0.6f);
    m_mainLayer->addChild(title);

    posLabel = CCLabelBMFont::create(positions[sets.posIndex].c_str(), "bigFont.fnt");
    posLabel->setPosition(winSize / 2 + ccp(-90, 14));
    posLabel->setScale(0.355f);
    m_mainLayer->addChild(posLabel);

    auto spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setFlipX(true);
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(ClockLabelSettings::switchPos)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(-37, 14));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(ClockLabelSettings::switchPos)
    );
    btn->setID("left");
    btn->setPosition(winSize / 2 + ccp(-142, 14));
    menu->addChild(btn);

    title = CCLabelBMFont::create("Font", "goldFont.fnt");
    title->setPosition(winSize / 2 + ccp(-90, -12));
    title->setScale(0.6f);
    m_mainLayer->addChild(title);

    fontLabel = CCLabelBMFont::create(("Font " + std::to_string(fontIndex + 1)).c_str(), Labels::getFont(fontIndex).c_str());
    fontLabel->setPosition(winSize / 2 + ccp(-90, -35));
    fontLabel->setScale(0.455f);
    m_mainLayer->addChild(fontLabel);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setFlipX(true);
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(ClockLabelSettings::switchFont)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(-37, -35));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(ClockLabelSettings::switchFont)
    );
    btn->setID("left");
    btn->setPosition(winSize / 2 + ccp(-142, -35));
    menu->addChild(btn);

    opacityLabel = CCLabelBMFont::create(("Opacity (" + std::to_string(sets.opacity) + "%)").c_str(), "goldFont.fnt");
    opacityLabel->setPosition(winSize / 2 + ccp(90, 37));
    opacityLabel->setScale(0.6f);
    m_mainLayer->addChild(opacityLabel);

    opacitySlider = Slider::create(
        this,
        menu_selector(ClockLabelSettings::updateOpacity),
        0.8f
    );
    opacitySlider->setPosition(winSize / 2 + ccp(90, 18));
    opacitySlider->setAnchorPoint({ 0.f, 0.f });
    opacitySlider->setScale(0.8f);
    opacitySlider->setValue(sets.opacity / 100.f);
    menu->addChild(opacitySlider);

    sizeLabel = CCLabelBMFont::create(("Size (" + std::to_string(sets.size) + "%)").c_str(), "goldFont.fnt");
    sizeLabel->setPosition(winSize / 2 + ccp(90, -17));
    sizeLabel->setScale(0.6f);
    m_mainLayer->addChild(sizeLabel);

    sizeSlider = Slider::create(
        this,
        menu_selector(ClockLabelSettings::updateSize),
        0.8f
    );
    sizeSlider->setPosition(winSize / 2 + ccp(90, -36));
    sizeSlider->setAnchorPoint({ 0.f, 0.f });
    sizeSlider->setScale(0.8f);
    sizeSlider->setValue(sets.size / 500.f);
    menu->addChild(sizeSlider);

    offsetXLabel = CCLabelBMFont::create(("OffsetX (" + std::to_string(sets.offsetX) + "u)").c_str(), "goldFont.fnt");
    offsetXLabel->setPosition(winSize / 2 + ccp(-90, -70));
    offsetXLabel->setScale(0.6f);
    m_mainLayer->addChild(offsetXLabel);

    offsetXSlider = Slider::create(
        this,
        menu_selector(ClockLabelSettings::updateOffsetX),
        0.8f
    );
    offsetXSlider->setPosition(winSize / 2 + ccp(-90, -89));
    offsetXSlider->setAnchorPoint({ 0.f, 0.f });
    offsetXSlider->setScale(0.8f);
    offsetXSlider->setValue((sets.offsetX + 200.f) / 400.f);
    menu->addChild(offsetXSlider);

    offsetYLabel = CCLabelBMFont::create(("OffsetY (" + std::to_string(sets.offsetY) + "u)").c_str(), "goldFont.fnt");
    offsetYLabel->setPosition(winSize / 2 + ccp(90, -70));
    offsetYLabel->setScale(0.6f);
    m_mainLayer->addChild(offsetYLabel);

    offsetYSlider = Slider::create(
        this,
        menu_selector(ClockLabelSettings::updateOffsetY),
        0.8f
    );
    offsetYSlider->setPosition(winSize / 2 + ccp(90, -89));
    offsetYSlider->setAnchorPoint({ 0.f, 0.f });
    offsetYSlider->setScale(0.8f);
    offsetYSlider->setValue((sets.offsetY + 200.f) / 400.f);
    menu->addChild(offsetYSlider);

    menu->addChild(btn);
    return true;
}

ClockLabelSettings* ClockLabelSettings::create(int labelIndex) {
    auto ret = new ClockLabelSettings();
    ret->labelIndex = labelIndex;
    if (ret && ret->init(384, 286, "GJ_square02.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void ClockLabelSettings::openMenu(int labelIndex) {
    create(labelIndex)->show();
}

void ClockLabelSettings::updateOpacity(CCObject*) {
    opacityLabel->setString(("Opacity (" + std::to_string(static_cast<int>(opacitySlider->getThumb()->getValue() * 100)) + "%)").c_str());
}

void ClockLabelSettings::updateSize(CCObject*) {
    sizeLabel->setString(("Size (" + std::to_string(static_cast<int>(sizeSlider->getThumb()->getValue() * 500)) + "%)").c_str());
}

void ClockLabelSettings::updateOffsetX(CCObject*) {
    offsetXLabel->setString(("OffsetX (" + std::to_string(static_cast<int>((offsetXSlider->getThumb()->getValue() * 400.f) - 200.f)) + "u)").c_str());
}

void ClockLabelSettings::updateOffsetY(CCObject*) {
    offsetYLabel->setString(("OffsetY (" + std::to_string(static_cast<int>((offsetYSlider->getThumb()->getValue() * 400.f) - 200.f)) + "u)").c_str());
}

void ClockLabelSettings::switchPos(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    posIndex += (id == "right") ? 1 : -1;

    if (posIndex == -1) posIndex = 8;
    else if (posIndex == 9) posIndex = 0;

    posLabel->setString(positions[posIndex].c_str());
}

void ClockLabelSettings::switchFont(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    fontIndex += (id == "right") ? 1 : -1;

    if (fontIndex == 60) fontIndex = 0;
    if (fontIndex == -1) fontIndex = 59;

    fontLabel->removeFromParentAndCleanup(true);

    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

    fontLabel = CCLabelBMFont::create(("Font " + std::to_string(fontIndex + 1)).c_str(), Labels::getFont(fontIndex).c_str());
    fontLabel->setPosition(winSize / 2 + ccp(-90, -35));
    fontLabel->setScale(0.455f);
    m_mainLayer->addChild(fontLabel);
}

void ClockLabelSettings::saveSettings(CCObject*) {
    keyBackClicked();
    auto& lb = Labels::get();

    lb.labels[labelIndex].settings.name = (std::string(labelNameInput->getString()).length() < 1)
        ? lb.labels[labelIndex].settings.name : std::string(labelNameInput->getString());

    lb.labels[labelIndex].format12H = format12H;
    lb.labels[labelIndex].format24H = format24H;

    lb.labels[labelIndex].settings.posIndex = posIndex;

    lb.labels[labelIndex].settings.fontIndex = fontIndex;

    lb.labels[labelIndex].settings.opacity = static_cast<int>(opacitySlider->getThumb()->getValue() * 100);

    lb.labels[labelIndex].settings.size = static_cast<int>(sizeSlider->getThumb()->getValue() * 500);

    lb.labels[labelIndex].settings.offsetX = static_cast<int>((offsetXSlider->getThumb()->getValue() * 400.f) - 200.f);

    lb.labels[labelIndex].settings.offsetY = static_cast<int>((offsetYSlider->getThumb()->getValue() * 400.f) - 200.f);

    lb.labels[labelIndex].settings.color = colorSprite->getColor();

    CCArray* children = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCObject* child;
    CCARRAY_FOREACH(children, child) {
        CustomLabelsLayer* layer = dynamic_cast<CustomLabelsLayer*>(child);
        if (layer) {
            if (lb.labels.size() >= 5) {
                auto listLayer = static_cast<CCNode*>(layer->getChildren()->objectAtIndex(0))->getChildByID("GJCommentListLayer");
                auto listView = static_cast<CCNode*>(static_cast<CCNode*>(listLayer)->getChildren()->objectAtIndex(0));
                auto tableView = static_cast<CCNode*>(listView->getChildren()->objectAtIndex(0));
                auto contentLayer = static_cast<CCLayer*>(tableView->getChildren()->objectAtIndex(0));

                lb.previousScroll = contentLayer->getPositionY();
            }

            layer->refresh(lb.labels.size() >= 5);
        }
    }

    Labels::addLabels();
    Labels::save();
}

void ClockLabelSettings::openColorPicker(CCObject*) {
    auto popup = ColorPickPopup::create(colorSprite->getColor());
    popup->setColorTarget(colorSprite);
    popup->show();
}

void ClockLabelSettings::toggle12H(CCObject*) {
    if (format12H) {
        toggle12h->toggle(false);
    } else {
        format12H = true;
        toggle24h->toggle(false);
        format24H = false;
    }
}

void ClockLabelSettings::toggle24H(CCObject*) {
    if (format24H) {
        toggle24h->toggle(false);
    } else {
        format24H = true;
        toggle12h->toggle(false);
        format12H = false;
    }
}