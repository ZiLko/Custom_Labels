#include "custom_setting.hpp"

using namespace geode::prelude;

SettingNode* SectionSettingValue::createNode(float width) {
    return SectionSettingNode::create(this, width);
}

SettingNode* ButtonCustomSettingValue::createNode(float width) {
    return ButtonCustomSettingNode::create(this, width);
}
