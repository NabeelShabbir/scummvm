/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "gui/gui-manager.h"
#include "gui/widget.h"
#include "gui/widgets/edittext.h"
#include "gui/widgets/popup.h"
#include "gui/ThemeEval.h"

#include "common/translation.h"
#include "common/savefile.h"
#include "backends/keymapper/keymapper.h"
#include "backends/keymapper/action.h"
#include "graphics/scaler.h"
#include "image/png.h"
#include "twp/metaengine.h"
#include "twp/detection.h"
#include "twp/twp.h"
#include "twp/savegame.h"
#include "twp/time.h"
#include "twp/actions.h"
#include "twp/dialogs.h"

#define MAX_SAVES 99

namespace Twp {

static const ADExtraGuiOptionsMap optionsList[] = {
	{GAMEOPTION_ORIGINAL_SAVELOAD,
	 {_s("Use original save/load screens"),
	  _s("Use the original save/load screens instead of the ScummVM ones"),
	  "original_menus",
	  false,
	  0,
	  0}},
	AD_EXTRA_GUI_OPTIONS_TERMINATOR};

} // End of namespace Twp

const char *TwpMetaEngine::getName() const {
	return "twp";
}

const ADExtraGuiOptionsMap *TwpMetaEngine::getAdvancedExtraGuiOptions() const {
	return Twp::optionsList;
}

Common::Error TwpMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	*engine = new Twp::TwpEngine(syst, desc);
	return Common::kNoError;
}

bool TwpMetaEngine::hasFeature(MetaEngineFeature f) const {
	return checkExtendedSaves(f) ||
		   (f == kSupportsLoadingDuringStartup);
}

int TwpMetaEngine::getMaximumSaveSlot() const {
	return MAX_SAVES;
}

void TwpMetaEngine::registerDefaultSettings(const Common::String &) const {
	ConfMan.registerDefault("toiletPaperOver", false);
	ConfMan.registerDefault("annoyingInJokes", false);
	ConfMan.registerDefault("invertVerbHighlight", false);
	ConfMan.registerDefault("retroFonts", false);
	ConfMan.registerDefault("retroVerbs", false);
	ConfMan.registerDefault("hudSentence", false);
	ConfMan.registerDefault("talkiesShowText", true);
	ConfMan.registerDefault("talkiesHearVoice", true);
	ConfMan.registerDefault("language", "en");
}

static Common::String getDesc(const Twp::SaveGame& savegame) {
	Common::String desc = Twp::formatTime(savegame.time, "%b %d at %H:%M");
	if (savegame.easyMode)
		desc += " (casual)";
	return desc;
}

SaveStateDescriptor TwpMetaEngine::querySaveMetaInfos(const char *target, int slot) const {
	Common::String filename = Common::String::format("%s%02d.save", target, slot);
	Common::InSaveFile *f = g_system->getSavefileManager()->openForLoading(filename);

	if (f) {

		Common::InSaveFile *thumbnailFile = g_system->getSavefileManager()->openForLoading(Common::String::format("%s%02d.png", target, slot));

		// Create the return descriptor
		SaveStateDescriptor desc(this, slot, "?");

		if (thumbnailFile) {
			Image::PNGDecoder png;
			if (png.loadStream(*thumbnailFile)) {
				Graphics::ManagedSurface *thumbnail = new Graphics::ManagedSurface();
				thumbnail->copyFrom(*png.getSurface());
				Graphics::Surface *thumbnailSmall = new Graphics::Surface();
				createThumbnail(thumbnailSmall, thumbnail);
				desc.setThumbnail(thumbnailSmall);
			}
		}
		Twp::SaveGame savegame;
		Twp::SaveGameManager::getSaveGame(f, savegame);
		Common::String time = getDesc(savegame);

		desc.setDescription(time);
		desc.setPlayTime(savegame.gameTime * 1000);
		Twp::DateTime dt = Twp::toDateTime(savegame.time);
		desc.setSaveDate(dt.year, dt.month, dt.day);
		desc.setSaveTime(dt.hour, dt.min);

		return desc;
	}

	return SaveStateDescriptor();
}

