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
 * aint32 with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Based on the original sources
 *   Faery Tale II -- The Halls of the Dead
 *   (c) 1993-1996 The Wyrmkeep Entertainment Co.
 */

#define FORBIDDEN_SYMBOL_ALLOW_ALL // FIXME: Remove

#include "common/config-manager.h"

#include "saga2/std.h"
#include "saga2/cmisc.h"
#include "saga2/input.h"
#include "saga2/fta.h"
#include "saga2/player.h"
#include "saga2/tromode.h"
#include "saga2/display.h"

#include "saga2/mainmap.h"
#include "saga2/config.h"

namespace Saga2 {

#define VIDEO_EXTENSION ".SMK"

#define INTRO_VID1  "TRIMARK" VIDEO_EXTENSION
#define INTRO_VID2  "INTRO" VIDEO_EXTENSION

#define WIN_VID_1   "END_1" VIDEO_EXTENSION
#define WIN_VID_2   "END_2" VIDEO_EXTENSION
#define WIN_VID_3   "END_3A" VIDEO_EXTENSION
#define WIN_VID_4   "END_3B" VIDEO_EXTENSION

#define LOSE_VID    "END_4" VIDEO_EXTENSION


#define ERASE_BETWEEN TRUE
#define VIDEO_X 0
#define VIDEO_Y 0

extern bool gameRunning;
extern gMouseState  prevState;
extern gMousePointer    pointer;
extern MouseExtState mouseQueue[];
extern configuration    globalConfig;
extern bool allPlayerActorsDead;

extern int16        queueIn,
       queueOut;

int16 OptionsDialog(bool disableSaveResume = FALSE);
void SystemEventLoop(void);
void ClearMessageQueue(void);
void freeAllTileBanks(void);
void PollMouse(void);
void resetInputDevices(void);
void blackOut(void);
void quickSavePalette(void);
void quickRestorePalette(void);
void cursorFullHide(bool onOff);
#ifdef _WIN32
void suspendWinTimer(void);
void resumeWinTimer(void);
#endif

static void doIntro(void);
static void doWintro(int16 whichOne);
static void doLostro(void);

static void waitForVideo(void);
void waitForInput(void);

static void TroModeSetup(void);
static void TroModeCleanup(void);

static bool abortFlag = FALSE;
#ifndef NO_LOAD_AFTER_WIN
//DO_OUTRO_IN_CLEANUP
static int whichOutro = -1;
#endif

// ------------------------------------------------------------------------
// Play intro video

void setIntroMode(void) {
	blackOut();
	if (!abortFlag) {
		TroModeSetup();
		doIntro();
		TroModeCleanup();
	}
	showLoadMessage();
	resetInputDevices();
}

// ------------------------------------------------------------------------
// Play outro video

void setOutroMode(void) {
}

// ------------------------------------------------------------------------
// Winning videos
extern GameWorld            *currentWorld;          // pointer to the current world

void setWintroMode(int16 whichOne) {
#ifdef NO_LOAD_AFTER_WIN
	if (!abortFlag) {
		freeAllTileBanks();
		currentWorld = NULL;
		TroModeSetup();
		doWintro(whichOne);
		TroModeCleanup();
	}
	endGame();
#else
	whichOutro = whichOne;
	allPlayerActorsDead = TRUE;
#endif
}

// ------------------------------------------------------------------------
// Losing video

void fadeDown();
void fadeUp();
void dumpGBASE(char *msg);

void setLostroMode(void) {
	allPlayerActorsDead = FALSE;
	if (GameMode::newmodeFlag)
		GameMode::update();

	if (!abortFlag) {
		freeAllTileBanks();
		TroModeSetup();
		if (whichOutro >= 0)
			doWintro(whichOutro);
		else
			doLostro();
		whichOutro = -1;
		TroModeCleanup();
	}
	OptionsDialog(TRUE);
	reDrawScreen();
}

/* ===================================================================== *
   Entry & termination
 * ===================================================================== */

void TroModeExternEvent(void) {
	abortFlag = TRUE;
}

// ------------------------------------------------------------------------
// Entry code

static void TroModeSetup(void) {
	suspendAudio();
	pointer.hide();
#ifdef _WIN32
	cursorFullHide(TRUE);
#endif
	quickSavePalette();
	blackOut();
	displayDisable(PlayingVideo);
	pushVidState();
	ClearMessageQueue();
	resetInputDevices();
	abortFlag = FALSE;
}

// ------------------------------------------------------------------------
// Exit

static void TroModeCleanup(void) {
	g_vm->endVideo();
	popVidState();
	displayEnable(PlayingVideo);
	blackOut();
	quickRestorePalette();
	resumeAudio();
#ifdef _WIN32
	cursorFullHide(FALSE);
#endif
	pointer.show();
//	pointer.manditoryShow();                     //  hide mouse pointer
	resetInputDevices();
}

/* ===================================================================== *
   Wait for Event type routines
 * ===================================================================== */

// ------------------------------------------------------------------------
// Wait till a video completes

static void waitForVideo(void) {
	while (g_vm->checkVideo()) {
		SystemEventLoop();
		if (abortFlag)
			return;

		g_system->delayMillis(10);
	}
}

// ------------------------------------------------------------------------
// Wait till the user hits a key or clicks or screams or whatever

void waitForInput(void) {
	abortFlag = FALSE;
	while (!abortFlag) {
		SystemEventLoop();
		if (abortFlag)
			return;

		g_system->updateScreen();
		g_system->delayMillis(10);
	}
}

/* ===================================================================== *
   Video playback
 * ===================================================================== */

static void playAVideo(const char *fileName, int x, int y) { //, int16 from, int16 to )
	g_vm->startVideo(fileName, x, y);
	if (!g_vm->checkVideo()) {
		g_vm->endVideo();
		abortFlag = TRUE;
		return;
	}
	waitForVideo();
}


/* ===================================================================== *
   These are the actual video routines
 * ===================================================================== */

// ------------------------------------------------------------------------
// intro video(s)

static void doIntro(void) {
	playAVideo(INTRO_VID1, 0, 0);
	abortFlag = FALSE;
	playAVideo(INTRO_VID2, 0, 0);
}

// ------------------------------------------------------------------------
// one of several endings

static void doWintro(int16 whichOne) {
	switch (whichOne) {
	case 0:
		playAVideo(WIN_VID_1, 0, 0);
		return;
	case 1:
		playAVideo(WIN_VID_2, 0, 0);
		return;
	case 2:
		playAVideo(WIN_VID_3, 0, 0);
		return;
	case 3:
		playAVideo(WIN_VID_4, 0, 0);
		return;
	}
}

// ------------------------------------------------------------------------
// lost

static void doLostro(void) {
	playAVideo(LOSE_VID, 0, 0);
}

} // end of namespace Saga2
