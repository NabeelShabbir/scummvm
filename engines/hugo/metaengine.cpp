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

#include "engines/advancedDetector.h"
#include "common/system.h"
#include "common/savefile.h"
#include "common/textconsole.h"
#include "graphics/thumbnail.h"
#include "graphics/surface.h"

#include "hugo/hugo.h"
#include "hugo/detection.h"

namespace Hugo {

uint32 HugoEngine::getFeatures() const {
	return _gameDescription->desc.flags;
}

const char *HugoEngine::getGameId() const {
	return _gameDescription->desc.gameId;
}

class HugoMetaEngine : public AdvancedMetaEngine<HugoGameDescription> {
public:
	const char *getName() const override {
		return "hugo";
	}

	Common::Error createInstance(OSystem *syst, Engine **engine, const HugoGameDescription *gd) const override;
	bool hasFeature(MetaEngineFeature f) const override;

	int getMaximumSaveSlot() const override;
	SaveStateList listSaves(const char *target) const override;
	SaveStateDescriptor querySaveMetaInfos(const char *target, int slot) const override;
	void removeSaveState(const char *target, int slot) const override;
	Common::String getSavegameFile(int saveGameIdx, const char *target) const override {
		if (!target)
			target = getName();
		if (saveGameIdx == kSavegameFilePattern)
			return Common::String::format("%s-##.SAV", target);
		else
			return Common::String::format("%s-%02d.SAV", target, saveGameIdx);
	}
};

Common::Error HugoMetaEngine::createInstance(OSystem *syst, Engine **engine, const HugoGameDescription *gd) const {
	*engine = new HugoEngine(syst,gd);
	((HugoEngine *)*engine)->initGame(gd);
	return Common::kNoError;
}

bool HugoMetaEngine::hasFeature(MetaEngineFeature f) const {
	return
	    (f == kSupportsListSaves) ||
	    (f == kSupportsLoadingDuringStartup) ||
	    (f == kSupportsDeleteSave) ||
	    (f == kSavesSupportMetaInfo) ||
	    (f == kSavesSupportThumbnail) ||
	    (f == kSavesSupportCreationDate);
}

int HugoMetaEngine::getMaximumSaveSlot() const { return 99; }

SaveStateList HugoMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	Common::StringArray filenames;
	Common::String pattern = target;
	pattern += "-##.SAV";

	filenames = saveFileMan->listSavefiles(pattern);

	SaveStateList saveList;
	char slot[3];
	for (Common::StringArray::const_iterator filename = filenames.begin(); filename != filenames.end(); ++filename) {
		slot[0] = filename->c_str()[filename->size() - 6];
		slot[1] = filename->c_str()[filename->size() - 5];
		slot[2] = '\0';
		// Obtain the last 2 digits of the filename (without extension), since they correspond to the save slot
		int slotNum = atoi(slot);
		if (slotNum >= 0 && slotNum <= getMaximumSaveSlot()) {
			Common::InSaveFile *file = saveFileMan->openForLoading(*filename);
			if (file) {
				int saveVersion = file->readByte();

				if (saveVersion != kSavegameVersion) {
					warning("Savegame of incompatible version");
					delete file;
					continue;
				}

				// read name
				uint16 nameSize = file->readUint16BE();
				if (nameSize >= 255) {
					delete file;
					continue;
				}
				char name[256];
				file->read(name, nameSize);
				name[nameSize] = 0;

				saveList.push_back(SaveStateDescriptor(this, slotNum, name));
				delete file;
			}
		}
	}

	// Sort saves based on slot number.
	Common::sort(saveList.begin(), saveList.end(), SaveStateDescriptorSlotComparator());
	return saveList;
}

SaveStateDescriptor HugoMetaEngine::querySaveMetaInfos(const char *target, int slot) const {
	Common::InSaveFile *file = g_system->getSavefileManager()->openForLoading(getSavegameFile(slot, target));

	if (file) {
		int saveVersion = file->readByte();

		if (saveVersion != kSavegameVersion) {
			warning("Savegame of incompatible version");
			delete file;
			return SaveStateDescriptor();
		}

		uint32 saveNameLength = file->readUint16BE();
		char saveName[256];
		file->read(saveName, saveNameLength);
		saveName[saveNameLength] = 0;

		SaveStateDescriptor desc(this, slot, saveName);

		// Protect slot 99 (used for 'restart game')
		if (slot == 99) {
			desc.setDeletableFlag(false);
			desc.setWriteProtectedFlag(true);
		}

		Graphics::Surface *thumbnail;
		if (!Graphics::loadThumbnail(*file, thumbnail)) {
			warning("Missing or broken savegame thumbnail");
			delete file;
			return SaveStateDescriptor();
		}
		desc.setThumbnail(thumbnail);

		uint32 saveDate = file->readUint32BE();
		uint16 saveTime = file->readUint16BE();

		int day = (saveDate >> 24) & 0xFF;
		int month = (saveDate >> 16) & 0xFF;
		int year = saveDate & 0xFFFF;

		desc.setSaveDate(year, month, day);

		int hour = (saveTime >> 8) & 0xFF;
		int minutes = saveTime & 0xFF;

		desc.setSaveTime(hour, minutes);

		delete file;
		return desc;
	}

	SaveStateDescriptor desc(this, slot, Common::String());
	// Protect slot 99 (used for 'restart game')
	if (slot == 99)
		desc.setWriteProtectedFlag(true);

	return desc;
}

void HugoMetaEngine::removeSaveState(const char *target, int slot) const {
	g_system->getSavefileManager()->removeSavefile(getSavegameFile(slot, target));
}

} // End of namespace Hugo

#if PLUGIN_ENABLED_DYNAMIC(HUGO)
	REGISTER_PLUGIN_DYNAMIC(HUGO, PLUGIN_TYPE_ENGINE, Hugo::HugoMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(HUGO, PLUGIN_TYPE_ENGINE, Hugo::HugoMetaEngine);
#endif

namespace Hugo {

void HugoEngine::initGame(const HugoGameDescription *gd) {
	_gameType = gd->gameType;
	_platform = gd->desc.platform;
	_packedFl = (getFeatures() & GF_PACKED);
	_gameVariant = _gameType - 1 + ((_platform == Common::kPlatformWindows) ? 0 : 3);
}

} // End of namespace Hugo
