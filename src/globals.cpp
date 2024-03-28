#include "globals.hpp"

std::string(*getText2[])(Labels&, PlayLayer*, const Label&) =
{ &LabelText::text, &LabelText::clicks, &LabelText::attempts,
&LabelText::testmode, &LabelText::time, &LabelText::clock,
&LabelText::jumps };

std::string Labels::getFont(int index) {
    if (index <= 1)
        return index == 0 ? "bigFont.fnt" : "chatFont.fnt";
    else if (index < 10) {
        return "gjFont0" + std::to_string(index) + ".fnt";
    }
    else {
        return "gjFont" + std::to_string(index) + ".fnt";
    }
}

void Labels::addLabels() {
    clear();

    PlayLayer* pl = PlayLayer::get();
    auto& lb = Labels::get();

    if (lb.labels.empty()) return;

    std::vector<Label> labelsInPos[9];

    for (const auto& element : lb.labels) {
        labelsInPos[element.settings.posIndex].push_back(element);
    }

    for (int i = 0; i < 9; i++) {
        if (labelsInPos[i].empty()) continue;

        std::sort(labelsInPos[i].begin(), labelsInPos[i].end());

        float accumulatedHeight = 0.f;
        for (const auto& element : labelsInPos[i]) {
            if (element.settings.typeIndex == TESTMODE && !pl->m_isTestMode) continue;

            std::string text = element.settings.typeIndex != FPS ? getText2[element.settings.typeIndex](lb, pl, element) : "0 FPS";

            CCLabelBMFont* lbl = CCLabelBMFont::create(text.c_str(), Labels::getFont(element.settings.fontIndex).c_str());
            lbl->setZOrder(10);
            lbl->setOpacity(element.settings.opacity / 100.f * 255.f);
            lbl->setScale(element.settings.size / 100.f);
            lbl->setColor(element.settings.color);

            auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
            switch (i) {
            case 0:
                lbl->setPosition(winSize / 2 + ccp(-winSize.width / 2, winSize.height / 2));
                lbl->setAnchorPoint({ 0.f, 0.f });
                break;
            case 1:
                lbl->setPosition(winSize / 2 + ccp(0, winSize.height / 2));
                lbl->setAnchorPoint({ 0.5f, 0.f });
                break;
            case 2:
                lbl->setPosition(winSize / 2 + ccp(winSize.width / 2, winSize.height / 2));
                lbl->setAnchorPoint({ 1.f, 0.f });
                break;
            case 3:
                lbl->setPosition(winSize / 2 + ccp(-winSize.width / 2, 0));
                lbl->setAnchorPoint({ 0.f, 0.5f });
                break;
            case 4:
                lbl->setPosition(winSize / 2);
                lbl->setAnchorPoint({ 0.5f, 0.5f });
                break;
            case 5:
                lbl->setPosition(winSize / 2 + ccp(winSize.width / 2, 0));
                lbl->setAnchorPoint({ 1.f, 0.5f });
                break;
            case 6:
                lbl->setPosition(ccp(5, 5));
                lbl->setAnchorPoint({ 0.f, 1.f });
                break;
            case 7:
                lbl->setPosition(winSize / 2 + ccp(0, -winSize.height / 2));
                lbl->setAnchorPoint({ 0.5f, 1.f });
                break;
            case 8:
                lbl->setPosition(winSize / 2 + ccp(winSize.width / 2, -winSize.height / 2));
                lbl->setAnchorPoint({ 1.f, 1.f });
                break;
            }

            int multiplierY = 1;
            if (i == 0 || i == 1 || i == 2) multiplierY = -1;
            else if (i == 3 || i == 4 || i == 5) multiplierY = 0;

            int multiplierX = 0;
            if (i == 0 || i == 3 || i == 6) multiplierX = 1;
            else if (i == 2 || i == 5 || i == 8) multiplierX = -1;

            accumulatedHeight += lbl->getContentSize().height * (element.settings.size / 100.f);

            lbl->setPosition(lbl->getPosition() + ccp(5 * multiplierX, accumulatedHeight * multiplierY) + ccp(element.settings.offsetX, element.settings.offsetY));

            lb.labelPointers[element.settings.typeIndex].push_back({ element, lbl });
            pl->addChild(lbl);
        }

    }
}

void Labels::clear() {
    auto& lb = Labels::get();
    for (int i = 0; i < typesSize; i++) {
        for (const auto& element : lb.labelPointers[i]) {
            element.pointer->removeFromParentAndCleanup(true);
            delete element.pointer;
        }
        lb.labelPointers[i].clear();
    }

    lb.currentCPS = 0;
    lb.queuedClicks.clear();
}

std::string LabelText::text(Labels& lb, PlayLayer* pl, const Label& element) {
    return element.text;
}

void Labels::save() {
    matjson::Value serializedData = matjson::Serialize<std::vector<Label>>::to_json(Labels::get().labels);
    Mod::get()->setSavedValue("data2", serializedData);
}

void Labels::load() {
    auto& lb = Labels::get();
    matjson::Value serializedData = Mod::get()->getSavedValue<matjson::Value>("data2");

    for (const auto& element : matjson::Serialize<std::vector<Label>>::from_json(serializedData)) {
        lb.labels.push_back(element);
    }
}

std::string LabelText::clicks(Labels& lb, PlayLayer* pl, const Label& element) {
    if (element.showCPSOnly)
        return std::to_string(lb.currentCPS) + " CPS";

    if (element.showTotalClicksOnly)
        return std::to_string(MBO(int, pl, 0x29a8)) + " Clicks";

    return std::to_string(lb.currentCPS) + "/" + std::to_string(MBO(int, pl, 0x29a8));
}

std::string LabelText::attempts(Labels& lb, PlayLayer* pl, const Label& element) {
    return "Attempt " + std::to_string(MBO(int, pl, 0x29ac));
}

std::string LabelText::testmode(Labels& lb, PlayLayer* pl, const Label& element) {
    return "Testmode";
}

std::string LabelText::time(Labels& lb, PlayLayer* pl, const Label& element) {
    float time = static_cast<float>(element.attemptTime ? MBO(double, pl, 0x2c20) : MBO(double, pl, 0x330));

    if (time >= 60 && time < 3600) {
        float minutes = time / 60.f;
        float seconds = (minutes - static_cast<int>(minutes)) * 60.f;

        return std::to_string(static_cast<int>(minutes)) + ":" + (seconds < 10 ? "0" : "") + std::to_string(static_cast<int>(seconds));
    }
    else if (time >= 3600) {
        float hours = time / 3600.f;
        float minutes = (hours - static_cast<int>(hours)) * 60.f;
        float seconds = (minutes - static_cast<int>(minutes)) * 60.f;

        return std::to_string(static_cast<int>(hours)) + ":" + std::to_string(static_cast<int>(minutes)) + ":" + (seconds < 10 ? "0" : "") + std::to_string(static_cast<int>(seconds));
    }
    else {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << time;

        return stream.str();
    }
}

std::string LabelText::clock(Labels& lb, PlayLayer* pl, const Label& element) {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream stream;
    stream << std::put_time(localTime, element.format24H ? "%H:%M:%S" : "%I:%M:%S %p");

    return stream.str();
}

std::string LabelText::jumps(Labels& lb, PlayLayer* pl, const Label& element) {
    return element.sessionJumps ? std::to_string(MBO(int, pl, 0x2ea4)) : std::to_string(MBO(int, pl, 0x2eac));
}