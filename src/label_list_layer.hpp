#pragma once
#include "label_cell.hpp"

class CustomLabelsLayer : public geode::Popup<std::string const&> {
protected:
    bool setup(std::string const& value) override;

    static CustomLabelsLayer* create();

public:
	void openMenu(CCObject*);

    void refresh(bool keepScroll);
};
