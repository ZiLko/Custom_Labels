#pragma once

#include "globals.hpp"

class LabelCell : public CCNode {
    int labelIndex;
public:
    static LabelCell* create(std::string const& name, int const& labelIndex, int const& typeIndex, int const& posIndex);

    bool init(std::string const& name, int const& labelIndex, int const& typeIndex, int const& posIndex);

    void swapCells(CCObject* obj);

    void deleteLabel(CCObject*);

    void openLabelSettings(CCObject*);
};