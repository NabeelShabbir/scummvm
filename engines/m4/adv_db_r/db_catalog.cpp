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

#include "common/file.h"
#include "common/str.h"
#include "m4/adv_db_r/db_catalog.h"
#include "m4/adv_db_r/database.h"
#include "m4/core/cstring.h"
#include "m4/core/errors.h"
#include "m4/core/imath.h"
#include "m4/globals.h"

namespace M4 {

static void sort_catalog();
static char *catalog_search(char *name);
static char *db_get_catalog_entry(char *c, short *tag, short *room, char *name, char *path, short *c_size);
static int compare_catalog_entries_for_search(const void *n1, const void *n2);

int read_catalog() {
	Common::File f;
	size_t size = 0;
	Common::String myFilename;

	myFilename = "roomsdb.chk";
#if 0
	if (f_info_exists(myFileName))
		goto plarg_o_rama;

	f_info_cd_name(myFileName);
	strcat(myFileName, PATHNAME_SEPARATOR_STRING);
	strcat(myFileName, "roomsdb.chk");

	if (f_info_exists(myFileName))
		goto plarg_o_rama;

	env_get_path(myFileName, 0, "roomsdb.chk");
	term_message("using network ROOMSDB.CHK %s", myFileName);
	if (!f_info_exists(myFileName))
		return 0;

plarg_o_rama:
#endif
	if (!f.open(myFilename))
		error_show(FL, 'FNF!', "Can't open %s", myFilename.c_str());
	size = f.size();

	if (_G(catalog)._data)
		mem_free(_G(catalog)._data);

	_G(catalog)._data = (char *)mem_alloc(size + 4, "catalog");

	if (f.read(_G(catalog)._data, size) != size)
		error_show(FL, 'FRDF', "Could not read in the catalog.");

	f.close();

	sort_catalog();
	return 1;
}

char *db_get_catalog() {
	return _G(catalog)._data;
}

char *db_rmlst_get_asset_room_path(char *asset_name, char *result, int32 *sceneCode) {
	char name[MAX_FILENAME_SIZE], path[MAX_FILENAME_SIZE];
	short tag = 0, room = 0;
	short c_size = 0;
	long str_len;

	result[0] = '\0';

	char *search_result = catalog_search(asset_name);

	//apr10
	if (search_result != NULL) {
		db_get_catalog_entry(search_result, &tag, &room, name, path, &c_size);
		*sceneCode = room;
	}

	if (!scumm_strnicmp(asset_name, name, MAX_FILENAME_SIZE)) {
		if (path[0] == '\\')
			cstrncpy(result, &path[1], MAX_FILENAME_SIZE);
		else
			cstrncpy(result, path, MAX_FILENAME_SIZE);

		str_len = strlen(result);

		if (str_len) {
			if (result[str_len - 1] == '\\')
				result[str_len - 1] = '\0';
		}
	}

	return result;
}

static int32 count_catalog_items() {
	char *pCatIter = db_get_catalog();
	int32 my_catalog_size = 0;

	while (pCatIter) {
		pCatIter = db_get_catalog_entry(pCatIter, NULL, NULL, NULL, NULL, NULL);
		if (pCatIter)
			++my_catalog_size;
	}

	return my_catalog_size;
}

static int compare_catalog_entries_for_sort(const void *n1, const void *n2) {
	char *entry1 = *(char **)n1;
	if (convert_intel16(*(short *)&entry1[2]) == _T_ROOM)
		entry1 = &entry1[6];
	else
		entry1 = &entry1[4];

	char *entry2 = *(char **)n2;
	if (convert_intel16(*(short *)&entry2[2]) == _T_ROOM)
		entry2 = &entry2[6];
	else
		entry2 = &entry2[4];

	return (scumm_strnicmp(entry1, entry2, 80));
}

static void sort_catalog() {
	char name[MAX_FILENAME_SIZE], path[MAX_FILENAME_SIZE];
	short tag;
	long i;

	_G(catalog)._size = count_catalog_items();
	_G(catalog)._catalog = (char **)calloc(_G(catalog)._size + 4, sizeof(char *));

	char *pCatalogIter = _G(catalog)._data;
	int32 index = 0;
	while (pCatalogIter) {
		_G(catalog)._catalog[index] = pCatalogIter;

		short room_number;
		char *nextItem = db_get_catalog_entry(pCatalogIter, &tag, &room_number, name, path, NULL);

		switch (tag) {
		case _T_ROOM:
			snprintf(&pCatalogIter[(3 * sizeof(short))], 256, "%03d!\0", room_number);

			i = (3 * sizeof(short)) + (5 * sizeof(char));

			for (;;) {
				if (!pCatalogIter[i])
					break;
				pCatalogIter[i++] = '\0';
			}
			break;

		default:
			cstrupr(pCatalogIter + (2 * sizeof(short)));
			break;
		}

		pCatalogIter = nextItem;

		if (pCatalogIter)
			++index;

		if (index > _G(catalog)._size)
			error_show(FL, 'OOM!');
	}

	qsort(_G(catalog)._catalog, _G(catalog)._size, sizeof(char *), compare_catalog_entries_for_sort);
}

static char *catalog_search(char *name) {
	char myString[80];
	cstrcpy(myString, name);
	cstrupr(myString);

	char **result = (char **)bsearch((void *)myString, (void *)_G(catalog)._catalog, _G(catalog)._size, sizeof(char *), compare_catalog_entries_for_search);
	if (!result)
		return NULL;

	return *result;
}

static char *db_get_catalog_entry(char *c, short *tag, short *room, char *name, char *path, short *c_size) {
	int i;
	char s[MAX_FILENAME_SIZE];

	if (tag)
		*tag = 0;
	if (room)
		*room = 0;
	if (name)
		*name = '\0';
	if (path)
		*path = '\0';
	if (c_size)
		*c_size = 0;

	short size = convert_intel16(*(short *)&c[0]);

	if (!size)
		return NULL;

	if (c_size)
		*c_size = size;

	int32 x = sizeof(short);

	int16 theTag = convert_intel16(*(short *)&c[x]);
	if (tag)
		*tag = theTag;

	x += sizeof(short); //tag

	if ((theTag == _T_ROOM) && room) {
		*room = convert_intel16(*(short *)&c[x]);
		x += sizeof(short);
	}

	for (i = 0; c[x]; x++) {
		s[i++] = c[x];

		if (i == MAX_FILENAME_SIZE)
			error_show(FL, 'OOM!');
	}
	s[i] = '\0';

	if (name)
		snprintf(name, MAX_FILENAME_SIZE, "%s", s);

	//feb5
	//skip over trailing '\0' or NULL string.
	//for( i=0; i<2; i++ ) {
	//	if( c[x] )
	//		break;
	//	x++;
	//}
	for (;; ) {
		if (c[x])
			break;
		x++;
	}

	switch (theTag) {
	case _T_DEPTH:
	case _T_SPECIAL:
	case _T_WALK:
		break;

	default:
		for (i = 0; c[x]; x++) {
			s[i++] = c[x];
		}
		s[i] = '\0';
		if (path)
			snprintf(path, MAX_FILENAME_SIZE, "%s", s);
		break;
	}

	if ((theTag != _T_ROOM) && room)
		*room = convert_intel16(*(short *)&c[size - (sizeof(short))]);

	return &c[size];
}

static int compare_catalog_entries_for_search(const void *n1, const void *n2) {
	char *cat_entry = *(char **)n2;

	if (convert_intel16(*(short *)&cat_entry[2]) == _T_ROOM)
		cat_entry = &cat_entry[6];
	else
		cat_entry = &cat_entry[4];

	return (scumm_strnicmp((char *)n1, cat_entry, 80));
}

} // End of namespace M4
