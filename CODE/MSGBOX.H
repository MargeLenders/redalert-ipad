/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef MSGBOX_H
#define MSGBOX_H

#include	"jshell.h"

class WWMessageBox
{
		int Caption;

	public:
		WWMessageBox(int caption=TXT_NONE) {Caption = caption;};
		int Process(const char *msg, const char *b1txt, const char *b2txt=NULL, const char *b3txt=NULL, bool preserve=false);
		int Process(int msg, int b1txt=TXT_OK, int b2txt=TXT_NONE, int b3txt=TXT_NONE, bool preserve=false);
		int Process(char const *msg, int b1txt=TXT_OK, int b2txt=TXT_NONE, int b3txt=TXT_NONE, bool preserve=false);
};

#endif

