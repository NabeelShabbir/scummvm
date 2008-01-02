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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */



#include "common/config-manager.h"
#include "common/events.h"
#include "common/system.h"

#include "gui/message.h"
#include "gui/newgui.h"

#include "scumm/debugger.h"
#include "scumm/dialogs.h"
#include "scumm/insane/insane.h"
#include "scumm/imuse/imuse.h"
#ifndef DISABLE_HE
#include "scumm/he/intern_he.h"
#include "scumm/he/logic_he.h"
#endif
#include "scumm/scumm.h"
#include "scumm/sound.h"
#include "scumm/intern.h"


#ifdef _WIN32_WCE
#define		KEY_ALL_SKIP	3457
#endif

namespace Scumm {

enum MouseButtonStatus {
	msDown = 1,
	msClicked = 2
};

void ScummEngine::parseEvents() {
	Common::Event event;

	while (_eventMan->pollEvent(event)) {

		switch (event.type) {
		case Common::EVENT_KEYDOWN:
			if (event.kbd.keycode >= '0' && event.kbd.keycode <= '9'
				&& (event.kbd.flags == Common::KBD_ALT ||
					event.kbd.flags == Common::KBD_CTRL)) {
				_saveLoadSlot = event.kbd.keycode - '0';

				//  don't overwrite autosave (slot 0)
				if (_saveLoadSlot == 0)
					_saveLoadSlot = 10;

				sprintf(_saveLoadName, "Quicksave %d", _saveLoadSlot);
				_saveLoadFlag = (event.kbd.flags == Common::KBD_ALT) ? 1 : 2;
				_saveTemporaryState = false;
			} else if (event.kbd.flags == Common::KBD_CTRL && event.kbd.keycode == 'f') {
				_fastMode ^= 1;
			} else if (event.kbd.flags == Common::KBD_CTRL && event.kbd.keycode == 'g') {
				_fastMode ^= 2;
			} else if ((event.kbd.flags == Common::KBD_CTRL && event.kbd.keycode == 'd') ||
					event.kbd.ascii == '~' || event.kbd.ascii == '#') {
				_debugger->attach();
			} else if (event.kbd.flags == Common::KBD_CTRL && event.kbd.keycode == 's') {
				_res->resourceStats();
			} else {
				// Normal key press, pass on to the game.
				_keyPressed = event.kbd;
			}

			if (_game.heversion >= 80) {
				// FIXME: Move this code & VAR_KEY_STATE to class ScummEngine_v80he

				// Keyboard is controlled via variable
				int keyState = 0;

				if (event.kbd.keycode == Common::KEYCODE_LEFT) // Left
					keyState = 1;

				if (event.kbd.keycode == Common::KEYCODE_RIGHT) // Right
					keyState |= 2;

				if (event.kbd.keycode == Common::KEYCODE_UP) // Up
					keyState |= 4;

				if (event.kbd.keycode == Common::KEYCODE_DOWN) // Down
					keyState |= 8;

				if (event.kbd.flags == Common::KBD_SHIFT)
					keyState |= 16;

				if (event.kbd.flags == Common::KBD_CTRL)
					keyState |= 32;

				VAR(VAR_KEY_STATE) = keyState;
			}

			// FIXME: We are using ASCII values to index the _keyDownMap here,
			// yet later one code which checks _keyDownMap will use KEYCODEs
			// to do so. That is, we are mixing ascii and keycode values here,
			// which is bad. We probably should be only using keycodes, but at
			// least INSANE checks for "Shift-V" by looking for the 'V' key
			// being pressed. It would be easy to solve that by also storing
			// the modifier flags. However, since getKeyState() is also called
			// by scripts, we have to be careful with semantic changes.
			if (_keyPressed.ascii >= 512)
				debugC(DEBUG_GENERAL, "_keyPressed > 512 (%d)", _keyPressed.ascii);
			else
				_keyDownMap[_keyPressed.ascii] = true;
			break;

		case Common::EVENT_KEYUP:
			if (event.kbd.ascii >= 512) {
				debugC(DEBUG_GENERAL, "keyPressed > 512 (%d)", event.kbd.ascii);
			} else {
				_keyDownMap[event.kbd.ascii] = false;

				// Due to some weird bug with capslock key pressed
				// generated keydown event is for lower letter but
				// keyup is for upper letter
				// On most (all?) keyboards it is safe to assume that
				// both upper and lower letters are unpressed on keyup event
				//
				// Fixes bug #1709430: "FT: CAPSLOCK + V enables cheating for all fights"
				//
				// Fingolfin remarks: This wouldn't be a problem if we used keycodes.
				_keyDownMap[toupper(event.kbd.ascii)] = false;
			}
			break;


		// We update the mouse position whenever the mouse moves or a click occurs.
		// The latter is done to accomodate systems with a touchpad / pen controller.
		case Common::EVENT_LBUTTONDOWN:
		case Common::EVENT_RBUTTONDOWN:
		case Common::EVENT_MOUSEMOVE:
			if (event.type == Common::EVENT_LBUTTONDOWN)
				_leftBtnPressed |= msClicked|msDown;
			else if (event.type == Common::EVENT_RBUTTONDOWN)
				_rightBtnPressed |= msClicked|msDown;
			_mouse.x = event.mouse.x;
			_mouse.y = event.mouse.y;

			if (_renderMode == Common::kRenderHercA || _renderMode == Common::kRenderHercG) {
				_mouse.x -= (Common::kHercW - _screenWidth * 2) / 2;
				_mouse.x >>= 1;
				_mouse.y = _mouse.y * 4 / 7;
			} else if (_useCJKMode && _textSurfaceMultiplier == 2) {
				_mouse.x >>= 1;
				_mouse.y >>= 1;
			}
			break;
		case Common::EVENT_LBUTTONUP:
			_leftBtnPressed &= ~msDown;
			break;

		case Common::EVENT_RBUTTONUP:
			_rightBtnPressed &= ~msDown;
			break;

		// The following two cases enable dialog choices to be scrolled
		// through in the SegaCD version of MI. Values are taken from script-14.
		// See bug report #1193185 for details.
		case Common::EVENT_WHEELDOWN:
			if (_game.id == GID_MONKEY && _game.platform == Common::kPlatformSegaCD)
				_keyPressed = Common::KeyState(Common::KEYCODE_7, 55);	// '7'
			break;

		case Common::EVENT_WHEELUP:
			if (_game.id == GID_MONKEY && _game.platform == Common::kPlatformSegaCD)
				_keyPressed = Common::KeyState(Common::KEYCODE_6, 54);	// '6'
			break;

		case Common::EVENT_QUIT:
			_quit = true;
			break;

		default:
			break;
		}
	}
}

#ifndef DISABLE_HE
void ScummEngine_v90he::clearClickedStatus() {
	ScummEngine::clearClickedStatus();
	if (_game.heversion >= 98) {
		_logicHE->processKeyStroke(_keyPressed.ascii);
	}
}

void ScummEngine_v90he::processInput() {
	if (_game.heversion >= 98) {
		_logicHE->processKeyStroke(_keyPressed.ascii);
	}
	ScummEngine::processInput();
}
#endif

void ScummEngine::clearClickedStatus() {
	_keyPressed.reset();

	_mouseAndKeyboardStat = 0;
	_leftBtnPressed &= ~msClicked;
	_rightBtnPressed &= ~msClicked;
}

void ScummEngine_v0::processInput() {
	// F1 - F3
	if (_keyPressed.keycode >= Common::KEYCODE_F1 && _keyPressed.keycode <= Common::KEYCODE_F3) {
		switchActor(_keyPressed.keycode - Common::KEYCODE_F1);
	}

	ScummEngine::processInput();
}

void ScummEngine::processInput() {
	Common::KeyState lastKeyHit = _keyPressed;
	_keyPressed.reset();

	//
	// Clip the mouse coordinates, and compute _virtualMouse.x (and clip it, too)
	//
	if (_mouse.x < 0)
		_mouse.x = 0;
	if (_mouse.x > _screenWidth-1)
		_mouse.x = _screenWidth-1;
	if (_mouse.y < 0)
		_mouse.y = 0;
	if (_mouse.y > _screenHeight-1)
		_mouse.y = _screenHeight-1;

	VirtScreen *vs = &_virtscr[kMainVirtScreen];
	_virtualMouse.x = _mouse.x + vs->xstart;
	_virtualMouse.y = _mouse.y - vs->topline;
	if (_game.version >= 7)
		_virtualMouse.y += _screenTop;

	if (_virtualMouse.y < 0)
		_virtualMouse.y = -1;
	if (_virtualMouse.y >= vs->h)
		_virtualMouse.y = -1;

	//
	// Determine the mouse button state.
	//
	_mouseAndKeyboardStat = 0;

	// Interpret 'return' as left click and 'tab' as right click
	if (lastKeyHit.keycode && _cursor.state > 0) {
		if (lastKeyHit.keycode == Common::KEYCODE_TAB) {
			_mouseAndKeyboardStat = MBS_RIGHT_CLICK;
			lastKeyHit.reset();
		} else if (lastKeyHit.keycode == Common::KEYCODE_RETURN) {
			_mouseAndKeyboardStat = MBS_LEFT_CLICK;
			lastKeyHit.reset();
		}
	}

	if ((_leftBtnPressed & msClicked) && (_rightBtnPressed & msClicked) && _game.version >= 4) {
		// Pressing both mouse buttons is treated as if you pressed
		// the cutscene exit key (ESC) in V4+ games. That mimicks
		// the behaviour of the original engine where pressing both
		// mouse buttons also skips the current cutscene.
		_mouseAndKeyboardStat = 0;
		lastKeyHit = Common::KeyState(Common::KEYCODE_ESCAPE);
	} else if ((_rightBtnPressed & msClicked) && (_game.version <= 3 && _game.id != GID_LOOM)) {
		// Pressing right mouse button is treated as if you pressed
		// the cutscene exit key (ESC) in V0-V3 games. That mimicks
		// the behaviour of the original engine where pressing right
		// mouse button also skips the current cutscene.
		_mouseAndKeyboardStat = 0;
		lastKeyHit = Common::KeyState(Common::KEYCODE_ESCAPE);
	} else if (_leftBtnPressed & msClicked) {
		_mouseAndKeyboardStat = MBS_LEFT_CLICK;
	} else if (_rightBtnPressed & msClicked) {
		_mouseAndKeyboardStat = MBS_RIGHT_CLICK;
	}

	if (_game.version >= 6) {
		VAR(VAR_LEFTBTN_HOLD) = (_leftBtnPressed & msDown) != 0;
		VAR(VAR_RIGHTBTN_HOLD) = (_rightBtnPressed & msDown) != 0;

		if (_game.version >= 7) {
			VAR(VAR_LEFTBTN_DOWN) = (_leftBtnPressed & msClicked) != 0;
			VAR(VAR_RIGHTBTN_DOWN) = (_rightBtnPressed & msClicked) != 0;
		}
	}

	_leftBtnPressed &= ~msClicked;
	_rightBtnPressed &= ~msClicked;

#ifdef _WIN32_WCE
	if (lastKeyHit.ascii == KEY_ALL_SKIP) {
		// Skip talk
		if (VAR_TALKSTOP_KEY != 0xFF && _talkDelay > 0) {
			lastKeyHit = Common::KeyState(Common::KEYCODE_PERIOD);
		} else {
			lastKeyHit = Common::KeyState(Common::KEYCODE_ESCAPE);
		}
	}
#endif

	if (!lastKeyHit.ascii)
		return;

	processKeyboard(lastKeyHit);
}

#ifndef DISABLE_SCUMM_7_8
void ScummEngine_v8::processKeyboard(Common::KeyState lastKeyHit) {

	if (!(_game.features & GF_DEMO)) {
		// F1 (the trigger for the original save/load dialog) is mapped to F5
		if (lastKeyHit.keycode == Common::KEYCODE_F1 && lastKeyHit.flags == 0) {
			lastKeyHit = Common::KeyState(Common::KEYCODE_F5, 319);
		}

		// Alt-F5 should bring up the original save/load dialog, so map it to F1.
		if (lastKeyHit.keycode == Common::KEYCODE_F5 && lastKeyHit.flags == Common::KBD_ALT) {
			lastKeyHit = Common::KeyState(Common::KEYCODE_F1, 315);
		}
	}

	// If a key script was specified (a V8 feature), and it's trigger
	// key was pressed, run it. Usually used to display the built-in menu.
	if (_keyScriptNo && (_keyScriptKey == lastKeyHit.ascii)) {
		runScript(_keyScriptNo, 0, 0, 0);
		return;
	}

	// Fall back to V7 behavior
	ScummEngine_v7::processKeyboard(lastKeyHit);
}

void ScummEngine_v7::processKeyboard(Common::KeyState lastKeyHit) {
	const bool cutsceneExitKeyEnabled = (VAR_CUTSCENEEXIT_KEY == 0xFF || VAR(VAR_CUTSCENEEXIT_KEY) != 0);

	// VAR_VERSION_KEY (usually ctrl-v) is used in COMI, Dig and FT to trigger
	// a version dialog, unless VAR_VERSION_KEY is set to 0. However, the COMI
	// version string is hard coded in the engine, hence we don't invoke
	// versionDialog for it. Dig/FT version strings are partly hard coded, too.
	if (_game.id != GID_CMI && 0 != VAR(VAR_VERSION_KEY) &&
	    lastKeyHit.keycode == Common::KEYCODE_v && lastKeyHit.flags == Common::KBD_CTRL) {
		versionDialog();

	} else if (cutsceneExitKeyEnabled && lastKeyHit.keycode == Common::KEYCODE_ESCAPE) {
		// Skip cutscene (or active SMUSH video).
		if (_smushActive) {
			if (_game.id == GID_FT)
				_insane->escapeKeyHandler();
			else
				_smushVideoShouldFinish = true;
		}
		if (!_smushActive || _smushVideoShouldFinish)
			abortCutscene();

		_mouseAndKeyboardStat = Common::ASCII_ESCAPE;

	} else {
		// Fall back to V6 behavior
		ScummEngine_v6::processKeyboard(lastKeyHit);
	}
}
#endif

void ScummEngine_v6::processKeyboard(Common::KeyState lastKeyHit) {
	if (lastKeyHit.keycode == Common::KEYCODE_t && lastKeyHit.flags == Common::KBD_CTRL) {
		SubtitleSettingsDialog dialog(this, _voiceMode);
		_voiceMode = runDialog(dialog);

		switch (_voiceMode) {
		case 0:
			ConfMan.setBool("speech_mute", false);
			ConfMan.setBool("subtitles", false);
			break;
		case 1:
			ConfMan.setBool("speech_mute", false);
			ConfMan.setBool("subtitles", true);
			break;
		case 2:
			ConfMan.setBool("speech_mute", true);
			ConfMan.setBool("subtitles", true);
			break;
		}

		if (VAR_VOICE_MODE != 0xFF)
			VAR(VAR_VOICE_MODE) = _voiceMode;

		return;
	}

	// Fall back to default behavior
	ScummEngine::processKeyboard(lastKeyHit);
}

void ScummEngine_v2::processKeyboard(Common::KeyState lastKeyHit) {
	// Fall back to default behavior
	ScummEngine::processKeyboard(lastKeyHit);

	if (VAR_KEYPRESS != 0xFF && _mouseAndKeyboardStat) {		// Key Input
		if (315 <= _mouseAndKeyboardStat && _mouseAndKeyboardStat <= 323) {
			// Convert F-Keys for V1/V2 games (they start at 1)
			VAR(VAR_KEYPRESS) = _mouseAndKeyboardStat - 314;
		} else {
			VAR(VAR_KEYPRESS) = _mouseAndKeyboardStat;
		}
	}
}

void ScummEngine_v3::processKeyboard(Common::KeyState lastKeyHit) {
	// Fall back to default behavior
	ScummEngine::processKeyboard(lastKeyHit);

	// 'i' brings up an IQ dialog in Indy3
	if (lastKeyHit.ascii == 'i' && _game.id == GID_INDY3) {
		// SCUMM var 244 is the episode score
		// and var 245 is the series score
		char text[50];

		// FIXME: Currently, the series score does not work properly
		// This workaround just sets it equal to the episode score
		// However, at the end of the game, it does show the episode
		// score by itself
		int a = _scummVars[245];
		if (!a)
			a = _scummVars[244];

		sprintf(text, "IQ Points: Episode = %d, Series = %d", _scummVars[244], a);
		Indy3IQPointsDialog indy3IQPointsDialog(this, text);
		runDialog(indy3IQPointsDialog);
	}
}

void ScummEngine::processKeyboard(Common::KeyState lastKeyHit) {
	// Enable the following five special keys conditionally:
	bool restartKeyEnabled = (VAR_RESTART_KEY == 0xFF || VAR(VAR_RESTART_KEY) != 0);
	bool pauseKeyEnabled = (VAR_PAUSE_KEY == 0xFF || VAR(VAR_PAUSE_KEY) != 0);
	bool talkstopKeyEnabled = (VAR_TALKSTOP_KEY == 0xFF || VAR(VAR_TALKSTOP_KEY) != 0);
	bool cutsceneExitKeyEnabled = (VAR_CUTSCENEEXIT_KEY == 0xFF || VAR(VAR_CUTSCENEEXIT_KEY) != 0);
	bool mainmenuKeyEnabled = (VAR_MAINMENU_KEY == 0xFF || VAR(VAR_MAINMENU_KEY) != 0);

	// In FM-TOWNS games F8 / restart is always enabled
	if (_game.platform == Common::kPlatformFMTowns)
		restartKeyEnabled = true;

	// For games which use VAR_MAINMENU_KEY, disable the mainmenu key if
	// requested by the scripts. We make an exception for COMI (i.e.
	// forcefully always enable it there), as that always disables it.
	if (_game.id == GID_CMI)
		mainmenuKeyEnabled = true;

	if (mainmenuKeyEnabled && (lastKeyHit.keycode == Common::KEYCODE_F5 && lastKeyHit.flags == 0)) {
		if (VAR_SAVELOAD_SCRIPT != 0xFF && _currentRoom != 0)
			runScript(VAR(VAR_SAVELOAD_SCRIPT), 0, 0, 0);

		mainMenuDialog();		// Display NewGui

		if (VAR_SAVELOAD_SCRIPT != 0xFF && _currentRoom != 0)
			runScript(VAR(VAR_SAVELOAD_SCRIPT2), 0, 0, 0);

	} else if (restartKeyEnabled && (lastKeyHit.keycode == Common::KEYCODE_F8 && lastKeyHit.flags == 0)) {
		confirmRestartDialog();

	} else if (pauseKeyEnabled && (lastKeyHit.keycode == Common::KEYCODE_SPACE && lastKeyHit.flags == 0)) {
		pauseGame();

	} else if (talkstopKeyEnabled && (lastKeyHit.keycode == Common::KEYCODE_PERIOD && lastKeyHit.flags == 0)) {
		_talkDelay = 0;
		if (_sound->_sfxMode & 2)
			stopTalk();

	} else if (cutsceneExitKeyEnabled && (lastKeyHit.keycode == Common::KEYCODE_ESCAPE && lastKeyHit.flags == 0)) {
		abortCutscene();

		// FIXME: Is the following line really necessary?
		if (VAR_CUTSCENEEXIT_KEY != 0xFF)
			_mouseAndKeyboardStat = VAR(VAR_CUTSCENEEXIT_KEY);

	} else if (lastKeyHit.ascii == '[' || lastKeyHit.ascii == ']') { // Change music volume
		int vol = ConfMan.getInt("music_volume") / 16;
		if (lastKeyHit.ascii == ']' && vol < 16)
			vol++;
		else if (lastKeyHit.ascii == '[' && vol > 0)
			vol--;

		// Display the music volume
		ValueDisplayDialog dlg("Music volume: ", 0, 16, vol, ']', '[');
		vol = runDialog(dlg);

		vol *= 16;
		if (vol > Audio::Mixer::kMaxMixerVolume)
			vol = Audio::Mixer::kMaxMixerVolume;

		ConfMan.setInt("music_volume", vol);
		updateSoundSettings();

	} else if (lastKeyHit.ascii == '-' || lastKeyHit.ascii == '+') { // Change text speed
		if (lastKeyHit.ascii == '+' && _defaultTalkDelay > 0)
			_defaultTalkDelay--;
		else if (lastKeyHit.ascii == '-' && _defaultTalkDelay < 9)
			_defaultTalkDelay++;

		// Display the talk speed
		ValueDisplayDialog dlg("Subtitle speed: ", 0, 9, 9 - _defaultTalkDelay, '+', '-');
		_defaultTalkDelay = 9 - runDialog(dlg);

		// Save the new talkspeed value to ConfMan
		setTalkspeed(_defaultTalkDelay);

		if (VAR_CHARINC != 0xFF)
			VAR(VAR_CHARINC) = _defaultTalkDelay;

	} else {

		if (lastKeyHit.keycode >= Common::KEYCODE_F1 &&
		    lastKeyHit.keycode <= Common::KEYCODE_F9) {
			_mouseAndKeyboardStat = lastKeyHit.keycode - Common::KEYCODE_F1 + 315;

		} else if (_game.id == GID_MONKEY2 && (lastKeyHit.flags & Common::KBD_ALT)) {
			// Handle KBD_ALT combos in MI2. We know that the result must be 273 for Alt-W
			// because that's what MI2 looks for in its "instant win" cheat.
			_mouseAndKeyboardStat = lastKeyHit.keycode + 154;

		} else if (lastKeyHit.keycode >= Common::KEYCODE_UP &&
		          lastKeyHit.keycode <= Common::KEYCODE_LEFT) {
			if (_game.id == GID_MONKEY && _game.platform == Common::kPlatformSegaCD) {
				// Map arrow keys to number keys in the SEGA version of MI to support
				// scrolling to conversation choices. See bug report #1193185 for details.
				_mouseAndKeyboardStat = lastKeyHit.keycode - Common::KEYCODE_UP + 54;
			} else if (_game.version >= 7) {
				// Don't let pre-V7 game see arrow keys. This fixes bug with up arrow (273)
				// corresponding to the "instant win" cheat in MI2 mentioned above.
				//
				// This is not applicable to V7+ games, which need to see the arrow keys,
				// too, else certain things (derby scene, asterorid lander) won't work.
				_mouseAndKeyboardStat = lastKeyHit.ascii;
			}

		} else {
			_mouseAndKeyboardStat = lastKeyHit.ascii;
		}
	}
}

} // End of namespace Scumm
