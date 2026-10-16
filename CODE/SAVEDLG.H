/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SAVEDLG_H
#define SAVEDLG_H

#include "gadget.h"

class SaveOptionsClass 
{
	private:

		enum SaveOptionsClassEnums {
			BUTTON_CANCEL=200,
			BUTTON_SAVE,
			OPTION_WIDTH=216,
			OPTION_HEIGHT=122,
			OPTION_X=((320 - OPTION_WIDTH) / 2) & ~7,
			OPTION_Y=(200 - OPTION_HEIGHT) / 2,
			NUMBER_OF_BUTTONS=2,
			CAPTION_Y_POS=5,
			BORDER1_LEN=49,
			BUTTON_CANCEL_X=90,
			BUTTON_CANCEL_Y=103,
			LISTBOX_X=40,
			LISTBOX_Y=24,
			LISTBOX_W=136,
			LISTBOX_H=72
		};

	public:
		SaveOptionsClass (void) { };
		void Process (void);
};


#endif
