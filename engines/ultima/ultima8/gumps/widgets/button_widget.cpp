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

#include "ultima/ultima8/misc/pent_include.h"
#include "ultima/ultima8/gumps/widgets/button_widget.h"
#include "ultima/ultima8/gumps/widgets/text_widget.h"
#include "ultima/ultima8/games/game_data.h"
#include "ultima/ultima8/graphics/shape_frame.h"
#include "ultima/ultima8/graphics/shape_archive.h"
#include "ultima/ultima8/graphics/shape.h"
#include "ultima/ultima8/kernel/mouse.h"
#include "ultima/ultima8/world/get_object.h"

#include "ultima/ultima8/filesys/idata_source.h"
#include "ultima/ultima8/filesys/odata_source.h"

namespace Ultima {
namespace Ultima8 {

// p_dynamic_class stuff
DEFINE_RUNTIME_CLASSTYPE_CODE(ButtonWidget, Gump)

ButtonWidget::ButtonWidget()
	: Gump() {
}

ButtonWidget::ButtonWidget(int X, int Y, Std::string txt, bool gamefont,
                           int font, uint32 mouseOverBlendCol_,
                           int w, int h, int32 layer_) :
	Gump(X, Y, w, h, 0, 0, layer_), shape_up(0), shape_down(0),
	mouseOver(false), origw(w), origh(h) {
	TextWidget *widget = new TextWidget(0, 0, txt, gamefont, font, w, h);
	textwidget = widget->getObjId();
	mouseOverBlendCol = mouseOverBlendCol_;
	mouseOver = (mouseOverBlendCol != 0);
}

ButtonWidget::ButtonWidget(int X, int Y, FrameID frame_up, FrameID frame_down,
                           bool _mouseOver, int32 layer_)
	: Gump(X, Y, 5, 5, 0, 0, layer_), textwidget(0), mouseOver(_mouseOver) {
	shape_up = GameData::get_instance()->getShape(frame_up);
	shape_down = GameData::get_instance()->getShape(frame_down);
	_frameNum_up = frame_up._frameNum;
	_frameNum_down = frame_down._frameNum;
}


ButtonWidget::~ButtonWidget(void) {
}

void ButtonWidget::InitGump(Gump *newparent, bool take_focus) {
	Gump::InitGump(newparent, take_focus);

	if (textwidget != 0) {
		Gump *widget = getGump(textwidget);
		assert(widget);
		widget->InitGump(this);
		widget->GetDims(_dims); // transfer child dimension to self
		widget->Move(0, _dims.y); // move it to the correct height
	} else {
		assert(shape_up != 0);
		assert(shape_down != 0);

		_shape = shape_up;
		_frameNum = _frameNum_up;

		ShapeFrame *sf = _shape->getFrame(_frameNum);
		assert(sf);
		_dims.w = sf->width;
		_dims.h = sf->height;
	}
}

int ButtonWidget::getVlead() {
	if (textwidget != 0) {
		Gump *widget = getGump(textwidget);
		TextWidget *txtWidget = p_dynamic_cast<TextWidget *>(widget);
		assert(txtWidget);
		return txtWidget->getVlead();
	} else {
		return 0;
	}
}

bool ButtonWidget::PointOnGump(int mx, int my) {
	// CHECKME: this makes the ButtonWidget accept any point in its rectangle,
	// effectively ignoring shape transparency. For some buttons (like those
	// in U8's diary), this is desirable. For others it may not be, so this
	// behaviour may need to be changed. (bool ignoreShapeTransparency or
	// something)

	int32 gx = mx, gy = my;
	ParentToGump(gx, gy);

	return _dims.InRect(gx, gy);
}

Gump *ButtonWidget::OnMouseDown(int button, int32 mx, int32 my) {
	Gump *ret = Gump::OnMouseDown(button, mx, my);
	if (ret) return ret;
	if (button == Shared::BUTTON_LEFT) {
		// CHECKME: change dimensions or not?
		if (!mouseOver) {
			_shape = shape_down;
			_frameNum = _frameNum_down;
		}
		return this;
	}
	return 0;
}

uint16 ButtonWidget::TraceObjId(int32 mx, int32 my) {
	if (PointOnGump(mx, my))
		return getObjId();
	else
		return 0;
}


void ButtonWidget::OnMouseUp(int button, int32 mx, int32 my) {
	if (button == Shared::BUTTON_LEFT) {
		if (!mouseOver) {
			_shape = shape_up;
			_frameNum = _frameNum_up;
		}
		_parent->ChildNotify(this, BUTTON_UP);
	}
}

void ButtonWidget::OnMouseClick(int button, int32 mx, int32 my) {
	int gx = mx, gy = my;
	if (PointOnGump(gx, gy))
		_parent->ChildNotify(this, BUTTON_CLICK);
}

void ButtonWidget::OnMouseDouble(int button, int32 mx, int32 my) {
	_parent->ChildNotify(this, BUTTON_DOUBLE);
}

void ButtonWidget::OnMouseOver() {
	if (mouseOver) {
		if (textwidget) {
			Gump *widget = getGump(textwidget);
			TextWidget *txtWidget = p_dynamic_cast<TextWidget *>(widget);
			assert(txtWidget);
			txtWidget->setBlendColour(mouseOverBlendCol);
		} else {
			_shape = shape_down;
			_frameNum = _frameNum_down;
		}
	}
}

void ButtonWidget::OnMouseLeft() {
	if (mouseOver) {
		if (textwidget) {
			Gump *widget = getGump(textwidget);
			TextWidget *txtWidget = p_dynamic_cast<TextWidget *>(widget);
			assert(txtWidget);
			txtWidget->setBlendColour(0);
		} else {
			_shape = shape_up;
			_frameNum = _frameNum_up;
		}
	}
}

void ButtonWidget::saveData(ODataSource *ods) {
	// HACK ALERT
	int w = 0, h = 0;
	if (textwidget != 0) {
		w = _dims.w;
		h = _dims.h;
		_dims.w = origw;
		_dims.h = origh;
	}

	Gump::saveData(ods);

	// HACK ALERT
	if (textwidget != 0) {
		_dims.w = w;
		_dims.h = h;
	}

	uint16 flex = 0;
	uint32 shapenum = 0;
	if (shape_up) {
		shape_up->getShapeId(flex, shapenum);
	}
	ods->write2(flex);
	ods->write4(shapenum);
	ods->write4(_frameNum_up);

	flex = 0;
	shapenum = 0;
	if (shape_down) {
		shape_down->getShapeId(flex, shapenum);
	}
	ods->write2(flex);
	ods->write4(shapenum);
	ods->write4(_frameNum_down);
	ods->write2(textwidget);
	ods->write4(mouseOverBlendCol);

	uint8 m = (mouseOver ? 1 : 0);
	ods->write1(m);
}

bool ButtonWidget::loadData(IDataSource *ids, uint32 version) {
	if (!Gump::loadData(ids, version)) return false;

	shape_up = 0;
	ShapeArchive *flex = GameData::get_instance()->getShapeFlex(ids->read2());
	uint32 shapenum = ids->read4();
	if (flex) {
		shape_up = flex->getShape(shapenum);
	}
	_frameNum_up = ids->read4();

	shape_down = 0;
	flex = GameData::get_instance()->getShapeFlex(ids->read2());
	shapenum = ids->read4();
	if (flex) {
		shape_down = flex->getShape(shapenum);
	}
	_frameNum_down = ids->read4();
	textwidget = ids->read2();
	mouseOverBlendCol = ids->read4();
	mouseOver = (ids->read1() != 0);

	// HACK ALERT
	if (textwidget != 0) {
		Gump *widget = getGump(textwidget);
		widget->GetDims(_dims); // transfer child dimension to self
		widget->Move(0, _dims.y); // move it to the correct height
	}

	return true;
}

} // End of namespace Ultima8
} // End of namespace Ultima
