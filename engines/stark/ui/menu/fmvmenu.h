/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#ifndef STARK_UI_MENU_FMV_MENU_H
#define STARK_UI_MENU_FMV_MENU_H

#include "engines/stark/ui/menu/locationscreen.h"

#include "engines/stark/visual/text.h"

namespace Stark {

class FMVWidget;

/**
 * The video replay menu
 */
class FMVMenuScreen : public StaticLocationScreen {
public:
	FMVMenuScreen(Gfx::Driver *gfx, Cursor *cursor);
	virtual ~FMVMenuScreen();

	// StaticLocationScreen API
	void open() override;
	void close() override;

protected:
	// Window API
	void onMouseMove(const Common::Point &pos) override;
	void onClick(const Common::Point &pos) override;
	void onRender() override;

private:
	Common::Array<FMVWidget *> _fmvWidgets;

	void backHandler();

	void freeFMVWidgets();
};

/**
 * The widget for FMV entry, specifically built for FMVMenuScreen
 */
class FMVWidget {
public:
	FMVWidget(Gfx::Driver *gfx, int index);
	~FMVWidget() {}

	void render() { _title.render(_position); }

	bool isMouseInside(const Common::Point &mousePos) const;

	void onMouseMove(const Common::Point &mousePos) {
		setTextColor(isMouseInside(mousePos) ? _textColorHovered : _textColorDefault);
	}

	void onClick();

	void setTextColor(uint32 color) { _title.setColor(color); }

private:
	const static int _fmvPerPage = 18;
	const static int _height = 16;
	static const uint32 _textColorHovered = 0xFF961E1E;
	static const uint32 _textColorDefault = 0xFF000000;

	Common::String _filename;
	VisualText _title;

	int _width;
	Common::Point _position;
};

} // End of namespace Stark

#endif // STARK_UI_MENU_FMV_MENU_H
