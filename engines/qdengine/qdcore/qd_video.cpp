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

#define FORBIDDEN_SYMBOL_ALLOW_ALL
#include "common/debug.h"
#include "common/textconsole.h"

#include "qdengine/qdengine.h"
#include "qdengine/qd_precomp.h"
#include "qdengine/system/graphics/gr_dispatcher.h"
#include "qdengine/parser/qdscr_parser.h"
#include "qdengine/parser/xml_tag_buffer.h"
#include "qdengine/qdcore/qd_video.h"
#include "qdengine/qdcore/qd_setup.h"
#include "qdengine/qdcore/qd_game_dispatcher.h"
#include "qdengine/qdcore/qd_file_manager.h"

namespace QDEngine {

qdVideo::qdVideo() : position_(0, 0) {
}

qdVideo::qdVideo(const qdVideo &v):
	qdConditionalObject(v),
	position_(v.position_),
	file_name_(v.file_name_),
	background_(v.background_) {
}

qdVideo::~qdVideo() {
}

qdVideo &qdVideo::operator = (const qdVideo &v) {
	if (this == &v) return *this;

	*static_cast<qdConditionalObject *>(this) = v;

	position_ = v.position_;
	file_name_ = v.file_name_;
	background_ = v.background_;

	return *this;
}

bool qdVideo::load_script(const xml::tag *p) {
	load_conditions_script(p);

	Vect2s v;
	for (xml::tag::subtag_iterator it = p->subtags_begin(); it != p->subtags_end(); ++it) {
		switch (it->ID()) {
		case QDSCR_NAME:
			set_name(it->data());
			break;
		case QDSCR_FLAG:
			set_flag(xml::tag_buffer(*it).get_int());
			break;
		case QDSCR_CD:
			set_CD_info(xml::tag_buffer(*it).get_uint());
			break;
		case QDSCR_FILE:
			set_file_name(Common::Path(it->data(), '\\').toString().c_str());
			break;
		case QDSCR_VIDEO_POSITION:
			xml::tag_buffer(*it) > v.x > v.y;
			set_position(v);
			break;
		case QDSCR_VIDEO_BACKGROUND:
			if (strlen(it->data()))
				set_background_file_name(it->data());
			break;
		}
	}

	return true;
}

bool qdVideo::save_script(Common::SeekableWriteStream &fh, int indent) const {
	 for (int i = 0; i < indent; i++) {
		fh.writeString("\t");
	}

	fh.writeString("<video name=");

	if (name()) {
		fh.writeString(Common::String::format("\"%s\"", qdscr_XML_string(name())));
	} else {
		fh.writeString("\" \"");
	}

	if (CD_info()) {
		fh.writeString(Common::String::format(" cd=\"%d\"", CD_info()));
	}

	if (flags()) {
		fh.writeString(Common::String::format(" flags=\"%d\"", flags()));
	}

	if (!check_flag(VID_CENTER_FLAG | VID_FULLSCREEN_FLAG) && (position_.x || position_.y)) {
		fh.writeString(Common::String::format(" video_position=\"%d %d\"", position_.x, position_.y)) ;
	}

	fh.writeString(">\r\n");

	if (background_.has_file()) {
		for (int i = 0; i <= indent; i++) {
			fh.writeString("\t");
		}
		fh.writeString(Common::String::format("<video_background>%s</video_background>", qdscr_XML_string(background_file_name())));
	}

	for (int i = 0; i <= indent; i++) {
		fh.writeString("\t");
	}
	fh.writeString(Common::String::format("<file>%s</file>\r\n", qdscr_XML_string(file_name_.c_str())));

	save_conditions_script(fh, indent);

	for (int i = 0; i < indent; i++) {
		fh.writeString("\t");
	}
	fh.writeString("</video>\r\n");

	return true;
}

bool qdVideo::draw_background() {
	if (background_.has_file()) {
		background_.load();

		grDispatcher::instance()->Fill(0);
		int x = qdGameConfig::get_config().screen_sx() >> 1;
		int y = qdGameConfig::get_config().screen_sy() >> 1;
		background_.redraw(x, y, 0);
		grDispatcher::instance()->Flush();

		background_.free();

		return true;
	}

	grDispatcher::instance()->Fill(0);
	grDispatcher::instance()->Flush();

	return false;
}

qdConditionalObject::trigger_start_mode qdVideo::trigger_start() {
	debugC(3, kDebugLog, "[%d] Video start->%s", g_system->getMillis(), transCyrillic(name()));

	if (qdGameDispatcher * dp = qd_get_game_dispatcher()) {
		if (dp->play_video(this))
			dp->pause();
	}

	return qdConditionalObject::TRIGGER_START_ACTIVATE;
}

bool qdVideo::get_files_list(qdFileNameList &files_to_copy, qdFileNameList &files_to_pack) const {
	if (!file_name_.empty())
		files_to_copy.push_back(file_name_);

	if (background_file_name())
		files_to_pack.push_back(background_file_name());

	return true;
}
} // namespace QDEngine
