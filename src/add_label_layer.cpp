#include "add_label_layer.hpp"

bool AddLabelLayer::setup(std::string const& value) {
    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    auto& lb = Labels::get();
    lb.typeIndex = 0;
    lb.posIndex = 2;

    auto inputBg = CCScale9Sprite::create("square02b_001.png", { 0, 0, 80, 80 });
    inputBg->setScale(0.7f);
    inputBg->setColor({ 0,0,0 });
    inputBg->setOpacity(75);
    inputBg->setPosition(winSize / 2 + ccp(0, 45));
    inputBg->setContentSize({ 235, 54 });

    labelNameInput = CCTextInputNode::create(150, 30, "Name", "bigFont.fnt");
    labelNameInput->m_textField->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->ignoreAnchorPointForPosition(true);
    labelNameInput->m_placeholderLabel->setAnchorPoint({ 0.5f, 0.5f });
    labelNameInput->setPosition(winSize / 2 + ccp(0, 45));
    labelNameInput->setMaxLabelScale(0.7f);
    labelNameInput->setLabelPlaceholderColor(ccc3(110, 119, 160));
    labelNameInput->setMouseEnabled(true);
    labelNameInput->setTouchEnabled(true);

    m_mainLayer->addChild(inputBg);
    m_mainLayer->addChild(labelNameInput);

    auto menu = CCMenu::create();
    menu->setPosition({ 0,0 });
    m_mainLayer->addChild(menu);

    auto title = CCLabelBMFont::create("Add Label", "bigFont.fnt");
    title->setPosition(winSize / 2 + ccp(0, 82));
    title->setScale(0.6f);
    m_mainLayer->addChild(title);

    title = CCLabelBMFont::create("Type", "goldFont.fnt");
    title->setPosition(winSize / 2 + ccp(-71, 0));
    title->setScale(0.825f);
    m_mainLayer->addChild(title);

    title = CCLabelBMFont::create("Pos", "goldFont.fnt");
    title->setPosition(winSize / 2 + ccp(71, 0));
    title->setScale(0.825f);
    m_mainLayer->addChild(title);

    typeLabel = CCLabelBMFont::create("Text", "bigFont.fnt");
    typeLabel->setPosition(winSize / 2 + ccp(-71, -34));
    typeLabel->setScale(0.475f);
    m_mainLayer->addChild(typeLabel);

    posLabel = CCLabelBMFont::create("Top Right", "bigFont.fnt");
    posLabel->setPosition(winSize / 2 + ccp(71, -34));
    posLabel->setScale(0.355f);
    m_mainLayer->addChild(posLabel);

    auto btnSpr = ButtonSprite::create("Add");
    btnSpr->setScale(0.9f);

    auto btn = CCMenuItemSpriteExtra::create(
        btnSpr,
        this,
        menu_selector(AddLabelLayer::addLabel)
    );
    btn->setPosition(winSize / 2 + ccp(0, -77));
    menu->addChild(btn);

    auto spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setFlipX(true);
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(AddLabelLayer::switchType)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(-18, -34));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(AddLabelLayer::switchType)
    );
    btn->setID("left");
    btn->setPosition(winSize / 2 + ccp(-123, -34));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setFlipX(true);
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(AddLabelLayer::switchPos)
    );
    btn->setID("right");
    btn->setPosition(winSize / 2 + ccp(123, -34));
    menu->addChild(btn);

    spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    spr->setScale(0.8f);

    btn = CCMenuItemSpriteExtra::create(
        spr,
        this,
        menu_selector(AddLabelLayer::switchPos)
    );
    btn->setID("left");
    btn->setPosition(winSize / 2 + ccp(18, -34));
    menu->addChild(btn);


    return true;
}

AddLabelLayer* AddLabelLayer::create() {
    auto ret = new AddLabelLayer();
    if (ret && ret->init(300, 206, "", "GJ_square02.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void AddLabelLayer::openMenu(CCObject*) {
    create()->show();
}

void AddLabelLayer::addLabel(CCObject*) {
    auto name = std::string(labelNameInput->getString());
    auto& lb = Labels::get();

    LabelSettings settings;

    settings.name = (name.length() < 1) ? "Unnamed Label" : name;
    settings.labelIndex = lb.labels.size();
    settings.posIndex = lb.posIndex;
    settings.typeIndex = lb.typeIndex;

    Label lbl;
    lbl.settings = settings;
    if (lb.typeIndex == 0 && name.length() >= 1) lbl.text = settings.name;
    lb.labels.push_back(lbl);
    keyBackClicked();

    CCArray* children = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCObject* child;
    CCARRAY_FOREACH(children, child) {
        CustomLabelsLayer* layer = dynamic_cast<CustomLabelsLayer*>(child);
        if (layer) {
            if (lb.labels.size() >= 5)
                lb.previousScroll = 0.f;

            layer->refresh(lb.labels.size() >= 5);
        }
    }

    Labels::addLabels();
    Labels::save();
}

void AddLabelLayer::switchType(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    lb.typeIndex += (id == "right") ? 1 : -1;

    if (lb.typeIndex == -1) lb.typeIndex = typesSize - 1;
    else if (lb.typeIndex == typesSize) lb.typeIndex = 0;

    typeLabel->setString(types[lb.typeIndex].c_str());
}

void AddLabelLayer::switchPos(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    lb.posIndex += (id == "right") ? 1 : -1;

    if (lb.posIndex == -1) lb.posIndex = 8;
    else if (lb.posIndex == 9) lb.posIndex = 0;

    posLabel->setString(positions[lb.posIndex].c_str());
}