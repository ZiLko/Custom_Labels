#include "globals.hpp"
#include <Geode/ui/ColorPickPopup.hpp>

class SettingsLayer : public geode::Popup<> {
public:
    CCTextInputNode* labelNameInput = nullptr;

    CCLabelBMFont* posLabel = nullptr;
    CCLabelBMFont* fontLabel = nullptr;
    CCLabelBMFont* opacityLabel = nullptr;
    CCLabelBMFont* sizeLabel = nullptr;
    CCLabelBMFont* offsetXLabel = nullptr;
    CCLabelBMFont* offsetYLabel = nullptr;

    Slider* opacitySlider = nullptr;
    Slider* sizeSlider = nullptr;
    Slider* offsetYSlider = nullptr;
    Slider* offsetXSlider = nullptr;

    ColorChannelSprite* colorSprite = nullptr;

    int labelIndex;
    int fontIndex;
    int posIndex;

    void openColorPicker(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);

    void refreshList();
};

class DefaultLabelSettings : public SettingsLayer {
protected:
    bool setup() override;

    static DefaultLabelSettings* create(int labelIndex);
public:
    void saveSettings(CCObject*);
    static void openMenu(int labelIndex);
};

class CustomLabelSettings : public SettingsLayer {
    CCTextInputNode* customTextInput = nullptr;

protected:
    bool setup() override;

    static CustomLabelSettings* create(int labelIndex);
public:
    void saveSettings(CCObject*);
    static void openMenu(int labelIndex);
};

class ClicksLabelSettings : public SettingsLayer {
    CCMenuItemToggler* cpsOnlyToggle = nullptr;
    CCMenuItemToggler* totalClicksOnlyToggle = nullptr;

    bool showCPSOnly;
    bool showTotalClicksOnly;
protected:
    bool setup() override;

    static ClicksLabelSettings* create(int labelIndex);
public:
    void saveSettings(CCObject*);
    void toggleCPSOnly(CCObject*);
    void toggleTotalClicksOnly(CCObject*);
    static void openMenu(int labelIndex);
};

class TimeLabelSettings : public SettingsLayer {
    CCMenuItemToggler* attemptTimeToggle = nullptr;
    CCMenuItemToggler* sessionTimeToggle = nullptr;

    bool attemptTime;
    bool sessionTime;
protected:
    bool setup() override;

    static TimeLabelSettings* create(int labelIndex);

public:
    void saveSettings(CCObject*);
    void toggleAttemptTime(CCObject*);
    void toggleSessionTime(CCObject*);
    static void openMenu(int labelIndex);
};

class ClockLabelSettings : public SettingsLayer {
    CCMenuItemToggler* toggle12h = nullptr;
    CCMenuItemToggler* toggle24h = nullptr;

    bool format12H;
    bool format24H;

protected:
    bool setup() override;

    static ClockLabelSettings* create(int labelIndex);

public:
    void saveSettings(CCObject*);
    void toggle12H(CCObject*);
    void toggle24H(CCObject*);
    static void openMenu(int labelIndex);
};

class JumpsLabelSettings : public SettingsLayer {
    CCMenuItemToggler* attemptJumpsToggle = nullptr;
    CCMenuItemToggler* sessionJumpsToggle = nullptr;

    bool attemptJumps;
    bool sessionJumps;
protected:
    bool setup() override;

    static JumpsLabelSettings* create(int labelIndex);

public:
    
    void saveSettings(CCObject*);
    static void openMenu(int labelIndex);

    void toggleAttemptJumps(CCObject*);
    void toggleSessionJumps(CCObject*);

};