#include "label_list_layer.hpp"
#include "globals.hpp"

class AddLabelLayer : public geode::Popup<std::string const&> {
    
    CCTextInputNode* labelNameInput = nullptr;
    CCLabelBMFont* typeLabel = nullptr;
    CCLabelBMFont* posLabel = nullptr;

protected:

    bool setup(std::string const& value) override;
    static AddLabelLayer* create();

public:

	void openMenu(CCObject*);
    void addLabel(CCObject*);
    void switchType(CCObject*);
    void switchPos(CCObject*);
    
};
