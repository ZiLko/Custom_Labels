#include "label_list_layer.hpp"
#include "custom_setting.hpp"

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>

std::string(*getText1[])(Labels&, PlayLayer*, const Label&) =
{ &LabelText::text, &LabelText::clicks, &LabelText::attempts,
&LabelText::testmode, &LabelText::time, &LabelText::clock,
&LabelText::jumps };

class $modify(PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
		if (!Mod::get()->getSettingValue<bool>("button_enabled")) return;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

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

		auto menu = this->getChildByID("left-button-menu");
		if (!menu) return;

		menu->addChild(btn);
		menu->updateLayout();
	}

	void onQuit(CCObject * sender) {
		PauseLayer::onQuit(sender);
		Labels::clear();
	}

	void goEdit() {
		PauseLayer::goEdit();
		Labels::clear();
	}

};

class $modify(EndLevelLayer) {
	void goEdit() {
		EndLevelLayer::goEdit();
		Labels::clear();
	}

	void onMenu(CCObject * s) {
		EndLevelLayer::onMenu(s);
		Labels::clear();
	}

};

class $modify(PlayLayer) {

	bool init(GJGameLevel * level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

		Labels::addLabels();

		return true;
	}

	void resetLevel() {
		PlayLayer::resetLevel();

		auto& lb = Labels::get();
		if (!lb.labelPointers[ATTEMPTS].empty()) {
			for (const auto& element : lb.labelPointers[ATTEMPTS]) {
				if (!element.pointer) continue;
				element.pointer->setString(getText1[ATTEMPTS](lb, this, element.label).c_str());
			}
		}
		if (!lb.labelPointers[CLICKS].empty()) {
			lb.currentCPS = 0;
			lb.queuedClicks.clear();
			for (const auto& element : lb.labelPointers[CLICKS]) {
				if (!element.pointer) continue;

				element.pointer->setColor(element.label.settings.color);

				std::string text = "";

				if (element.label.showCPSOnly)
					text = "0 CPS";
				else if (element.label.showTotalClicksOnly)
					text = std::to_string(MBO(int, this, 0x29a8)) + " Clicks";
				else
					text = "0/" + std::to_string(MBO(int, this, 0x29a8));

				element.pointer->setString(text.c_str());
			}
		}

		if (!lb.labelPointers[JUMPS].empty()) {
			MBO(int, this, 0x2eac) = 0;
			for (const auto& element : lb.labelPointers[JUMPS]) {
				if (!element.pointer) continue;
				element.pointer->setString(getText1[JUMPS](lb, this, element.label).c_str());
			}
		}
	}

	void incrementJumps() {
		PlayLayer::incrementJumps();

		auto& lb = Labels::get();
		if (lb.labelPointers[JUMPS].empty()) return;

		for (const auto& element : lb.labelPointers[JUMPS]) {
			if (!element.pointer) continue;

			element.pointer->setString(getText1[JUMPS](lb, this, element.label).c_str());
		}

	}

	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);

		auto& lb = Labels::get();

		if (!lb.labelPointers[TIME].empty()) {
			for (const auto& element : lb.labelPointers[TIME]) {
				if (!element.pointer) continue;

				element.pointer->setString(getText1[TIME](lb, this, element.label).c_str());
			}
		}

		if (!lb.labelPointers[CLOCK].empty()) {
			std::time_t currentTime = std::time(nullptr);
			std::tm* localTime = std::localtime(&currentTime);
			for (const auto& element : lb.labelPointers[CLOCK]) {
				if (!element.pointer) continue;

				element.pointer->setString(getText1[CLOCK](lb, this, element.label).c_str());
			}
		}

		if (!lb.labelPointers[CLICKS].empty()) {
			auto& vec = lb.queuedClicks;
			if (vec.empty()) return;

			for (int i = 0; i < vec.size(); i++) {
				if (GetTickCount() - vec[i] >= 1000) {
					lb.currentCPS--;
					vec.erase(vec.begin() + i);
				}
			}

			for (const auto& element : lb.labelPointers[CLICKS]) {
				if (!element.pointer) continue;

				element.pointer->setString(getText1[CLICKS](lb, this, element.label).c_str());
			}
		}
	}
};

class $modify(GJBaseGameLayer) {
	void handleButton(bool hold, int button, bool p1) {
		GJBaseGameLayer::handleButton(hold, button, p1);

		auto& lb = Labels::get();
		if (lb.labelPointers[CLICKS].empty()) return;

		bool summed = false;
		for (const auto& element : lb.labelPointers[CLICKS]) {
			auto col = element.label.settings.color;

			int rDiff = abs(col.r - 255);
			int gDiff = abs(col.g - 255);
			int bDiff = abs(col.b - 255);

			element.pointer->setColor(hold ? (rDiff + gDiff + bDiff <= 180 ? ccc3(84, 241, 36) : ccc3(255 - col.r, 255 - col.g, 255 - col.b)) : col);

			if (!hold) continue;

			if (!summed && !element.label.showTotalClicksOnly) {
				summed = true;
				lb.queuedClicks.push_back(GetTickCount());
				lb.currentCPS++;
			}

			element.pointer->setString(getText1[ATTEMPTS](lb, PlayLayer::get(), element.label).c_str());
		}
	}
};

class $modify(CCScheduler) {
	void update(float dt) {
		CCScheduler::update(dt);

		auto& lb = Labels::get();
		if (lb.labelPointers[FPS].empty()) return;

		if (GetTickCount() - lb.previousFPSUpdate < 500) return;
		lb.previousFPSUpdate = GetTickCount();
		float fps = 1.f / dt;
		int intFps = static_cast<int>(fps);
		std::string finalFps = (std::to_string(intFps + (fps - intFps > 0.7f ? 1 : 0)) + " FPS");

		for (const auto& element : lb.labelPointers[FPS]) {
			if (!element.pointer) continue;
			element.pointer->setString(finalFps.c_str());
		}
	}
};

$execute{
	Labels::load();
}

$on_mod(Loaded) {
	Mod::get()->addCustomSetting<ButtonCustomSettingValue>("button_menu", "none");
}