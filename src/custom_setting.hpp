#include <Geode/loader/SettingNode.hpp>
#include "label_list_layer.hpp"

using namespace geode::prelude;

class ButtonCustomSettingValue;

class ButtonCustomSettingValue : public SettingValue {
protected:
    std::string m_placeholder;
public:
    ButtonCustomSettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
        : SettingValue(key, modID), m_placeholder(placeholder) {}

    bool load(matjson::Value const& json) override {
        return true;
    }

    bool save(matjson::Value& json) const override {
        return true;
    }

    SettingNode* createNode(float width) override;
};


class ButtonCustomSettingNode : public SettingNode {
protected:
    bool init(ButtonCustomSettingValue* value, float width) {
        if (!SettingNode::init(value))
            return false;

        this->setContentSize({ width, 35.f });
        auto menu = CCMenu::create();

        auto label = CCLabelBMFont::create("Open Labels Menu", "bigFont.fnt");
        label->setScale(0.58f);
        label->setPositionX(-154.f);
        label->setAnchorPoint({0.f, 0.5f});

        auto emptyBtn = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
		emptyBtn->setScale(0.70f);
		auto btnIcon = CCSprite::create("button.png"_spr);
		btnIcon->setPosition(emptyBtn->getContentSize() / 2 + ccp(1, 0));
		btnIcon->setScale(0.225f);
		emptyBtn->addChild(btnIcon);

		auto btn = CCMenuItemSpriteExtra::create(emptyBtn,
			this,
			menu_selector(CustomLabelsLayer::openMenu)
		);

        btn->setPositionX(143);

        menu->setPosition(width / 2, 18.f);
        menu->addChild(label);
        menu->addChild(btn);

        this->addChild(menu);

        return true;
    }

public:
    void onClickBtn(CCObject*);

    void commit() override {
        this->dispatchCommitted();
    }

    bool hasUncommittedChanges() override {
        return false;
    }

    bool hasNonDefaultValue() override {
        return true;
    }

    void resetToDefault() override {

    }

    static ButtonCustomSettingNode* create(ButtonCustomSettingValue* value, float width) {
        auto ret = new ButtonCustomSettingNode;
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

class SectionSettingValue : public SettingValue {
protected:
    std::string m_placeholder;
public:
    SectionSettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
        : SettingValue(key, modID), m_placeholder(placeholder) {}
    bool load(matjson::Value const& json) override { return true; }
    bool save(matjson::Value& json) const override { return true; }
    SettingNode* createNode(float width) override;
};

class SectionSettingNode : public SettingNode {
protected:
    bool init(SectionSettingValue* value, float width) {
        if (!SettingNode::init(value))
            return false;
        this->setContentSize({ width, 40.f });
        std::string name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");

        auto theMenu = CCMenu::create();
        auto theLabel = CCLabelBMFont::create(name.c_str(), "bigFont.fnt");

        theLabel->setScale(.5);
        theLabel->setPositionX(0);
        theMenu->addChild(theLabel);
        theMenu->setPosition(width / 2, 20.f);

        this->addChild(theMenu);

        return true;
    }

public:
    void commit() override {
        this->dispatchCommitted();
    }
    bool hasUncommittedChanges() override {
        return false;
    }
    bool hasNonDefaultValue() override {
        return true;
    }
    void resetToDefault() override {}

    static SectionSettingNode* create(SectionSettingValue* value, float width) {
        auto ret = new SectionSettingNode();
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};