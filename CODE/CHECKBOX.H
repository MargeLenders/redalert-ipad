/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include	"toggle.h"

class CheckBoxClass : public ToggleClass
{
	public:
		CheckBoxClass(unsigned id, int x, int y) :
			ToggleClass(id, x, y, 7, 7)
		{};

		virtual int Draw_Me(int forced=false);
		virtual int Action(unsigned flags, KeyNumType & key);

	protected:
};

#endif
