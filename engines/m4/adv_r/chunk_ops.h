
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

#ifndef M4_ADV_R_CHUNK_OPS_H
#define M4_ADV_R_CHUNK_OPS_H

#include "m4/m4_types.h"
#include "m4/adv_r/conv.h"

namespace M4 {

#define PPLUS					402
#define MINUS 					403
#define TIMES 					404
#define PERCENT 				405
#define POWER 					406
#define IS_ASSIGNED				407
#define PERIOD 					410
#define DOLLAR					411
#define LT					412
#define GT					413
#define L_BRAK					416 
#define R_BRAK					417

#define DIVIDE					418  
#define NOT					419

#define LE					420
#define GE					421
#define NE					422
#define PE					423
#define ME					424
#define TE					425
#define DE					426
#define AE					427
#define OE					428
#define EQ					429
#define AND					430
#define OR					431
#define TILDA					432
#define DBL_QUOTE				433
#define ANDAND					444
#define OROR					445
#define DOT					446
#define CNE					448

extern conv_chunk *get_conv(Conv *c, long cSize);
extern entry_chunk *get_entry(Conv *c, long cSize);
extern char *conv_ops_get_entry(long i, long *next, long *tag, Conv *c);
extern void conv_ops_unknown_chunk(long tag, const char *s);
extern decl_chunk *get_decl(Conv *c, long cSize);
extern char *get_string(Conv *c, long cSize);
extern text_chunk *get_text(Conv *c, long cSize);
extern long conv_ops_text_strlen(char *s);
extern c_assign_chunk *get_c_asgn(Conv *c, long cSize);
extern int conv_ops_cond_successful(long l_op, long op, long r_op);
extern long conv_ops_process_asgn(long val, long oprtr, long opnd);
extern assign_chunk *get_asgn(Conv *c, long cSize);
extern misc_chunk *get_misc(Conv *c, long cSize);
extern entry_chunk *get_hash_entry(Conv *c, long cSize);
extern c_misc_chunk *get_c_misc(Conv *c, long cSize);
extern c_goto_chunk *get_c_goto(Conv *c, long cSize);
extern goto_chunk *get_goto(Conv *c, long cSize);
extern reply_chunk *get_reply(Conv *c, long cSize);
extern lnode_chunk *get_lnode(Conv *c, long cSize);
extern node_chunk *get_node(Conv *c, long cSize);
extern fall_chunk *get_fall(Conv *c, long cSize);
extern long get_long(Conv *c, long cSize);
extern c_reply_chunk *get_c_reply(Conv *c, long cSize);
extern w_reply_chunk *get_w_reply(Conv *c, long cSize);
extern w_entry_chunk *get_w_entry(Conv *c, long cSize);

} // End of namespace M4

#endif
