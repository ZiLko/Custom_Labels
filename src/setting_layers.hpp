#include "globals.hpp"
#include <Geode/ui/ColorPickPopup.hpp>

class CustomLabelSettings : public geode::Popup<> {
    CCTextInputNode* labelNameInput = nullptr;
    CCTextInputNode* customTextInput = nullptr;

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
protected:
    bool setup() override;

    static CustomLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);

    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);
};

class ClicksLabelSettings : public geode::Popup<> {
    CCMenuItemToggler* cpsOnlyToggle = nullptr;
    CCMenuItemToggler* totalClicksOnlyToggle = nullptr;

    CCTextInputNode* labelNameInput = nullptr;
    CCTextInputNode* customTextInput = nullptr;

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

    bool showCPSOnly;
    bool showTotalClicksOnly;
protected:
    bool setup() override;

    static ClicksLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);
    
    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);

    void toggleCPSOnly(CCObject*);
    void toggleTotalClicksOnly(CCObject*);
};

class AttemptsLabelSettings : public geode::Popup<> {
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
protected:
    bool setup() override;

    static AttemptsLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);

    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);
};

class TestmodeLabelSettings : public geode::Popup<> {
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
protected:
    bool setup() override;

    static TestmodeLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);

    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);
};

class TimeLabelSettings : public geode::Popup<> {
    CCMenuItemToggler* attemptTimeToggle = nullptr;
    CCMenuItemToggler* sessionTimeToggle = nullptr;

    CCTextInputNode* labelNameInput = nullptr;
    CCTextInputNode* customTextInput = nullptr;

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

    bool attemptTime;
    bool sessionTime;
protected:
    bool setup() override;

    static TimeLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);
    
    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);

    void toggleAttemptTime(CCObject*);
    void toggleSessionTime(CCObject*);
};

class ClockLabelSettings : public geode::Popup<> {
    CCMenuItemToggler* toggle12h = nullptr;
    CCMenuItemToggler* toggle24h = nullptr;

    CCTextInputNode* labelNameInput = nullptr;
    CCTextInputNode* customTextInput = nullptr;

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

    bool format12H;
    bool format24H;
protected:
    bool setup() override;

    static ClockLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);
    
    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);

    void toggle12H(CCObject*);
    void toggle24H(CCObject*);
};

class JumpsLabelSettings : public geode::Popup<> {
    CCMenuItemToggler* attemptJumpsToggle = nullptr;
    CCMenuItemToggler* sessionJumpsToggle = nullptr;

    CCTextInputNode* labelNameInput = nullptr;
    CCTextInputNode* customTextInput = nullptr;

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

    bool attemptJumps;
    bool sessionJumps;
protected:
    bool setup() override;

    static JumpsLabelSettings* create(int labelIndex);

public:
    static void openMenu(int labelIndex);
    void openColorPicker(CCObject*);
    
    void saveSettings(CCObject*);

    void switchPos(CCObject*);
    void switchFont(CCObject*);

    void updateOpacity(CCObject*);
    void updateSize(CCObject*);
    void updateOffsetX(CCObject*);
    void updateOffsetY(CCObject*);

    void toggleAttemptJumps(CCObject*);
    void toggleSessionJumps(CCObject*);
};