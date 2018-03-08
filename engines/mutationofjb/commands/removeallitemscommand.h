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

#ifndef MUTATIONOFJB_REMOVEALLITEMSCOMMAND_H
#define MUTATIONOFJB_REMOVEALLITEMSCOMMAND_H

#include "mutationofjb/commands/seqcommand.h"

namespace MutationOfJB {

class RemoveAllItemsCommandParser : public SeqCommandParser {
public:
	RemoveAllItemsCommandParser() {}

	virtual bool parse(const Common::String &line, ScriptParseContext &parseCtx, Command *&command);
};

class RemoveAllItemsCommand : public SeqCommand {
public:
	RemoveAllItemsCommand() {}

	virtual ExecuteResult execute(GameData &gameData) override;
	virtual Common::String debugString() const override;
private:
};

}

#endif
