#include "setting_layers.hpp"
#include "label_list_layer.hpp"

void SettingsLayer::updateOpacity(CCObject*) {
    opacityLabel->setString(("Opacity (" + std::to_string(static_cast<int>(opacitySlider->getThumb()->getValue() * 100)) + "%)").c_str());
}

void SettingsLayer::updateSize(CCObject*) {
    sizeLabel->setString(("Size (" + std::to_string(static_cast<int>(sizeSlider->getThumb()->getValue() * 500)) + "%)").c_str());
}

void SettingsLayer::updateOffsetX(CCObject*) {
    offsetXLabel->setString(("OffsetX (" + std::to_string(static_cast<int>((offsetXSlider->getThumb()->getValue() * 400.f) - 200.f)) + "u)").c_str());
}

void SettingsLayer::updateOffsetY(CCObject*) {
    offsetYLabel->setString(("OffsetY (" + std::to_string(static_cast<int>((offsetYSlider->getThumb()->getValue() * 400.f) - 200.f)) + "u)").c_str());
}

void SettingsLayer::switchPos(CCObject* obj) {
    auto id = static_cast<CCNode*>(obj)->getID();
    auto& lb = Labels::get();

    posIndex += (id == "right") ? 1 : -1;

    if (posIndex == -1) posIndex = 8;
    else if (posIndex == 9) posIndex = 0;

    posLabel->setString(positions[posIndex].c_str());
}

void SettingsLayer::switchFont(CCObject* obj) {
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

void SettingsLayer::openColorPicker(CCObject*) {
    auto popup = ColorPickPopup::create(colorSprite->getColor());
    popup->setColorTarget(colorSprite);
    popup->show();
}

void SettingsLayer::refreshList() {
    auto& lb = Labels::get();
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