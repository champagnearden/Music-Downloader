#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/utils/cocos.hpp>

#include <Geode/binding/LevelInfoLayer.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/binding/CustomSongWidget.hpp>

#include <string>

using namespace geode::prelude;

static CustomSongWidget *findCustomSongWidget(CCNode *root)
{
	if (!root)
		return nullptr;

	if (auto widget = typeinfo_cast<CustomSongWidget *>(root))
	{
		return widget;
	}

	for (auto child : root->getChildrenExt())
	{
		if (!child)
			continue;

		if (auto widget = findCustomSongWidget(child))
		{
			return widget;
		}
	}

	return nullptr;
}

static bool hasAudioAssets(GJGameLevel *level)
{
	if (!level)
		return false;

	return level->m_songID > 0 || !std::string(level->m_songIDs).empty() || !std::string(level->m_sfxIDs).empty();
}

static void refreshAndDownloadFromVisibleWidget(LevelInfoLayer *layer, GJGameLevel *level)
{
	if (!layer || !level)
	{
		log::error("Missing layer or level");
		return;
	}

	if (!hasAudioAssets(level))
	{
		log::info("No audio assets detected");
		return;
	}

	auto widget = findCustomSongWidget(layer);

	if (!widget)
	{
		log::error("Could not find visible CustomSongWidget on LevelInfoLayer");
		Notification::create("Could not find song widget")->show();
		return;
	}

	log::info("Using visible CustomSongWidget");
	log::info("Level: {}", level->m_levelName);
	log::info("songID={}", level->m_songID);
	log::info("songIDs raw='{}'", level->m_songIDs);
	log::info("sfxIDs raw='{}'", level->m_sfxIDs);

	widget->updateWithMultiAssets(
			level->m_songIDs,
			level->m_sfxIDs,
			0);

	widget->updateMultiAssetInfo(true);
	widget->updateSongInfo();
	widget->positionInfoObjects();

	Notification::create("Downloading level audio assets")->show();

	widget->onDownload(nullptr);

	layer->runAction(CCSequence::create(
			CCDelayTime::create(0.25f),
			CallFuncExt::create([widget]()
													{
            widget->updateMultiAssetInfo(true);
            widget->updateSongInfo();
            widget->positionInfoObjects();
            log::info("Refreshed visible song widget after starting download"); }),
			nullptr));
}

class $modify(AutoSongDownloadLevelInfoLayer, LevelInfoLayer)
{
	void levelDownloadFinished(GJGameLevel *level)
	{
		LevelInfoLayer::levelDownloadFinished(level);

		if (!level)
		{
			log::error("levelDownloadFinished: level is null");
			return;
		}

		this->runAction(CCSequence::create(
				CCDelayTime::create(0.25f),
				CallFuncExt::create([this, level]()
														{ refreshAndDownloadFromVisibleWidget(this, level); }),
				nullptr));
	}
};