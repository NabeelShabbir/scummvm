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

namespace Composer {

static const ComposerGameDescription gameDescriptions[] = {
	// Magic Tales: Baba Yaga and the Magic Geese - from bug #5964
	{
		{
			"babayaga",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "412b7f4b0ef07f442009d28e3a819974", 3852},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Baba Yaga and the Magic Geese Mac - from bug #5934, #7025
	{
		{
			"babayaga",
			0,
			{
				{"book.mac", GAME_CONFIGFILE, "d:d82143cbc4a36093250c7d6f80af1147", 1877},
				{"Baba Yaga", GAME_EXECUTABLE, "d:ae3a4445f42fe10253da7ee4ea0d37d6", 44321},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Baba Yaga and the Magic Geese German- from bug #10171
	{
		{
			"babayaga",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "2a20e73d33ecd0f2fa8123d4f9862f90", 3814},
				AD_LISTEND
			},
			Common::DE_DEU,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Baba Yaga and the Magic Geese French- from bug #12122
	{
		{
			"babayaga",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "966a4ee9226d96085c953bb4f9426c06", 3940},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King - from bug #5964
	{
		{
			"imoking",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "62b52a1763cce7d7d6ccde9f9d32fd4b", 3299},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King Hebrew Windows
	{
		{
			"imoking",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "2b3eb997e8f55a03e81f67563c40adf4", 3337},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King French Windows. Bugreport #12123
	{
		{
			"imoking",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "753d3be27f54d564d8d1bff2b9f0d14f", 3375},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King Hebrew Macintosh
	{
		{
			"imoking",
			0,
			{
				{"book.mac", GAME_CONFIGFILE, "d:4896a22874bb660f5ba26a0af111f9c0", 1868},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Baba Yaga Demo from Imo and the King Hebrew CD
	{
		{
			"babayaga",
			"Magic Tales: Baba Yaga and the Magic Geese Demo",
			{
				{"by_demo.ini", GAME_CONFIGFILE, "4a87806683add232916298d6b62b9420", 224},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Little Samurai Demo from Imo and the King Hebrew CD
	{
		{
			"littlesamurai",
			"Magic Tales: The Little Samurai Demo",
			{
				{"ls_demo.ini", GAME_CONFIGFILE, "462cad83006721d2491dde7ef7a2d243", 223},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Baba Yaga Demo from Imo and the King Hebrew CD
	{
		{
			"babayaga",
			"Magic Tales: Baba Yaga and the Magic Geese Demo",
			{
				{"book.mac", GAME_CONFIGFILE, "d:ed4a902df3b26d58e9c013f814a30ee8", 134},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Little Samurai Demo from Imo and the King Hebrew CD
	{
		{
			"littlesamurai",
			"Magic Tales: The Little Samurai Demo",
			{
				{"book.mac", GAME_CONFIGFILE, "d:57a82d563800001ed88b2742c3650a2d", 136},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King Mac - from bug #5934
	{
		{
			"imoking",
			0,
			{
				{"book.mac", GAME_CONFIGFILE, "d:190158751630f69c2b6cf146aa2f1efc", 1874},
				{"imo and the king", GAME_EXECUTABLE, "d:b0277885fec943b5f19409f35b33964c", 44242},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King Mac Demo from Baba Yaga CD
	{
		{
			"imoking",
			"Magic Tales: Imo and the King Demo",
			{
				{"book.mac", GAME_CONFIGFILE, "d:b3456692eab14e9bdac64db6dad27be9", 136},
				{"imo and the king", GAME_EXECUTABLE, "d:764e0feea86cc201471f2b443161023b", 44321},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: Imo and the King German - from bug #10199
	{
		{
			"imoking",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "5925c6d4bf85d89b17208be4fcace5e8", 3274},
				AD_LISTEND
			},
			Common::DE_DEU,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: The Little Samurai - from bug #5964
	{
		{
			"littlesamurai",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "7a851869d022a9041e0dd11e5bace09b", 3747},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: The Little Samurai - French from bug #12124
	{
		{
			"littlesamurai",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "1e9199e31b4f93c5e5caeedd3c2e7c0b", 3833},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: The Little Samurai Mac - from bug #5934
	{
		{
			"littlesamurai",
			0,
			{
				{"book.mac", GAME_CONFIGFILE, "d:190158751630f69c2b6cf146aa2f1efc", 1874},
				{"The Little Samurai", GAME_EXECUTABLE, "d:38121dd649c24e8676aa108cf35d44b5", 44128},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: The Little Samurai Hebrew Windows
	{
		{
			"littlesamurai",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "c5f2c84df04780e7e67c70ec85b780a8", 3789},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Magic Tales: The Little Samurai Hebrew Macintosh
	{
		{
			"littlesamurai",
			0,
			{
				{"book.mac", GAME_CONFIGFILE, "d:190158751630f69c2b6cf146aa2f1efc", 1874},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// from Liam Finds a Story CD
	{
		{
			"magictales",
			"Magic Tales Demo: Baba Yaga, Samurai, Imo",
			{
				{"book.ini", GAME_CONFIGFILE, "dbc98c566f4ac61b544443524585dccb", AD_NO_SIZE},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Windows Demo from Little Samurai Hebrew CD
	{
		{
			"magictales",
			"Magic Tales Demo: Baba Yaga, Samurai, Imo",
			{
				{"demo.ini", GAME_CONFIGFILE, "ea784af960375834d655eb7281cd4500", 734},
				{"ik_demo.rsc", GAME_SCRIPTFILE, "31a2d65c4d22d327b8f5f205ab6e7ea3", 6680135},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformWindows,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	// Macintosh Demo from Little Samurai Hebrew CD
	{
		{
			"magictales",
			"Magic Tales Demo: Baba Yaga, Samurai, Imo",
			{
				{"demo.mac", GAME_CONFIGFILE, "d:6e775cda6539102d1ddee852bebf32c1", 488},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformMacintosh,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV1
	},

	{
		{
			"liam",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "fc9d9b9e72e7301d011b808606eaa15b", 834},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	// Liam Finds a Story Mac - from bug #5931
	{
		{
			"liam",
			0,
			{
				{"liam finds a story.ini", GAME_CONFIGFILE, "d:85a1ca6002ded8572920bbdb73d35b0a", 747},
				{"page99.rsc", GAME_SCRIPTFILE, "d:11b0a19c6b6d73c39e2bd289a457c1dc", 355159},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	// from Liam Finds a Story CD
	{
		{
			"magictales",
			"Magic Tales Demo: Sleeping Cub, Princess & Crab",
			{
				{"book.ini", GAME_CONFIGFILE, "3dede2522bb0886c95667b082987a87f", AD_NO_SIZE},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_USEEXTRAASTITLE | ADGF_DEMO,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{
		{
			"darby",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "7e3404c559d058521fff2aebe5c427a8", 2545},
				{"page99.rsc", GAME_SCRIPTFILE, "49cc6b16caa1c5ec7d94a3c47eed9a02", 1286480},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{
		{
			"darby",
			0,
			{
				{"Darby the Dragon.ini", GAME_CONFIGFILE, "d:d81f9214936fa70d42fc578908d4bb3d", 2950},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by msSeven - from bug Trac #10399
		{
			"darby",
			0,
			{
				{"page99.rsc", GAME_SCRIPTFILE, "d:ca350397f0c009649afc0cb6145921f0", 1286480},
				{"Dragor le dragon.ini", GAME_CONFIGFILE, "d:b0ccebb50cf8377486d86cb65ee7215d", 2240},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by Strangerke, "CD-Rom 100% Malin" Pack
		{
			"darby",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "285308372f7dddff2ca5a25c9192cf5c", AD_NO_SIZE},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by WindlePoons, "100% Kids Darby & Gregor" Pack. Bugreport #6825
		{
			"darby",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "285308372f7dddff2ca5a25c9192cf5c", 2545},
				{"page99.rsc", GAME_SCRIPTFILE, "40b4879e9ba6a34d6aa2a9d2e30c5ef7", 1286480},
				AD_LISTEND
			},
			Common::DE_DEU,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by Niv Baehr, Bugreport #6878
		{
			"darby",
			0,
			{
				{"page99.rsc", GAME_SCRIPTFILE, "183463d18c050563dcdec2d9f9670515", AD_NO_SIZE},
				AD_LISTEND
			},
			Common::HE_ISR,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{
		{
			"gregory",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "14a562dcf361773445255af9f3e94790", 2234},
				{"page99.rsc", GAME_SCRIPTFILE, "01f9381162467e052dfd4c704169ef3e", 388644},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{
		{
			"gregory",
			0,
			{
				{"Gregory.ini", GAME_CONFIGFILE, "d:fa82f14731f28c7379c5a106df07a0d6", 2753},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by Strangerke, "CD-Rom 100% Malin" Pack
		{
			"gregory",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "e54fc5c00de5f94e908a969e445af5d0", AD_NO_SIZE},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by WindlePoons, "100% Kids Darby & Gregor" Pack. Bugreport #6825
		{
			"gregory",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "e54fc5c00de5f94e908a969e445af5d0", 2234},
				{"page99.rsc", GAME_SCRIPTFILE, "1ae6610de621a9901bf87b874fbf331f", 388644},
				AD_LISTEND
			},
			Common::DE_DEU,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by sev
		{
			"princess",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "fb32572577b9a41ba299825ef1e3181e", 966},
				{"page99.rsc", GAME_SCRIPTFILE, "fd5ebd3b5e36c4651c50241619525355", 45418},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	// The Princess and the Crab Mac - From Bug #5928
	{
		{
			"princess",
			0,
			{
				{"the princess and the crab.ini", GAME_CONFIGFILE, "d:f6b551a7304643004bd5e4df7ac1e76e", 877},
				{"page99.rsc", GAME_SCRIPTFILE, "d:fd5ebd3b5e36c4651c50241619525355", 45418},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ // Provided by sev
		{
			"sleepingcub",
			0,
			{
				{"book.ini", GAME_CONFIGFILE, "0d329e592387009c6387a733a3ea2235", 964},
				{"page99.rsc", GAME_SCRIPTFILE, "219fbd9bd2ff87c7023814405d753145", 46916},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	// Sleeping Cub Mac - From Bug #5927
	{
		{
			"sleepingcub",
			0,
			{
				{"sleeping cub.ini", GAME_CONFIGFILE, "d:39642a4036cb51443f5e90052c3ad0b2", 877},
				{"page99.rsc", GAME_SCRIPTFILE, "d:219fbd9bd2ff87c7023814405d753145", 46916},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformMacintosh,
			ADGF_NO_FLAGS,
			GUIO2(GUIO_NOASPECT, GUIO_NOMIDI)
		},
		GType_ComposerV2
	},

	{ AD_TABLE_END_MARKER, 0 }
};

} // End of namespace Composer
