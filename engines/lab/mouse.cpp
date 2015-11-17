/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This code is based on Labyrinth of Time code with assistance of
 *
 * Copyright (c) 1993 Terra Nova Development
 * Copyright (c) 2004 The Wyrmkeep Entertainment Co.
 *
 */

#include "lab/mouse.h"
#include "lab/vga.h"
#include "lab/stddefines.h"
#include "lab/timing.h"
#include "lab/interface.h"

namespace Lab {

extern bool IsHiRes;

static bool LeftClick = false;
static bool RightClick = false;

static bool MouseHidden = true;
static int32 NumHidden   = 1;
static Gadget *LastGadgetHit = NULL;
Gadget *ScreenGadgetList = NULL;
static byte MouseData[] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
						   1, 7, 1, 0, 0, 0, 0, 0, 0, 0,
						   1, 7, 7, 1, 0, 0, 0, 0, 0, 0,
						   1, 7, 7, 7, 1, 0, 0, 0, 0, 0,
						   1, 7, 7, 7, 7, 1, 0, 0, 0, 0,
						   1, 7, 7, 7, 7, 7, 1, 0, 0, 0,
						   1, 7, 7, 7, 7, 7, 7, 1, 0, 0,
						   1, 7, 7, 7, 7, 7, 7, 7, 1, 0,
						   1, 7, 7, 7, 7, 7, 1, 1, 1, 1,
						   1, 7, 7, 1, 7, 7, 1, 0, 0, 0,
						   1, 7, 1, 0, 1, 7, 7, 1, 0, 0,
						   1, 1, 0, 0, 1, 7, 7, 1, 0, 0,
						   0, 0, 0, 0, 0, 1, 7, 7, 1, 0,
						   0, 0, 0, 0, 0, 1, 7, 7, 1, 0,
						   0, 0, 0, 0, 0, 0, 1, 1, 0, 0};

#define MOUSE_WIDTH 10
#define MOUSE_HEIGHT 15

static Gadget *hitgad = NULL;

/*****************************************************************************/
/* Checks whether or not the cords fall within one of the gadgets in a list  */
/* of gadgets.                                                               */
/*****************************************************************************/
static Gadget *checkGadgetHit(Gadget *gadlist, uint16 x, uint16 y) {
	uint16 counter;

	while (gadlist != NULL) {
		if ((x >= gadlist->x) && (y >= gadlist->y) &&
		        (x <= (gadlist->x + gadlist->Im->Width)) &&
		        (y <= (gadlist->y + gadlist->Im->Height)) &&
		        !(GADGETOFF & gadlist->GadgetFlags)) {
			if (IsHiRes) {
				hitgad = gadlist;
			} else {
				mouseHide();
				drawImage(gadlist->ImAlt, gadlist->x, gadlist->y);
				mouseShow();

				for (counter = 0; counter < 3; counter++)
					waitTOF();

				mouseHide();
				drawImage(gadlist->Im, gadlist->x, gadlist->y);
				mouseShow();
			}

			return gadlist;
		} else {
			gadlist = gadlist->NextGadget;
		}
	}

	return NULL;
}



void attachGadgetList(Gadget *GadList) {
	if (ScreenGadgetList != GadList)
		LastGadgetHit = NULL;

	ScreenGadgetList = GadList;
}

void mouseHandler(int32 flag, int32 mouseX, int32 mouseY) {
	if (NumHidden >= 2)
		return;

	if (!IsHiRes)
		mouseX /= 2;

	if (flag & 0x02) { /* Left mouse button click */
		Gadget *tmp = NULL;
		if (ScreenGadgetList)
			tmp = checkGadgetHit(ScreenGadgetList, mouseX, mouseY);

		if (tmp)
			LastGadgetHit = tmp;
		else
			LeftClick = true;
	}

	if (flag & 0x08) /* Right mouse button click */
		RightClick = true;
}

void updateMouse() {
	uint16 counter;
	bool doUpdateDisplay = false;

	if (!MouseHidden)
		doUpdateDisplay = true;

	if (hitgad) {
		mouseHide();
		drawImage(hitgad->ImAlt, hitgad->x, hitgad->y);
		mouseShow();

		for (counter = 0; counter < 3; counter++)
			waitTOF();

		mouseHide();
		drawImage(hitgad->Im, hitgad->x, hitgad->y);
		mouseShow();
		doUpdateDisplay = true;
		hitgad = NULL;
	}

	if (doUpdateDisplay)
		WSDL_UpdateScreen();
}


/*****************************************************************************/
/* Initializes the mouse.                                                    */
/*****************************************************************************/
void initMouse() {
	g_system->setMouseCursor(MouseData, MOUSE_WIDTH, MOUSE_HEIGHT, 0, 0, 0);
	g_system->showMouse(false);

	mouseMove(0, 0);
}


/*****************************************************************************/
/* Shows the mouse.                                                          */
/*****************************************************************************/
void mouseShow() {
	if (NumHidden)
		NumHidden--;

	if ((NumHidden == 0) && MouseHidden) {
		WSDL_ProcessInput(0);
		MouseHidden = false;
	}

	g_system->showMouse(true);
}

/*****************************************************************************/
/* Hides the mouse.                                                          */
/*****************************************************************************/
void mouseHide() {
	NumHidden++;

	if (NumHidden && !MouseHidden) {
		MouseHidden = true;

		g_system->showMouse(false);
	}
}


extern uint32 g_MouseX;
extern uint32 g_MouseY;

/*****************************************************************************/
/* Gets the current mouse co-ordinates.  NOTE: On IBM version, will scale    */
/* from virtual to screen co-ordinates automatically.                        */
/*****************************************************************************/
void mouseXY(uint16 *x, uint16 *y) {
	*x = (uint16)g_MouseX;
	*y = (uint16)g_MouseY;

	if (!IsHiRes)
		(*x) /= 2;
}


/*****************************************************************************/
/* Moves the mouse to new co-ordinates.                                      */
/*****************************************************************************/
void mouseMove(uint16 x, uint16 y) {
	if (!IsHiRes)
		x *= 2;

	g_system->warpMouse(x, y);

	if (!MouseHidden)
		WSDL_ProcessInput(0);
}


/*****************************************************************************/
/* Checks whether or not the mouse buttons have been pressed, and the last   */
/* co-ordinates of the button press.  leftbutton tells whether to check the  */
/* left or right button.                                                     */
/*****************************************************************************/
bool mouseButton(uint16 *x, uint16 *y, bool leftbutton) {
	if (leftbutton) {
		if (LeftClick) {
			*x = (!IsHiRes) ? (uint16)g_MouseX / 2 : (uint16)g_MouseX;
			*y = (uint16)g_MouseY;
			LeftClick = false;
			return true;
		}
	} else {
		if (RightClick) {
			*x = (!IsHiRes) ? (uint16)g_MouseX / 2 : (uint16)g_MouseX;
			*y = (uint16)g_MouseY;
			RightClick = false;
			return true;
		}
	}

	return false;
}




Gadget *mouseGadget() {
	Gadget *Temp = LastGadgetHit;

	LastGadgetHit = NULL;
	return Temp;
}

} // End of namespace Lab
