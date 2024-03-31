#include "setting_layers.hpp"
#include "label_cell.hpp"
#include "label_list_layer.hpp"

void refresh(Labels& lb) {
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
}

bool LabelCell::init(std::string const& name, int const& labelIndex, int const& typeIndex, int const& posIndex) {
    this->labelIndex = labelIndex;

    auto nameLabel = CCLabelBMFont::create(name.c_str(), "chatFont.fnt");
    nameLabel->setPosition({ 75, 23 });
    nameLabel->setScale(0.675f);
    this->addChild(nameLabel);

    auto typeLabel = CCLabelBMFont::create(("Type: " + types[typeIndex]).c_str(), "chatFont.fnt");
    typeLabel->setPosition({ 34, 8 });
    typeLabel->setScale(0.475f);
    typeLabel->setSkewX(12);
    typeLabel->setOpacity(90);
    this->addChild(typeLabel);

    auto posLabel = CCLabelBMFont::create(("Pos: " + positions[posIndex]).c_str(), "chatFont.fnt");
    posLabel->setPosition({ 111, 8 });
    posLabel->setScale(0.475f);
    posLabel->setSkewX(12);
    posLabel->setOpacity(90);
    this->addChild(posLabel);

    auto separatorLabel = CCLabelBMFont::create("|", "chatFont.fnt");
    separatorLabel->setPosition({ 72, 8 });
    separatorLabel->setScale(0.475f);
    separatorLabel->setOpacity(90);
    this->addChild(separatorLabel);

    auto menu = CCMenu::create();
    menu->setPosition({ 0,0 });

    auto icon = CCSprite::createWithSpriteFrameName("edit_leftBtn_001.png");
    icon->setScale(0.7f);
    icon->setRotation(90);
    icon->setOpacity(102);
    auto btn = CCMenuItemSpriteExtra::create(
        icon,
        this,
        menu_selector(LabelCell::swapCells)
    );
    btn->setID("up");
    btn->setPosition(ccp(152, ((labelIndex != Labels::get().labels.size() - 1) ? 26 : 18)));
    if (labelIndex != 0) menu->addChild(btn);

    icon = CCSprite::createWithSpriteFrameName("edit_leftBtn_001.png");
    icon->setScale(0.7f);
    icon->setOpacity(102);
    icon->setRotation(-90);
    btn = CCMenuItemSpriteExtra::create(
        icon,
        this,
        menu_selector(LabelCell::swapCells)
    );
    btn->setID("down");
    btn->setPosition(ccp(152, ((labelIndex != 0) ? 8 : 18)));
    if (labelIndex != Labels::get().labels.size() - 1) menu->addChild(btn);

    icon = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
    icon->setScale(0.39f);
    btn = CCMenuItemSpriteExtra::create(
        icon,
        this,
        menu_selector(LabelCell::openLabelSettings)
    );
    btn->setPosition(ccp(195, 18));
    menu->addChild(btn);

    icon = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
    icon->setScale(0.39f);
    btn = CCMenuItemSpriteExtra::create(
        icon,
        this,
        menu_selector(LabelCell::deleteLabel)
    );
    btn->setPosition(ccp(174, 18));
    menu->addChild(btn);

    this->addChild(menu);
    return true;
}

LabelCell* LabelCell::create(std::string const& name, int const& labelIndex, int const& typeIndex, int const& posIndex) {
    auto ret = new LabelCell();
    if (ret && ret->init(name, labelIndex, typeIndex, posIndex)) {
        ret->autorelease();
    }
    else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void LabelCell::swapCells(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    int direction = (id == "up") ? -1 : 1;

    auto temp = lb.labels[labelIndex];
    lb.labels[labelIndex] = lb.labels[labelIndex + direction];
    lb.labels[labelIndex + direction] = temp;

    lb.labels[labelIndex].settings.labelIndex = labelIndex;
    lb.labels[labelIndex + direction].settings.labelIndex = labelIndex + direction;
    
    refresh(lb);
    Labels::addLabels();
    Labels::save();
}

void LabelCell::deleteLabel(CCObject*) {
    auto& lb = Labels::get();

    lb.labels.erase(lb.labels.begin() + labelIndex);

    for (int i = labelIndex; i < lb.labels.size(); i++) {
        lb.labels[i].settings.labelIndex--;
    }

    refresh(lb);
    Labels::addLabels();
    Labels::save();
}

void LabelCell::openLabelSettings(CCObject*) {
    switch (Labels::get().labels[labelIndex].settings.typeIndex) {
        case TEXT:
            CustomLabelSettings::openMenu(labelIndex);
        break;
        case CLICKS:
            ClicksLabelSettings::openMenu(labelIndex);
        break;
        case TIME:
            TimeLabelSettings::openMenu(labelIndex);
        break;
        case CLOCK:
            ClockLabelSettings::openMenu(labelIndex);
        break;
        case JUMPS:
            JumpsLabelSettings::openMenu(labelIndex);
        break;
        case ATTEMPTS:
        case TESTMODE:
        case FPS:
        default:
            DefaultLabelSettings::openMenu(labelIndex); 
        break;
    }
}