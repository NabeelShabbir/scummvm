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

/*
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

//=============================================================================
// Author:   Arvind
// Purpose:  Contains the image manager class - used to manage in-game assets
//=============================================================================
#ifndef CRAB_IMAGEMANAGER_H
#define CRAB_IMAGEMANAGER_H

#include "crab/image/Image.h"
#include "crab/TMX/TMXTileSet.h"

#include "common/hashmap.h"

namespace Crab {

// We use this object as the key for all image assets
typedef uint ImageKey;

// Since we use uint as a key for images, our loadImgKey function is loadNum
#define loadImgKey loadNum

namespace pyrodactyl {
namespace image {
// We store images here
typedef Common::HashMap<ImageKey, Image> TextureMap;

// Two image maps are used in the game - current (changes with level) and common
enum MapID {
	MAP_CURRENT,
	MAP_COMMON,
	MAP_TOTAL
};

class ImageManager {
	// Assets are stored in images
	// Common is stuff used everywhere - this is only loaded once
	TextureMap _map[MAP_TOTAL];

	// The default image for all invalid image names
	Image _invalidImg;

public:
	// The tile sets used in the level
	TMX::TileSetGroup _tileset;

	// This image is used to notify player about changes to quests and inventory
	ImageKey _notify;

	ImageManager() {
		_notify = 0;
	}

	~ImageManager() {}

	void quit();

	bool init();
	// image related stuff

	// Load all images specified in an xml file in a map
	void loadMap(const Common::Path &filename, const MapID &mapid = MAP_CURRENT);

	void getTexture(const ImageKey &id, Image &data);
	Image &getTexture(const ImageKey &id);
	bool validTexture(const ImageKey &id);

	void draw(const int &x, const int &y, const ImageKey &id,
			  Common::Rect *clip = nullptr, const TextureFlipType &flip = FLIP_NONE);
	void draw(const int &x, const int &y, const ImageKey &id,
			  Rect *clip, const TextureFlipType &flip = FLIP_NONE);

	void dimScreen();
	void blackScreen();

	// Draw the notification icon
	void notifyDraw(const int &x, const int &y) {
		auto *k = &getTexture(_notify);
		draw(x - k->w() / 2, y - k->h() / 2, _notify);
	}
};

} // End of namespace image
} // End of namespace pyrodactyl

} // End of namespace Crab

#endif // CRAB_IMAGEMANAGER_H
