/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef DESCDLG_H
#define DESCDLG_H

#include "gadget.h"

class DescriptionClass 
{
	private:

		enum DescriptionClassEnum {
			OPTION_WIDTH=216,							// Width of dialog box.
			OPTION_HEIGHT=122,						// Height of dialog box.
			OPTION_X=(((320 - OPTION_WIDTH) / 2) & ~7),
			OPTION_Y=((200 - OPTION_HEIGHT) / 2),
			TEXT_X=OPTION_X+32,			 			// Title's x pos
			TEXT_Y=OPTION_Y+32,  					// Add 11 for each following line
			BUTTON_OPTIONS=1,							// Button number for "Ok"
			BUTTON_CANCEL,							
			BUTTON_EDIT,
			BUTTON_X=OPTION_X+63,	 				// Options button x pos
			BUTTON_Y=OPTION_Y+102, 					// Options button y pos
			EDIT_Y  =OPTION_Y+50, 					
			EDIT_W  =180   //204,
		};

	public:
		DescriptionClass(void) {};
		void Process(char *string);
};

#endif


