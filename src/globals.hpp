#pragma once

#include <Geode/Geode.hpp>
#include <vector>
#include <ctime>

#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

using namespace geode::prelude;

const std::string positions[9] = {
    "Top Left", "Top Middle", "Top Right",
    "Middle Left", "Center", "Middle Right",
    "Bottom Left", "Bottom Mid", "Bottom Right"
};

const int typesSize = 8;
const std::string types[typesSize] = {
    "Text", "Clicks", "Attempts", "Testmode", "Time", "Clock", "Jumps", "FPS"
};

const int TEXT = 0;
const int CLICKS = 1;
const int ATTEMPTS = 2;
const int TESTMODE = 3;
const int TIME = 4;
const int CLOCK = 5;
const int JUMPS = 6;
const int FPS = 7;

struct LabelSettings {
    int labelIndex;
    int posIndex = 0;
    int typeIndex = 0;
    int fontIndex = 0;
    std::string name = "Unnamed Label";
    int offsetX = 0;
    int offsetY = 0;
    int size = 50;
    int opacity = 35;
    ccColor3B color = ccc3(255, 255, 255);
};

struct Label {
    LabelSettings settings;

    bool operator<(const Label& other) const {
        return settings.labelIndex < other.settings.labelIndex;
    }

    std::string text = "Custom Text";

    bool showCPSOnly = false;
    bool showTotalClicksOnly = false;

    bool attemptTime = true;
    bool sessionTime = false;

    bool attemptJumps = true;
    bool sessionJumps = false;

    bool format12H = true;
    bool format24H = false;
};

struct LabelPointer {
    Label label;
    CCLabelBMFont* pointer;
};

class Labels {

    Labels() {}

public:

    int typeIndex = 0;
    int posIndex = 0;
    int currentCPS = 0;
    DWORD previousFPSUpdate = 0;

    float previousScroll = 0.f;

    std::vector<Label> labels;
    std::vector<LabelPointer> labelPointers[typesSize];
    std::vector<DWORD> queuedClicks;

    static auto& get() {
        static Labels instance;
        return instance;
    }

    static std::string getFont(int index);

    static void addLabels();

    static void clear();

    static void save();

    static void load();

};

class LabelText {
public:

    static std::string text(Labels& lb, PlayLayer* pl, const Label& element);
    
    static std::string clicks(Labels& lb, PlayLayer* pl, const Label& element);

    static std::string attempts(Labels& lb, PlayLayer* pl, const Label& element);

    static std::string testmode(Labels& lb, PlayLayer* pl, const Label& element);

    static std::string time(Labels& lb, PlayLayer* pl, const Label& element);

    static std::string clock(Labels& lb, PlayLayer* pl, const Label& element);

    static std::string jumps(Labels& lb, PlayLayer* pl, const Label& element);

};

template<>
struct matjson::Serialize<LabelSettings> {
    static LabelSettings from_json(matjson::Value const& value) {
        LabelSettings settings;
        settings.labelIndex = value["labelIndex"].as_int();
        settings.posIndex = value["posIndex"].as_int();
        settings.typeIndex = value["typeIndex"].as_int();
        settings.fontIndex = value["fontIndex"].as_int();
        settings.name = value["name"].as_string();
        settings.offsetX = value["offsetX"].as_int();
        settings.offsetY = value["offsetY"].as_int();
        settings.size = value["size"].as_int();
        settings.opacity = value["opacity"].as_int();
        settings.color = ccc3(value["colorR"].as_int(), value["colorG"].as_int(), value["colorB"].as_int());
        return settings;
    }

    static matjson::Value to_json(LabelSettings const& settings) {
        auto obj = matjson::Object();
        obj["labelIndex"] = settings.labelIndex;
        obj["posIndex"] = settings.posIndex;
        obj["typeIndex"] = settings.typeIndex;
        obj["fontIndex"] = settings.fontIndex;
        obj["name"] = settings.name;
        obj["offsetX"] = settings.offsetX;
        obj["offsetY"] = settings.offsetY;
        obj["size"] = settings.size;
        obj["opacity"] = settings.opacity;
        obj["colorR"] = settings.color.r;
        obj["colorG"] = settings.color.g;
        obj["colorB"] = settings.color.b;
        return obj;
    }
};

template<>
struct matjson::Serialize<Label> {
    static Label from_json(matjson::Value const& value) {
        Label label;
        label.settings = matjson::Serialize<LabelSettings>::from_json(value["settings"]);
        label.text = value["text"].as_string();
        label.showCPSOnly = value["showCPSOnly"].as_bool();
        label.showTotalClicksOnly = value["showTotalClicksOnly"].as_bool();
        label.attemptTime = value["attemptTime"].as_bool();
        label.sessionTime = value["sessionTime"].as_bool();
        label.attemptJumps = value["attemptJumps"].as_bool();
        label.sessionJumps = value["sessionJumps"].as_bool();
        label.format12H = value["format12H"].as_bool();
        label.format24H = value["format24H"].as_bool();
        return label;
    }

    static matjson::Value to_json(Label const& label) {
        auto obj = matjson::Object();
        obj["settings"] = matjson::Serialize<LabelSettings>::to_json(label.settings);
        obj["text"] = label.text;
        obj["showCPSOnly"] = label.showCPSOnly;
        obj["showTotalClicksOnly"] = label.showTotalClicksOnly;
        obj["attemptTime"] = label.attemptTime;
        obj["sessionTime"] = label.sessionTime;
        obj["attemptJumps"] = label.attemptJumps;
        obj["sessionJumps"] = label.sessionJumps;
        obj["format12H"] = label.format12H;
        obj["format24H"] = label.format24H;
        return obj;
    }
};

template<>
struct matjson::Serialize<std::vector<Label>> {
    static std::vector<Label> from_json(matjson::Value const& value) {
        std::vector<Label> result;
        for (auto const& element : value.as_array()) {
            result.push_back(matjson::Serialize<Label>::from_json(element));
        }
        return result;
    }

    static matjson::Value to_json(std::vector<Label> const& value) {
        auto array = matjson::Array();
        for (auto const& element : value) {
            array.push_back(matjson::Serialize<Label>::to_json(element));
        }
        return array;
    }
};
