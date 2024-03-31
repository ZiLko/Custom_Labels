#include "setting_layers.hpp"
#include "label_list_layer.hpp"

bool DefaultLabelSettings::setup() {
    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    auto& lb = Labels::get();
    auto sets = lb.labels[labelIndex].settings;
    fontIndex = sets.fontIndex;
    posIndex = sets.posIndex;

    this->setTitle("Label Settings");

    auto inputBg = CCScale9Sprite::create("square02b_001.png", { 0, 0, 80, 80 });
    inputBg->setScale(0.7f);
    inputBg->setColor({ 0,0,0 });
    inputBg->setOpacity(75);
    inputBg->setPosition(winSize / 2 + ccp(0, 71));
    inputBg->setContentSize({ 235, 54 });

    labelNameInput = CCTextInputNode::create(150, 30, "Name", "bigFont.fnt");
    labelNameInput->m_textField->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->ignoreAnchorPointForPosition(true);
    labelNameInput->m_placeholderLabel->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->setPosition(winSize / 2 + ccp(0, 71));
    labelNameInput->setMaxLabelScale(0.7f);
    labelNameInput->setLabelPlaceholderColor(ccc3(110, 119, 160));
    labelNameInput->setMouseEnabled(true);
    labelNameInput->setTouchEnabled(true);

    labelNameInput->setString(sets.name);

    auto title = CCLabelBMFont::create("Name", "bigFont.fnt");
    title->setScale(0.5f);
    title->setPosition(winSize / 2 + ccp(0, 100));

    m_mainLayer->addChild(title);
    m_mainLayer->addChild(inputBg);
    m_mainLayer->addChild(labelNameInput);

    auto btnSpr = ButtonSprite::create("Save");
    btnSpr->setScale(0.9f);

    auto btn = CCMenuItemSpriteExtra::create(
        btnSpr,
        this,
        menu_selector(DefaultLabelSettings::saveSettings)
    );
    btn->setPosition(winSize / 2 + ccp(0, -118));

    auto menu = CCMenu::create();
    menu->setPosition({ 0,0 });
    m_mainLayer->addChild(menu);
    menu->addChild(btn);

    colorSprite = ColorChannelSprite::create();
    colorSprite->setColor(sets.color);
    colorSprite->setScale(0.65f);

    btn = CCMenuItemSpriteExtra::create(
        colorSprite,
        this,
        menu_selector(DefaultLabelSettings::openColorPicker)
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
        menu_selector(DefaultLabelSettings::switchPos)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(-37, 14));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(DefaultLabelSettings::switchPos)
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
        menu_selector(DefaultLabelSettings::switchFont)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(-37, -35));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(DefaultLabelSettings::switchFont)
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
        menu_selector(DefaultLabelSettings::updateOpacity),
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
        menu_selector(DefaultLabelSettings::updateSize),
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
        menu_selector(DefaultLabelSettings::updateOffsetX),
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
        menu_selector(DefaultLabelSettings::updateOffsetY),
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

DefaultLabelSettings* DefaultLabelSettings::create(int labelIndex) {
    auto ret = new DefaultLabelSettings();
    ret->labelIndex = labelIndex;
    if (ret && ret->init(384, 286, "GJ_square02.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void DefaultLabelSettings::saveSettings(CCObject*) {
    keyBackClicked();
    auto& lb = Labels::get();

    lb.labels[labelIndex].settings.name = (std::string(labelNameInput->getString()).length() < 1)
        ? lb.labels[labelIndex].settings.name : std::string(labelNameInput->getString());

    lb.labels[labelIndex].settings.posIndex = posIndex;

    lb.labels[labelIndex].settings.fontIndex = fontIndex;

    lb.labels[labelIndex].settings.opacity = static_cast<int>(opacitySlider->getThumb()->getValue() * 100);

    lb.labels[labelIndex].settings.size = static_cast<int>(sizeSlider->getThumb()->getValue() * 500);

    lb.labels[labelIndex].settings.offsetX = static_cast<int>((offsetXSlider->getThumb()->getValue() * 400.f) - 200.f);

    lb.labels[labelIndex].settings.offsetY = static_cast<int>((offsetYSlider->getThumb()->getValue() * 400.f) - 200.f);

    lb.labels[labelIndex].settings.color = colorSprite->getColor();

    refreshList();
    Labels::addLabels();
    Labels::save();
}

void DefaultLabelSettings::openMenu(int labelIndex) {
    create(labelIndex)->show();
}