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

#include "chewy/dialogs/credits.h"
#include "chewy/events.h"
#include "chewy/file.h"
#include "chewy/global.h"

namespace Chewy {
namespace Dialogs {

static const int16 CREDITS_POS[65][2] = {
	{40,  160}, {80,  170}, {40,  190}, {80,  200}, {80,  210},
	{40,  230}, {80,  240}, {80,  250}, {80,  260}, {40,  280},
	{80,  290}, {80,  300}, {80,  310}, {80,  320}, {40,  340},
	{80,  350}, {80,  360}, {40,  380}, {80,  390}, {40,  410},
	{80,  420}, {40,  440}, {80,  450}, {40,  470}, {80,  480},
	{80,  490}, {80,  500}, {80,  510}, {80,  520}, {40,  540},
	{80,  550}, {80,  560}, {80,  570}, {80,  580}, {40,  600},
	{80,  610}, {80,  620}, {80,  630}, {80,  640}, {80,  650},
	{80,  660}, {80,  670}, {80,  680}, {80,  690}, {80,  700},
	{80,  710}, {80,  720}, {80,  730}, {80,  740}, {80,  750},
	{80,  760}, {40,  780}, {40,  790}, {40,  800}, {40,  810},
	{40,  820}, {40,  840}, {80,  850}, {40,  870}, {80,  880},
	{80,  890}, {80,  910}, {80,  920}, {80,  930}, {80,  940}
};

static const bool CREDITS_TYPE[65] = {
	true, false, true, false, false, true, false, false, false, true,
	false, false, false, false, true, false, false, true, false, true,
	false, true, false, true, false, false, false, false, false, true,
	false, false, false, false, true, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false,
	false, true, true, true, true, true, true, false, true, false,
	false, true, true, true, true
};

static const char *CREDITS_TEXT[65] = {
	"Idea & Story:",
	"Carsten Wieland",
	"Programming:",
	"Helmut Theuerkauf",
	"Alexander Diessner",
	"Graphics & Animation:",
	"Carsten Wieland",
	"Nihat Keesen",
	"Stefan Frank",
	"Text & Dialogues:",
	"Helmut Theuerkauf",
	"Alexander Diessner",
	"Carsten Wieland",
	"Wolfgang Walk",
	"Music:",
	"Carsten Wieland",
	"Stelter Studios",
	"Sound FX:",
	"Helmut Theuerkauf",
	"Producer & Lecturer:",
	"Wolfgang Walk",
	"Minister of financial affairs:",
	"Carsten (Dagobert) Korte",
	"Testers:",
	"Lutz Rafflenbeul",
	"Thomas Friedmann",
	"Bernhard Ewers",
	"Christian von der Hotline",
	"Carsten Korte",
	"The voices:",
	"Chewy......Renier Baaken",
	"Howard.....Wolfgang Walk",
	"Nichelle...Indhira Mohammed",
	"Clint......Alexander Schottky",
	"Also cast:",
	"Renier Baaken",
	"Guido B\x94sherz",
	"Gerhard Fehn",
	"Alice Krause",
	"Reinhard Lie\xE1",
	"Willi Meyer",
	"Nicole Meister",
	"Lutz Rafflenbeul",
	"Alexander Schottky",
	"Bernd Schulze",
	"Susanne Simenec",
	"Helmut Theuerkauf",
	"Andreas Vogelpoth",
	"Mark Wagener",
	"Wolfgang Walk",
	"Thomas Piet Wiesenm\x81ller",
	"Speech recorded by",
	"tmp Studio, Moers by Willi Meyer",
	"Cut by Hartmut Stelter",
	"Studios Hamburg and",
	"Carsten Wieland",
	"Soundsystem:",
	"AIL (c) Miles Design",
	"Adventure Engine:",
	"I.C.M. developed by",
	"New Generation Software",
	"Song Boo Boo Ba Baby composed",
	"by Haiko Ruttmann,",
	"Lyrics Wolfgang Walk,",
	"featuring Indhira Mohammed."
};

void Credits::execute() {
	int lineScrolled = 0;
	int fontCol;

	room->open_handle("BACK/GBOOK.TGP", "rb", 0);
	room->load_tgp(5, &room_blk, 1, 0, "BACK/GBOOK.TGP");
	_G(spieler).scrollx = 0;
	_G(spieler).scrolly = 0;
	out->setze_zeiger(screen0);
	room->set_ak_pal(&room_blk);
	fx->blende1(workptr, screen0, pal, 150, 0, 0);

	for (int i = 0; i < 6; ++i) {
		int color = 63 - (6 * i);

		out->raster_col(6 - i, color, 0, 0);
		out->raster_col(7 + i, color, 0, 0);

		color = 63 - (4 * i);
		out->raster_col(37 - i, color, color, color);
		out->raster_col(38 + i, color, color, color);
	}

	_G(spieler).DelaySpeed = 2;

	for (;;) {
		if (in->get_switch_code() == ESC || SHOULD_QUIT)
			break;

		// Display the starfield background
		out->setze_zeiger(workptr);
		out->map_spr2screen(ablage[room_blk.AkAblage],
			_G(spieler).scrollx, _G(spieler).scrolly);

		// Animate moving the background
		if (++_G(spieler).scrollx >= 320)
			_G(spieler).scrollx = 0;

		if (in->get_switch_code() == ESC)
			break;

		++lineScrolled;
		g_events->delay(50);
		bool stillScrolling = false;

		for (int i = 0; i < 65; ++i) {
			int destY = CREDITS_POS[i][1] - lineScrolled;
			if (destY >= 160 || destY <= 40)
				continue;

			if (CREDITS_TYPE[i]) {
				fontCol = 32;
				out->set_fontadr(font6x8);
				out->set_vorschub(fvorx6x8, fvory6x8);
			} else {
				fontCol = 1;
				out->set_fontadr(font8x8);
				out->set_vorschub(fvorx8x8, fvory8x8);
			}
			stillScrolling = true;

			int fgCol = fontCol + (160 - destY) / 10;
			out->printxy(CREDITS_POS[i][0], destY, fgCol, 300, scr_width, CREDITS_TEXT[i]);
		}

		if (!stillScrolling)
			break;

		out->setze_zeiger(nullptr);
		out->back2screen(workpage);
	}

	out->set_fontadr(font8x8);
	out->set_vorschub(fvorx8x8, fvorx8x8);
	room->open_handle("back/episode1.tgp", "rb", 0);

	room->set_ak_pal(&room_blk);
	hide_cur();
	uhr->reset_timer(0, 5);
}

} // namespace Dialogs
} // namespace Chewy
