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

namespace Wage {

#define ADGF_DEFAULT (ADGF_DROPLANGUAGE|ADGF_DROPPLATFORM|ADGF_MACRESFORK|ADGF_UNSTABLE)
#define ADGF_GENERIC (ADGF_DEFAULT|ADGF_USEEXTRAASTITLE|ADGF_AUTOGENTARGET)
#define ADGF_DEMO (ADGF_GENERIC|ADGF_DEMO)

#define FANGAME(n,m,s) { "wage",n,AD_ENTRY1s(n,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_GENERIC,GUIO0()}
#define FANGAMEN(n,f,m,s) { "wage",n,AD_ENTRY1s(f,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_GENERIC,GUIO0()}
#define FANGAMEND(n,f,m,s) { "wage",n,AD_ENTRY1s(f,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_DEMO,GUIO0()}
#define BIGGAME(t,v,f,m,s) { t,v,AD_ENTRY1s(f,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_DEFAULT,GUIO0()}

static const ADGameDescription gameDescriptions[] = {
	FANGAMEND("World Builder Demo World", "Demo World", "e221e6f9631f110b484f239e58137a3f", 45467),

	FANGAME("3rd Floor", "931aa0b6ada3aced5117ee6e6daf2fb8", 281153),
	FANGAME("3rd Floor", "140883954b7cd89b0ffabde6ee0073d4", 281167), // alt version
	FANGAME("3rd Floor", "afe1a9eb0d4e5857f9f748570862c88e", 281213), // v1.3
	BIGGAME("afm", "v1.3", "Another Fine Mess 1.3", "25934edf84e814f41f3ddf87185b554b", 1409792),
	BIGGAME("afm", "v1.4", "Another Fine Mess 1.4", "28d2b78c7abcbfd526f9c252444ef0b3", 1420563),
	BIGGAME("afm", "v1.8", "Another Fine Mess 1.8", "8bbec64ffe9deee4ff48d27f01176814", 1420467),
	BIGGAME("amot", "v1.8", "A Mess O' Trouble 1.8", "57de8f1f79a24fa1a296aa10242c3648", 1842848),
	FANGAMEN("The Adventures of Steve Reeve", "TAoSR", "e8b8ab3a838382125594aae17d53a4e7", 843323),
	FANGAMEND("The Ashland Revolution", "xn--The Ashland Revolution Demo-uc9p", "18f1f5d1081b9a5676ccfb0c3b857059", 144767), // Original file name "The Ashland Revolution Demo†"
	FANGAMEND("The Ashland Revolution", "Ashland Demo", "7a340e5ea03f7468717de408fb5b13fb", 149828),
	FANGAME("The Axe-orcist", "9718b72e86a9727bbd68e12fa992b268", 308508),
	FANGAME("Brownie Saves the Day", "964d9cf87422c09c50fe294adf9a7571", 680145),
	FANGAME("Brownie's Dream", "379f2c810efc18bad932049d331df1b6", 440448),
	FANGAME("Brownie's Dream", "78f79114a7e85e452a7b8c7346a21456", 440448), // alt version?
	FANGAMEN("Brownie's Time Travels", "Brownie's Time Travels v1.2", "d95999aff4e283bd21db686cfb2cb9b9", 471333),
	FANGAMEN("Brownie's Time Travels", "Brownie's Time Travels v1.2", "9dc2c6ba42788dbe534eea3ce6da91d8", 471333), // alt version?
	FANGAME("Bug Hunt", "b55b23a5f38d28407bd6c178a64ab629", 195443),
	FANGAME("Bug Hunt", "cd7e1064813b9b0e3cd946e569109b34", 195523), // alt version
	BIGGAME("cantitoe", "", "Camp Cantitoe", "4a44860fdfe5b9e98bcf8433801cd925", 616729),
	FANGAMEN("Can James Be Found?", "xn--Can James Be Found 1.1.1-iba62n", "27822449e7e725d898181adf6e3b1689", 767445),
	FANGAME("Canal District", "061a09e9258145f6a585e869a0319004", 641214),
	FANGAME("Carbon Copy", "322410318c60045928a10f6b4c0b0a87", 519189),
	FANGAME("Castle of Ert", "069daab46729291a615e9ee3528008ff", 198699),
	FANGAMEN("Castle of Ert", "Castle of Ert.1", "ecadcdd9bdee68aeb32507932857db30", 198727), // alt version, v1.0
	FANGAME("Color by Number", "8fc77e5976ca25d05cf74db3ec3e5ef2", 528306),
	FANGAMEN("Dash Hansen and the Search for the Black Orchid", "Dash Hansen", "555e07344506720c8e4a29e1b5ba3578", 257129),
	FANGAMEND("Death Mall", "Death Mall Demo", "8284351df1c7b678279139ed486ab127", 254618),
	FANGAMEN("Deep Angst", "xn--Deep Angst-398e", "ddc4c8b3d317e2c79a12c53275253ac3", 329294), // Original file name "Deep Angst™", v.90b
	FANGAMEN("Deep Angst II: The Nightmare Ends", "Deep Angst II", "2e468021416bc2b82e283030c7f6bc5d", 408761),
	FANGAME("Deep Ennui", "9879bf659f11c9177d578a347da0c658", 85819),
	// Polygons with ignored byte 1
	FANGAME("Double Trouble", "1cd05d66163b44f9f0d8c3e7232bc2db", 542115),
	BIGGAME("drakmythcastle", "Disk I", "Drakmyth Castle disk I of II", "54dd0a817b667fc05c4f2dee6abe126a", 793528),
	BIGGAME("drakmythcastle", "Disk I", "Drakmyth Castle", "b796545fc4b7c2b89683db873e005e92", 792355), // alt version
	BIGGAME("drakmythcastle", "Disk II", "Drakmyth Castle II", "b57af17c805775d7d68b62133164c4e4", 1685403),
	// Crash at start in GUI rendering
	FANGAMEN("Dune Eternity", "xn--DUNE ETERNITY -paaanaa75fbbobb", "4946bc99cc42bf83b628352aa9b81a7b", 289945), // Original file name is "***DUNE ETERNITY*** "
	FANGAMEN("Dungeon World II", "DungeonWorld2", "74a7153f9ae61a59a216078a37f68f2c", 229943),
	// Made for bigger resolution
	FANGAME("Dynasty of Dar", "e118a261d33831c224f3b776ec5dd2a8", 275437),
	FANGAME("Edg's World", "480bcf68be49ee3765902e922ccdc833", 106513),
	FANGAME("Eidisi I", "ed8fec61ad94ddec06feaf4eb720084b", 172296),
	FANGAME("Eidisi I", "a20f080d6109d8e253d74b0dfb4b2ae5", 172296), // alt version
	FANGAME("Eidisi I", "06ae31c4361f9bd5b91593858b6d0d79", 172310), // alt version
	FANGAME("Elite Commando", "3fc74f1403c1529b52f3cd4d60771dac", 293704), // v1.0
	// Problems(?) with text on the first screen
	FANGAMEN("Enchanted Pencils", "Enchanted Pencils 0.99 (PG)", "49a0708da81dbeb28c6e607429c92209", 408657),
	FANGAMEN("Enchanted Pencils", "Enchanted Pencils 0.99 (PG)", "0095d0e069851521c44ca3cdc94bcba3", 414464), // alt?
	FANGAMEN("Escape!", "xn--Escape!-z46c", "28a9658ee846a34f133df29b54cf255a", 64819), // Original file name "Escape!†"
	FANGAME("Escape from School!", "2055747bb874052333190eb993246a7f", 49849),
	FANGAMEN("Escape from School!", "xn--Escape from School!-3g6k", "fcc581e52d1fc8ea4603d7c953fa935a", 49863), // Original file name "Escape from School!†"
	FANGAME("Escape From Saecvrom", "ab401f96ca0755bf5fb849f71cc47d83", 588982),
	FANGAME("Everyman 1", "97d78e22493245636f84ad8db732305c", 335449),
	FANGAME("Exploration Zeta!", "9006eff549afadc956e5de4ae6a24fbd", 366343),
	// Cannot proceed past the first scene
	FANGAMEND("Explorer", "Explorer DEMO", "0ae79f48754466c4cd65137c7f186384", 460972),
	// Crash in console rendering on the first scene
	FANGAME("Fantasy Quest", "b52d3e2680a76c23b2791e2c87f6b6bd", 762498),
	FANGAME("Find the Heart", "0c0c282649597ea1ac82d97c8d4029a2", 105979), // From Joshua's Worlds 1.0
	FANGAME("Find the Heart", "6fb8c6b8bc2287ba225b0ac6580dc073", 105675), // From Joshua's Worlds 1.0, alt version
	FANGAME("Find the Heart", "08de3248b8c691d9a08af984bdcfa872", 105629), // From Joshua's Worlds. Alt version
	FANGAME("Find the Heart", "73935d313b666763e50d2cdc6b3b7908", 105615), // Standalone
	FANGAMEN("Fortune Teller", "Fortune Teller 1.1", "3c09329fc3c92a70e5c8874cc763f5cb", 73675),
	FANGAMEN("Fred Rogers - Terrorist", "xn--Terrorist-od0e", "4398f711bc2a456e6d730641308593f0", 524213), // Original file name "Terrorist†"
	FANGAME("Fred Rogers - Terrorist", "8597a77619847efbce3f1f8b2ceb3258", 524199),
	BIGGAME("grailquest", "", "GrailQuest", "6441d134c0aedd8cb3b6909107a22ee3", 739452),
	FANGAME("Grey Tower", "02d0bb7a8c278d3789616129d47f15c1", 397248), // v1.5.2
	FANGAMEN("Haunted House", "Haunted House 1.5", "5e34e9fa13f4c90876f10a40ea1d1c79", 177244),
	FANGAMEN("The Hotel Caper", "The Hotel Caper V1.0", "c9b3c75814fc6b14feae044157bef252", 231713),
	FANGAMEN("The Hotel Caper", "The Hotel Caper V1.0", "4658ece81a6f211a828e747125482f48", 231713), // alt version
	FANGAMEN("The Hotel Caper", "The Hotel Caper V1.0", "baaaae4569fbb1947d74667ac484bea9", 231773), // alt version
	FANGAMEN(".i.f.", "xn--.i.f.-", "575fc0c25e9823dd742de1acdcaac325", 183221),
	// Cropped graphics on first scene, cannot pass to in-game
	FANGAMEN("Introduction to Gothic", "Intro to Gothic", "606eec666f0b2d767e4423747e740434", 207811),
	FANGAMEN("James Bond 007", "007", "2449924f2cb43454489a4ef91c0ee702", 50407),
	// Lots of unhandled comparisons
	FANGAME("Jamie the Demon Slayer", "ed054aa760569059c7ea554e822089a6", 232533),
	FANGAMEN("Journey", "The Journey 1.6.2 US", "588a516caa187005fdfcbc72823c8eff", 820316),
	FANGAMEN("Jumble", "xn--LSJUMBLE -", "555ead186ec1683157e53b96fc4a99d5", 647083), // Original file name is "LSJUMBLE† "
	FANGAME("Karth of the Jungle", "6dae6eef6f46101ba8c9e312bb82e824", 96455),
	FANGAME("Karth of the Jungle", "c869cacc59f2402d06bc8197be28b5df", 96704), // Alternative version
	FANGAME("Karth of the Jungle II", "6f26e0bace5c41d91c135e5e102de5bc", 200797),
	FANGAMEN("Little Pythagoras", "Little Pythagoras 1.1.1", "66a5d2ac1a0df2ee84cbee583c1f1dfe", 628565),
	FANGAME("Lost Crystal", "945a1cf1ead6dd298305935b5ccb21d2", 770816),
	FANGAMEN("Lost In Kookyville", "Lost In Kookyville 1.2.4", "89ecb4cef5cc4036e54f8bc45ce7520e", 721313),
	FANGAMEN("Lost In Kookyville", "Lost In Kookyville 1.2.4", "dfa0abbadf3848f415c6696d6d914455", 722917), // alt version?
	FANGAME("Lost Princess", "29d9889b566286506ded7d8bec7b75ce", 166502),
	FANGAME("Mac Spudd!", "eaba9195dd27c2a26b809a730417122b", 781859),
	FANGAME("Magic Rings", "263e2c90af61f0798bf41f6a1e3f6345", 108788),
	FANGAMEN("Maze of the Questing Beast", "MQB", "03775e1894809f24234aeaab18f39451", 134444),
	FANGAMEN("Maze of the Questing Beast Solutions", "MQB Solutions", "8a27e515f12162cc8b85e4f2bd16a1e5", 37606),
	// No way to click on the house
	FANGAME("Messy House", "32ca71f2ff37997407cead590c2dd306", 176864),
	FANGAME("Midnight Snack", "70ba8a5a1f0304669c9987360bba236f", 67696),
	FANGAME("Midnight Snack", "24973af10822979e23866d88a7d2e15c", 67710), // Alt version
	FANGAME("Mike's House", "591b5a4d52ecf9a7d87256e83b78b0fd", 87101),
	FANGAME("Mike's House", "e4c0b836a21799db3995a921a447c28e", 87087), // Alt version
	FANGAME("Minitorian", "c728dfccdca12571e275a4113b3db343", 586208),
	FANGAMEN("M'Lord's Warrior", "xn--M'Lord's Warrior -f82j", "e0a0622ce2023984e3118141a9688ec5", 465383), // Original file name is "M'Lord's Warrior †"
	FANGAMEN("Mormonoids from the Deep", "Mormonoids 1.0",  "15c99d26ac2abb9eb4802a7dd5326086", 642975),
	FANGAMEN("Mormonoids from the Deep", "Mormonoids 1.25", "4730d0c47d13401d73353e980f91a304", 645062),
	FANGAMEN("Mormonoids from the Deep", "Mormonoids 1.25", "1a7ee052b375f0c0a4c18836c978ce5b", 645077), // Alt version
	// Unhandled comparison case
	FANGAMEN("Mountain of Mayhem", "xn--Mountain of Mayhem -3g6k", "634211b004371635d191ae0687035501", 749747), // Original file name "Mountain of Mayhem †"
	FANGAME("Muddy Water", "711dd9d154d13c31bc216ef8539bb095", 662438), // v1.3.2
	// No way to pass through the first screen
	FANGAME("Nightcrawler Ned", "8423fc015c395bd6be54a7ea69170d99", 366286),
	// No player in the world
	FANGAMEN("Parrot Talk", "PARROT TALK V1", "c38c090be8c078d931905c93bc0689f5", 118680),
	// No player in the world
	FANGAMEN("Parrot Talk", "PARROT TALKV2", "5ec1df9e2d6d0dcf1a040a95500d9551", 118628),
	FANGAME("Pavilion", "a980e60a291c0a7b949474177affa134", 231431),
	FANGAMEN("Pencils", "Pencils.99", "09dbcdbefe20536c2db1b1a4fb4e5ed3", 408295),
	FANGAMEN("Pencils", "Pencils.99", "9757cc28d82cea636ee260b9aa33c167", 407695), // alt version
	// Polygons with byte 1
	FANGAME("Periapt", "7e26a7827c694232624321a5a6844511", 405750),
	FANGAME("Periapt", "bc36e40de279d5f0844577fe702d9f64", 405750), // alt version
	FANGAME("The Phoenix", "bd6dabf7a19d2ab7902498a8513f8c71", 431387),
	// Cannot push buttons
	FANGAMEN("The Phoenix v1.2", "The Phoenix", "fee9f1de7ad9096d084461d6066192b1", 431384),
	FANGAME("Pirate Attack!", "d4d3f59b57d5bf3dd690fd657ecdd9c6", 323722),
	FANGAME("Porno Writer 2.0", "b5228c22158ff40ccac36b6a61cc317a", 791379),
	FANGAME("Pretty Good Pornography 3.0", "c86c92ec69b464a197659b1bd80880b9", 1122264),
	FANGAME("Psychotic!", "d6229615b71b189f6ef71399a0856cd2", 367053),
	FANGAME("Psychotic!", "c7608f67592563b44f2f48fe5fec63ce", 367067), // alt version
	FANGAME("Psychotic!", "51aa5f2744ceb5666c9556bccee797d6", 367173), // another alt version
	FANGAME("Puzzle Piece Search", "6c21c1e0c6afef9300941abd7782dd16", 247437), // From Joshua's Worlds 1.0
	FANGAME("The Puzzle Piece Search", "8fa1d80dd3f1ed69f45d15d774968995", 247082), // From Joshua's Worlds
	FANGAME("The Puzzle Piece Search", "fb839ac4f22427f44e99bcc5afd57a0b", 247068), // Standalone
	// Empty(?)  first scene
	FANGAME("Pyramid of No Return", "4bf4c39b140f5aadb5f8c9a50153d18e", 384889),
	// Cropped graphics at the first scene
	FANGAME("P-W Adventure", "a8e9f97ee02f01de588a4dbabe55ca3f", 218960),
	FANGAMEN("Pyramid of Ert", "Pyramid of Ert V1.2", "358b03ea9c978fbfd2ce2833daea00f8", 315527),
	FANGAME("Queen Quest", "7ca009dad76827ce008c3c7fa01cab0a", 56770),
	FANGAME("Queen Quest", "cde1255992101e0763687f45e0f47169", 56783), // alt version
	FANGAME("Quest for T-Rex", "51aa29d24ca702c8980e959706ef0b76", 592328),
	FANGAME("Quest for T-Rex", "f1edd78817e5a72fb7d85879f168fc8c", 592328), // alt version
	FANGAME("Quest for T-Rex", "31ef93ae4ee7b48e3720b977dcf480c3", 592314), // alt version
	FANGAMEN("Quest for the Dark Sword", "xn--Quest for the Dark Sword-3r4o", "d98c3879ff20ca7e835e3a630c2c74ef", 572320), // original file name "Quest for the Dark Sword™"
	FANGAME("Radical Castle", "e424dea5542817435b4b6da41fd532cb", 355345),
	FANGAME("Radical Castle 1.0", "7c7701dcab013c65510f97a8712fc419", 347022),
	BIGGAME("raysmaze", "v1.5", "Ray's Maze1.5", "328096d3c7ccb838956c42b273f17b8e", 1408260),
	BIGGAME("raysmaze", "v1.5/alt", "Ray's Maze1.5", "401cd46df5e49fa4171ed398b3e0227b", 1408260),
	FANGAME("Ray's World Builder Demo", "eafea10db54530ac6e6128be31741542", 115800),
	FANGAME("Robot Planet", "1066f6b2892cda16c2f365d1ec97537c", 107089),
	// Unhandled comparison case
	FANGAMEN("Sands of Time", "xn--Sands of Time-1s6g", "d065662865d0cb9065812479ed7d2795", 122416), // Original file name "Sands of Time†"
	BIGGAME("scepters", "", "Scepters", "ecb776fb660205fad5819a26f7e180b5", 347103),
	BIGGAME("scepters", "", "Scepters", "e6c58e96b02f8eb46e0ccfe4f547045b", 346339),
	BIGGAME("scepters", "", "Scepters", "2c824f1bd7b22c575c7be86ac88ebd23", 347284), // alt version
	FANGAME("Schmoozer", "7bbb3d317d2074870c72b28d07984ef8", 221244),
	FANGAME("sMythWorld", "8224b15a910c9e7515923107d138de77", 472101),
	// ??? problems with dog bitmap?
	FANGAMEN("Space Adventure", "SpaceAdventure", "3908c75d639989a28993c59931fbe1ec", 155100),
	FANGAMEN("Space Adventure", "SpaceAdventure", "e38d524cb778ed0beb77ee9299f0ed45", 155100), // alt version
	FANGAMEN("SparGate", "SparGate- vNC.1", "a7a7bfc1825011c2df8b7a03b57fcac9", 611991),
	FANGAMEN("Spear of Destiny", "xn--SpearOfDestiny-ef3h", "ac00a26f04f83b47c278cc1d226f48df", 333409), // Original file name "SpearOfDestiny†"
	FANGAMEN("Spear of Destiny", "SpearOfDestiny", "ac00a26f04f83b47c278cc1d226f48df", 333409), // same version, normal file name
	FANGAME("Spear of Destiny", "ea90bddd0925742351340cf88dd1c7a6", 620350), // alt version, normal file name
	FANGAME("Star Trek", "3067332e6f0bb0314579f9bf102e1b56", 53064),
	FANGAME("Starport", "d9e25edc9ea5d2a8b29a3693de19ae2c", 253970),
	FANGAMEN("Strange Disappearance", "xn--Strange Disappearance -", "9d6e41b61c0fc90400e5da2fcb653a4a", 772026), // Original file name "Strange Disappearance "
	FANGAME("The Sultan's Palace", "fde31cbcc77b66969b4cfcd43075341e", 456599), // Releases titled "Palace of Sand" were made with FutureBasic
	FANGAMEN("Swamp Witch", "xn--Swamp Witch-dl3f", "bd8c8394be31f7845d55785b7ccfbbde", 739525), // Original file name "Swamp Witch†"
	FANGAME("Swamp Witch", "bd8c8394be31f7845d55785b7ccfbbde", 739525), // same version, normal file name
	FANGAME("Swamp Witch", "07463c8b3b908b0c493a41b949ac1ff5", 739875), // alt version, normal file name
	FANGAME("Sweetspace Now!", "574dc7dd25543f7a516d6524f0c5ab33", 123557), // Comes with Jumble
	// Wrong scrolling in the first console text
	FANGAMEN("Sword of Siegfried", "Sword of Siegfried 1.0", "2ae8f21cfb228ce58ee47b767bdd8820", 234507),
	FANGAMEN("Sword of Siegfried", "Sword of Siegfried 1.0", "7a68b00019592f3aa671cae024f7e843", 234493), // alt version
	FANGAME("Time Bomb", "e96f3e2efd1e3db6ad0be22180f5473c", 64308),
	FANGAME("Time Bomb", "976180f9be0d1029aaba7774fec9767c", 64322), // Alt version
	FANGAMEN("The Time Squisher", "Time Squisher v 1.1", "3e296141e7a7c9b05e0dde779d9bb50d", 463526),
	// Admission for on 3rd screen is messed up
	FANGAME("The Tower", "4cd8755ccb5bbeaf2e5f7848a8daa033", 556283),
	// Messed up first scene
	FANGAMEND("Tombworld", "xn--Demo TombWorld-8ra", "695734292024290d5d0aa6a66ff628f6", 663996), // Original file name "Demo TombWorld©"
	// Doesn't go past first scene
	BIGGAME("twisted", "", "Twisted! 1.6", "6e0be4c7d83231e56a431dc4ef7bf978", 960698),
	// Polygons with ignored byte 1 and 2 on second scene
	FANGAME("The Village", "fd35cad8c61064d6c8aaadab7070ccad", 314572),
	FANGAMEN("Volcano II", "xn--Volcano II-0y6e", "7941c08b34bc2408b98c0004c7154aeb", 82735), // Original file name "Volcano II†"
	FANGAMEN("Who Shot Brownie Dog?", "xn--Who Shot Brownie Dogv1.01-lba88n", "4e7a950567c73e98e4478e5683e943ca", 195923),
	FANGAMEN("Wishing Well", "xn--Wishing Well -", "607a66461d65a73c1222d63dbde0175d", 103432), // original file name "Wishing Well "
	FANGAME("The Wizard's Apprentice", "477c2d2d4672d968dfac1df2acef1dc9", 782568),
	FANGAME("Wizard's Warehouse", "18b4678c76961c1f3ae3013e13f691a3", 159492),
	FANGAMEN("Wizard's Warehouse 2", "WizWarehouse 2.0", "e67ac67548236a73897a85cd12b30492", 230614),
	FANGAME("ZikTuria", "a91559e6f04a67dcb9023a98a0faed77", 52716),
	FANGAMEN("Zoony", "xn--Zoony-j64b", "3f7418ea8672ea558521c178188cfce5", 154734), // original file name "Zoony™"
	FANGAMEN("Zoony", "xn--Zoony-j64b", "55d3d42b5dca9630eb28ad464f343c67", 154734), // original file name "Zoony™", alt version
	FANGAMEN("Zoony", "xn--Zoony-j64b", "ecbe19c53f9d5b7ef62e66db9ea42348", 154970), // original file name "Zoony™", yet another alt version

	AD_TABLE_END_MARKER
};

} // End of namespace Wage