SaveStateList TwpMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	Common::StringArray filenames;
	Common::String saveDesc;
	Common::String pattern = Common::String::format("%s##.save", target);

	filenames = saveFileMan->listSavefiles(pattern);

	SaveStateList saveList;
	for (Common::StringArray::const_iterator file = filenames.begin(); file != filenames.end(); ++file) {
		const char *ext = strrchr(file->c_str(), '.');
		int slot = ext ? atoi(ext - 2) : -1;

		if (slot >= 0 && slot <= MAX_SAVES) {
			Common::InSaveFile *in = g_system->getSavefileManager()->openForLoading(*file);

			if (in) {
				Twp::SaveGame savegame;
				Twp::SaveGameManager::getSaveGame(in, savegame);
				Common::String time = getDesc(savegame);
				saveList.push_back(SaveStateDescriptor(this, slot, time));
			}
		}
	}

	// Sort saves based on slot number.
	Common::sort(saveList.begin(), saveList.end(), SaveStateDescriptorSlotComparator());
	return saveList;
}

GUI::OptionsContainerWidget *TwpMetaEngine::buildEngineOptionsWidget(GUI::GuiObject *boss, const Common::String &name, const Common::String &target) const {
	GUI::OptionsContainerWidget *widget = new Twp::TwpOptionsContainerWidget(boss, name, target);
	return widget;
}

Common::Array<Common::Keymap *> TwpMetaEngine::initKeymaps(const char *target) const {
	Common::Keymap *engineKeyMap = new Common::Keymap(Common::Keymap::kKeymapTypeGame, target, "Thimbleweed Park keymap");

	Common::Action *act;

	struct {
		Common::String name;
		const Common::U32String desc;
		Twp::TwpAction action;
		Common::String input;
	} actions[] = {
		{"SKIPCUTSCENE", _("Skip cutscene"), Twp::kSkipCutscene, "ESCAPE"},
		{"SELECTACTOR1", _("Select Actor 1"), Twp::kSelectActor1, "1"},
		{"SELECTACTOR2", _("Select Actor 2"), Twp::kSelectActor2, "2"},
		{"SELECTACTOR3", _("Select Actor 3"), Twp::kSelectActor3, "3"},
		{"SELECTACTOR4", _("Select Actor 4"), Twp::kSelectActor4, "4"},
		{"SELECTACTOR5", _("Select Actor 5"), Twp::kSelectActor5, "5"},
		{"SELECTACTOR6", _("Select Actor 6"), Twp::kSelectActor6, "6"},
		{"SELECTCHOICE1", _("Select Choice 1"), Twp::kSelectChoice1, "1"},
		{"SELECTCHOICE2", _("Select Choice 2"), Twp::kSelectChoice2, "2"},
		{"SELECTCHOICE3", _("Select Choice 3"), Twp::kSelectChoice3, "3"},
		{"SELECTCHOICE4", _("Select Choice 4"), Twp::kSelectChoice4, "4"},
		{"SELECTCHOICE5", _("Select Choice 5"), Twp::kSelectChoice5, "5"},
		{"SELECTCHOICE6", _("Select Choice 6"), Twp::kSelectChoice6, "6"},
		{"SELECTNEXTACTOR", _("Select Next Actor"), Twp::kSelectNextActor, "0"},
		{"SELECTPREVACTOR", _("Select Previous Actor"), Twp::kSelectPreviousActor, "9"},
		{"SKIPTEXT", _("Skip Text"), Twp::kSkipText, "."},
		{"SHOWHOTSPOTS", _("Show hotspots"), Twp::kShowHotspots, "TAB"},
	};

	for (int i = 0; i < ARRAYSIZE(actions); i++) {
		act = new Common::Action(actions[i].name.c_str(), actions[i].desc);
		act->setCustomEngineActionEvent(actions[i].action);
		act->addDefaultInputMapping(actions[i].input);
		engineKeyMap->addAction(act);
	}

	return Common::Keymap::arrayOf(engineKeyMap);
}

#if PLUGIN_ENABLED_DYNAMIC(TWP)
REGISTER_PLUGIN_DYNAMIC(TWP, PLUGIN_TYPE_ENGINE, TwpMetaEngine);
#else
REGISTER_PLUGIN_STATIC(TWP, PLUGIN_TYPE_ENGINE, TwpMetaEngine);
#endif
