#include "add_label_layer.hpp"

bool refreshed = false;

bool CustomLabelsLayer::setup(std::string const& value) {
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	this->setTitle("Custom Labels");
	CCPoint topLeftCorner = winSize / 2.f - ccp(m_size.width / 2.f, -m_size.height / 2.f);

	CCArray* labelCells = CCArray::create();
	for (const auto& element : Labels::get().labels) {
		auto sets = element.settings;
		labelCells->addObject(LabelCell::create(sets.name, sets.labelIndex, sets.typeIndex, sets.posIndex));
	}

	auto listView = ListView::create(labelCells, 35, 211, 155);
	auto tableView = static_cast<TableView*>(listView->getChildren()->objectAtIndex(0));
	auto contentLayer = static_cast<CCLayer*>(tableView->getChildren()->objectAtIndex(0));

	if (refreshed) {
		contentLayer->setPositionY(Labels::get().previousScroll);
		refreshed = false;
	}

	CCArray* children = contentLayer->getChildren();
	CCObject* child;
	int it = 0;
	CCARRAY_FOREACH(children, child) {
		GenericListCell* cell = dynamic_cast<GenericListCell*>(child);
		if (cell) {
			auto col = (it % 2 == 0) ? ccc3(20, 28, 78) : ccc3(20, 36, 87);
			it++;
			cell->m_backgroundLayer->setColor(col);
		}
	}

	auto listLayer = GJCommentListLayer::create(listView, "Custom Labels", { 255, 0, 0 }, 211, 155, true);
	listLayer->setPosition((winSize / 2) - (listLayer->getContentSize() / 2) - CCPoint((it >= 5) ? 6 : 0, 0));
	m_mainLayer->addChild(listLayer);

	listLayer->getChildByID("top-border")->setScaleX(0.62f);
	listLayer->getChildByID("top-border")->setScaleY(1.f);
	listLayer->getChildByID("top-border")->setPosition(ccp(105.25f, 150.f));

	listLayer->getChildByID("bottom-border")->setScaleX(0.62f);
	listLayer->getChildByID("bottom-border")->setScaleY(1.f);
	listLayer->getChildByID("top-border")->setPositionX(105.25f);

	listLayer->getChildByID("right-border")->setScaleX(0.8f);
	listLayer->getChildByID("right-border")->setPositionX(216);

	listLayer->getChildByID("left-border")->setScaleX(0.8f);
	listLayer->getChildByID("left-border")->setPositionX(-5.45);

	if (it >= 5) {
		auto scrollbar = Scrollbar::create(listView->m_tableView);
		scrollbar->setPosition({ (winSize.width / 2) + (listLayer->getScaledContentSize().width / 2) + 4, winSize.height / 2 });
		m_mainLayer->addChild(scrollbar);
	}

	auto icon = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
	icon->setScale(0.585f);
	auto btn = CCMenuItemSpriteExtra::create(
		icon,
		this,
		menu_selector(AddLabelLayer::openMenu)
	);
	btn->setPosition(ccp(110, -100));
	m_buttonMenu->addChild(btn);

	return true;
}

CustomLabelsLayer* CustomLabelsLayer::create() {
	auto ret = new CustomLabelsLayer();
	if (ret && ret->init(268, 250, "", "GJ_square02.png")) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void CustomLabelsLayer::openMenu(CCObject*) {
	auto layer = create();
	layer->m_noElasticity = true;
	layer->show();
}

void CustomLabelsLayer::refresh(bool keepScroll) {
	if (keepScroll) refreshed = true;
	this->keyBackClicked();
	openMenu(nullptr);
}