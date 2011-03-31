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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm-misc.svn.sourceforge.net/svnroot/scummvm-misc/trunk/engines/tsage/scene_logic.cpp $
 * $Id: scene_logic.cpp 232 2011-02-12 11:56:38Z dreammaster $
 *
 */

#include "graphics/cursorman.h"
#include "tsage/ringworld_scenes10.h"
#include "tsage/scenes.h"
#include "tsage/tsage.h"
#include "tsage/staticres.h"

namespace tSage {
/*--------------------------------------------------------------------------
 * Scene 9100
 *
 *--------------------------------------------------------------------------*/
void Scene9100::SceneHotspot1::doAction(int action) {
	Scene9100 *scene = (Scene9100 *)_globals->_sceneManager._scene;

	if (action == CURSOR_TALK) {
		if (_globals->getFlag(23)) {
			_globals->_player.disableControl();
			scene->_sceneMode = 9104;
		} else {
			_globals->setFlag(23);
			_globals->_player.disableControl();
			scene->_sceneMode = 9105;
		}
		scene->setAction(&scene->_sequenceManager, scene, scene->_sceneMode, &_globals->_player, &scene->_object5, &scene->_object6, 0);
	} else {
		SceneHotspot_3::doAction(action);
	}
}

void Scene9100::dispatch() {
	Scene9100 *scene = (Scene9100 *)_globals->_sceneManager._scene;
	
	if (!_action) {
		if (_globals->_player._position.x < 25) {
			warning("There");
			if (!_globals->getFlag(11)) {
				scene->_sceneMode = 9106;
			} else {
				scene->_sceneMode = 9108;
				_globals->setFlag(11);
			}
		} else {
			scene->_sceneMode = 9106;
		}
		scene->setAction(&scene->_sequenceManager, scene, scene->_sceneMode, &_globals->_player, 0);
	} else {
		Scene::dispatch();
	}
}

void Scene9100::signal() {
	Scene9100 *scene = (Scene9100 *)_globals->_sceneManager._scene;

	switch (scene->_sceneMode) {
	case 9102:
	case 9106:
	case 9108:
		_globals->_sceneManager.changeScene(9150);
		break;
	case 9105:
		_sceneHotspot1.remove();
	// No break on purpose
	case 9103:
	case 9104:
	case 9107:
	case 9109:
	default:
		_globals->_player.enableControl();
		break;
	}
}

void Scene9100::postInit(SceneObjectList *OwnerList) {
	Scene9100 *scene = (Scene9100 *)_globals->_sceneManager._scene;

	Scene::postInit();
	setZoomPercents(0, 100, 200, 100);
	_object1.postInit();
	_object1.setVisage(9100);
	_object1._strip = 1;
	_object1._numFrames = 6;
	_object1.setPosition(Common::Point(297, 132), 0);
	_object1.animate(ANIM_MODE_2, 0);
	_object1.setPriority2(10);

	_globals->_player.postInit();

	_object2.postInit();
	_object2.flag100();

	_object3.postInit();
	_object3.flag100();

	_object4.postInit();
	_object4.flag100();

	_object5.postInit();
	_object5.flag100();

	if (!_globals->getFlag(23)) {
		_object6.postInit();
		_object6.setVisage(9111);
		_object6.setStrip(6);
		_object6.setFrame(1);
		_object6.setPosition(Common::Point(138, 166), 0);
		_sceneHotspot3.quickInit(145, 125, 166, 156, 9100, 40, 43);
	}
	_sceneHotspot1.quickInit(140, 176, 185, 215, 9100, 36, 37);
	_sceneHotspot2.quickInit(161, 138, 182, 175, 9100, 38, 39);
	_sceneHotspot4.quickInit(37, 196, 47, 320, 9100, 44, -1);
	_sceneHotspot5.quickInit(69, 36, 121, 272, 9100, 45, 46);
	_sceneHotspot6.quickInit(127, 0, 200, 52, 9100, 47, 48);

	_globals->_soundHandler.startSound(251, 0, 127);
	if (_globals->_sceneManager._previousScene == 9150) {
		if (_globals->getFlag(20)) {
			_globals->_player.disableControl();
			if (_globals->getFlag(11))
				_sceneMode = 9107;
			else
				_sceneMode = 9109;
			setAction(&scene->_sequenceManager, scene, _sceneMode, &_globals->_player, &_object5, 0);
		} else {
			_sceneMode = 9103;
			_globals->_player.disableControl();
			setAction(&scene->_sequenceManager, scene, _sceneMode, &_globals->_player, &_object2, &_object3, &_object4, &_object5, 0);
			_globals->setFlag(20);
		}
	} else {
		_sceneMode = 9102;
		_globals->_player.disableControl();
		setAction(&scene->_sequenceManager, scene, _sceneMode, &_globals->_player, &_object2, &_object3, &_object4, &_object5, 0);
	}
}

/*--------------------------------------------------------------------------
 * Scene 9150
 *
 *--------------------------------------------------------------------------*/
void Scene9150::Object3::signal() {
	switch (_field8A++) {
	case 0:
		_field88 = 10 + _globals->_randomSource.getRandomNumber(90);
		break;
	default:	
		animate(ANIM_MODE_5, this);
		_field88 = 0;
		break;
	}
}

void Scene9150::Object3::dispatch() {
	SceneObject::dispatch();
	if ((_field88 != 0) && (--_field88 == 0))
		signal();
}

void Scene9150::signal() {
	switch (_sceneMode) {
	case 9151:
	case 9157:
		_globals->_sceneManager.changeScene(9100);
		break;
	case 9153:
		_globals->_sceneManager.changeScene(9300);
		break;
	case 9152:
	case 9155:
	case 9156:
		_globals->_player.enableControl();
		break;
	case 9154:
	default:
		break;
	}
}

void Scene9150::dispatch() {

	if ((_field30A != 0) && (_sceneBounds.left == 0)) {
		_object3._field88 = 0;
		_field30A = 0;
		_sceneHotspot3.setAction(&_sequenceManager2, 0, 9154, &_object3, 0);
		_sceneHotspot10.remove();
	}
	
	if (_action) {
		_action->dispatch();
	} else {
		if (_globals->_player._position.x >= 160) {
			if (_globals->_player._position.x > 630) {
				_globals->_player.disableControl();
				_sceneMode = 9157;
				setAction(&_sequenceManager1, this, _sceneMode, &_globals->_player, 0);
			}
		} else {
			_globals->_player.disableControl();
			if (_globals->getFlag(11)) {
				_globals->_soundHandler.startSound(286, 0, 127);
				_sceneMode = 9153;
			} else {
				_sceneMode = 9156;
			}
			setAction(&_sequenceManager1, this, _sceneMode, &_globals->_player, 0);
		}
	}
}

void Scene9150::postInit(SceneObjectList *OwnerList) {
	Scene::postInit();
	setZoomPercents(0, 100, 200, 100);
	_globals->_player.postInit();

	_object3.postInit();
	_field30A = 1;
	_object3.setVisage(9151);
	_object3._strip = 1;
	_object3._frame = 1;
	_object3.setPosition(Common::Point(312, 95), 0);
	_object3.signal();

	_sceneHotspot1.quickInit(0, 0, 200, 94, 9150, 46, -1);
	_sceneHotspot2.quickInit(51, 90, 118, 230, 9150, 47, -1);
	_sceneHotspot3.quickInit(182, 104, 200, 320, 9150, 48, 49);
	_sceneHotspot4.quickInit(103, 292, 152, 314, 9150, 50, 51);
	_sceneHotspot5.quickInit(115, 350, 160, 374, 9150, 52, 53);
	_sceneHotspot6.quickInit(0, 471, 200, 531, 9150, 54, 55);
	_sceneHotspot7.quickInit(170, 320, 185, 640, 9150, 56, -1);
	_sceneHotspot9.quickInit(157, 107, 186, 320, 9150, 56, -1);
	_sceneHotspot8.quickInit(133, 584, 142, 640, 9150, 57, -1);
	_sceneHotspot10.quickInit(83, 304, 103, 323, 9150, 58, 59);

	_globals->_soundHandler.startSound(285, 0, 127);
	_globals->_player.disableControl();

	if (_globals->getFlag(20)) {
		// Walking alone
		_globals->_scrollFollower = &_globals->_player;
		if (_globals->getFlag(11))
			// Hero wearing peasan suit
			_sceneMode = 9155;
		else
			// Hero wearing Purple suit
			_sceneMode = 9152;
		setAction(&_sequenceManager1, this, _sceneMode, &_globals->_player, 0);
	} else {
		// Walking with the tiger
		_sceneMode = 9151;
		_object2.postInit();
		_object2.flag100();
		_object1.postInit();
		setAction(&_sequenceManager1, this, _sceneMode, &_globals->_player, &_object1, &_object2, 0);
	}
}

/*--------------------------------------------------------------------------
 * Scene 9350
 *
 *--------------------------------------------------------------------------*/
void Scene9350::Object1::postInit(SceneObjectList *OwnerList) {
	warning("Scene9350::Object1::postInit - Weird cast to be verified");
	_globals->_sceneManager.postInit((SceneObjectList*) &_globals->_sceneManager._sceneChangeListeners);
}

void Scene9350::Object1::draw() {
	warning("Scene9350::Object1::draw - TODO");
}

void Scene9350::signal() {
	switch (_field30A ++) {
	case 0:
	case 9352:
	case 9353:
	case 9354:
		_globals->_player.enableControl();
		break;
	case 9355:
		_globals->_sceneManager.changeScene(9300);
		break;
	case 9356:
		_globals->_sceneManager.changeScene(9360);
		break;
	case 9357:
	case 9359:
		_globals->_sceneManager.changeScene(9400);
		break;
	default:
		break;
	}
}

void Scene9350::dispatch() {
	if (_action == 0) {
		if ((_globals->_player._position.x <= 300) || (_globals->_player._position.y >= 160)) {
			if ((_globals->_player._position.x <= 110) || (_globals->_player._position.y < 195)) {
				_globals->_player.disableControl();
				_field30A = 9355;
				Scene::setAction(&_sequenceManager, this, 9355, &_globals->_player, &_object2, 0);
			} else {
				_globals->_player.disableControl();
				_field30A = 9357;
				Scene::setAction(&_sequenceManager, this, 9357, &_globals->_player, &_object2, 0);
			}
		} else {
			_globals->_player.disableControl();
			_field30A = 9356;
			Scene::setAction(&_sequenceManager, this, 9356, &_globals->_player, &_object2, 0);
		}
	} else {
		Scene::dispatch();
	}
}

void Scene9350::postInit(SceneObjectList *OwnerList) {
	Scene::postInit();
	setZoomPercents(95, 80, 200, 100);
	_globals->_player.postInit();

	_object1.quickInit(9350, 1, 3, 139, 97, 0);
	_sceneHotspot1.quickInit(42, 0, 97, 60, 9350, 0, -1);
	_sceneHotspot2.quickInit(37, 205, 82, 256, 9350, 0, -1);
	_sceneHotspot3.quickInit(29, 93, 92, 174, 9350, 1, -1);
	_sceneHotspot4.quickInit(0, 308, 109, 320, 9350, 2, -1);
	_sceneHotspot5.quickInit(0, 0, 200, 320, 9350, 3, -1);

	_globals->_events.setCursor(CURSOR_WALK);
	_globals->_player.disableControl();

	if (_globals->_sceneManager._previousScene == 9360) {
		_globals->_player.disableControl();
		_field30A = 9352;
		setAction(&_sequenceManager, this, 9352, &_globals->_player, &_object2, 0);
	} else if (_globals->_sceneManager._previousScene == 9400) {
		_globals->_player.disableControl();
		_field30A = 9353;
		setAction(&_sequenceManager, this, 9353, &_globals->_player, &_object2, 0);
	} else {
		if (!_globals->getFlag(84)) {
			_globals->clearFlag(84);
			_object2.postInit();
			_globals->_player.disableControl();
			_field30A = 9359;
			setAction(&_sequenceManager, this, 9359, &_globals->_player, &_object2, 0);
		} else {
			_globals->_player.disableControl();
			_field30A = 9354;
			setAction(&_sequenceManager, this, 9354, &_globals->_player, &_object2, 0);
		}
	}
}

/*--------------------------------------------------------------------------
 * Scene 9700
 *
 *--------------------------------------------------------------------------*/
void Scene9700::signal() {
	switch (_sceneMode ++) {
	case 9703:
		_globals->setFlag(88);
		// No break on purpose
	case 9701:
	case 9702:
		_gfxButton1.setText(EXIT_MSG);
		_gfxButton1._bounds.centre(50, 190);
		_gfxButton1.draw();
		_gfxButton1._bounds.expandPanes();
		_globals->_player.enableControl();
		_globals->_player._canWalk = 0;
		_globals->_events.setCursor(CURSOR_USE);

		break;
	case 9704:
		_globals->_soundHandler.startSound(323, 0, 127);
		_globals->_sceneManager.changeScene(9750);
		break;
	}
}

void Scene9700::process(Event &event) {
	if ((event.eventType == EVENT_BUTTON_DOWN) && (event.kbd.keycode == 0)) {
		if (_gfxButton1.process(event)) {
			_globals->_sceneManager.changeScene(9200);
		} else if (_globals->_events._currentCursor == OBJECT_SCANNER) {
			event.handled = true;
			if (_globals->_inventory._helmet._sceneNumber == 1) {
				_globals->_player.disableControl();
				_sceneMode = 9704;
				setAction(&_sequenceManager, this, 9704, &_globals->_player, &_object1, 0);
			} else {
				_globals->_player.disableControl();
				_sceneMode = 9703;
				setAction(&_sequenceManager, this, 9703, &_globals->_player, &_object1, 0);
			}
		}
	}
}

void Scene9700::postInit(SceneObjectList *OwnerList) {
	Scene::postInit();
	setZoomPercents(0, 100, 200, 100);

	_sceneHotspot1.quickInit(84, 218, 151, 278, 9700, 14, -1);
	_sceneHotspot2.quickInit(89, 11, 151, 121, 9700, 14, -1);
	_sceneHotspot3.quickInit(69, 119, 138, 218, 9700, 15, 16);
	_sceneHotspot4.quickInit(34, 13, 88, 116, 9700, 17, -1);
	_sceneHotspot5.quickInit(52, 119, 68, 204, 9700, 17, -1);
	_sceneHotspot6.quickInit(0, 22, 56, 275, 9700, 18, -1);

	_object1.postInit();
	_object1.flag100();
	_globals->_player.postInit();
	if (_globals->getFlag(97)) {
		_globals->_player.disableControl();
		_sceneMode = 9701;
		setAction(&_sequenceManager, this, 9701, &_globals->_player, &_object1, 0);
		_globals->setFlag(97);
	} else {
		_globals->_player.disableControl();
		_sceneMode = 9702;
		setAction(&_sequenceManager, this, 9702, &_globals->_player, &_object1, 0);
	}
}

/*--------------------------------------------------------------------------
 * Scene 9750
 *
 *--------------------------------------------------------------------------*/
void Scene9750::signal() {
	switch (_sceneMode ++) {
	case 9751:
		_globals->_soundHandler.proc1(this);
		break;
	case 9752:
		_globals->_sceneManager.changeScene(2100);		
	default:
		break;
	}
}

void Scene9750::dispatch() {
	Scene::dispatch();
}

void Scene9750::postInit(SceneObjectList *OwnerList) {
	loadScene(9750);
	Scene::postInit();
	setZoomPercents(0, 100, 200, 100);
	
	_globals->_player.postInit();
	_object1.postInit();
	_object1.flag100();
	_object2.postInit();
	_object2.flag100();
	_globals->_player.disableControl();
	_sceneMode = 9751;
	setAction(&_sequenceManager, this, 9751, &_globals->_player, &_object1, &_object2, 0);
}

/*--------------------------------------------------------------------------
 * Scene 9999
 *
 *--------------------------------------------------------------------------*/

void Scene9999::Action1::signal() {
	switch (_actionIndex++) {
	case 0:
		setDelay(600);
		break;
	case 1:
		_globals->_sceneManager.changeScene(3500);
		break;
	default:
		break;
	}
}

/*--------------------------------------------------------------------------*/

void Scene9999::Action2::signal() {
	switch (_actionIndex++) {
	case 0:
		setDelay(10);
		break;
	case 1:
		SceneItem::display(9999, 0, SET_Y, 10, SET_X, 30, SET_FONT, 2, SET_BG_COLOUR, -1, SET_EXT_BGCOLOUR, 23, SET_WIDTH, 260, SET_KEEP_ONSCREEN, 1, LIST_END);
		setDelay(300);
		break;
	case 2:
		_globals->_stripNum = 3600;
		_globals->_sceneManager.changeScene(3600);
	default:
		break;
	}
}

void Scene9999::postInit(SceneObjectList *OwnerList) {
	loadScene(9998);
	Scene::postInit();
	setZoomPercents(0, 100, 200, 100);
	
	_object1.postInit();
	_object1.setVisage(1303);
	_object1.setStrip2(3);
	_object1.setPosition(Common::Point(160, 152), 0);
	
	_globals->_player.postInit();
	_globals->_player.setVisage(1303);
	_globals->_player.setStrip2(1);
	_globals->_player.setPriority2(250);
	_globals->_player.animate(ANIM_MODE_2, 0);
	_globals->_player.setPosition(Common::Point(194, 98), 0);
	_globals->_player._numFrames = 20;
	_globals->_player.disableControl();

	_object2.postInit();
	_object2.setVisage(1303);
	_object2.setStrip2(2);
	_object2.setPriority2(2);
	_object2.setPosition(Common::Point(164, 149), 0);

	_object3.postInit();
	_object3.setVisage(1303);
	_object3.setStrip2(2);
	_object3.setPriority2(2);
	_object3.setFrame(2);
	_object3.setPosition(Common::Point(292, 149), 0);
	_object3.setAction(&_action3);

	if (_globals->_sceneManager._previousScene == 3500)
		setAction(&_action2);
	else
		setAction(&_action1);

	_globals->_sceneManager._scene->_sceneBounds.centre(_globals->_player._position.x, _globals->_player._position.y);
	_globals->_sceneManager._scene->_sceneBounds.contain(_globals->_sceneManager._scene->_backgroundBounds);
	_globals->_sceneOffset.x = (_globals->_sceneManager._scene->_sceneBounds.left / 160) * 160;

	if (_globals->_sceneManager._previousScene == 3500)
		_globals->_stripNum = 2222;
	else
		_globals->_stripNum = 2121;

	_globals->_soundHandler.startSound(118, 0, 127);

}

} // End of namespace tSage
