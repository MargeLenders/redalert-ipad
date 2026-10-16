/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CONFDLG_H
#define CONFDLG_H

#include "gadget.h"

class ConfirmationClass
{
	private:
		enum ConfirmationClassEnum {
			BUTTON_YES=1,								// Button number for "Options menu"
			BUTTON_NO									// Button number for "Options menu"
		};

	public:
		ConfirmationClass(void) {  };
		bool Process(char const * string);
		bool Process(int text);
};

#endif
