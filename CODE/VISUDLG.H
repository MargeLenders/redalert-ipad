/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef VISUDLG_H
#define VISUDLG_H

#include "gadget.h"

class VisualControlsClass 
{
	private:

		enum VisualControlEnums {
			BUTTON_BRIGHTNESS=1,
			BUTTON_COLOR,
			BUTTON_CONTRAST,
			BUTTON_TINT,
			BUTTON_RESET,
			BUTTON_OPTIONS,							// Button number for "Options menu"
			OPTION_WIDTH=216,							// Width of dialog box.
			OPTION_HEIGHT=122,						// Height of dialog box.
			OPTION_X=(((320 - OPTION_WIDTH) / 2)),
			OPTION_Y=((200 - OPTION_HEIGHT) / 2),
			TEXT_X=OPTION_X+28,			 			// Title's x pos
			TEXT_Y=OPTION_Y+30,  					// Add 11 for each following line
			SLIDER_X=OPTION_X+105, 					// Slider's x pos
			SLIDER_Y=OPTION_Y+30,  					// Add 11 for each following line
			SLIDER_WIDTH=70,							// Width of each control slider.
			SLIDER_HEIGHT=5,							// Height of each control slider.
			SLIDER_Y_SPACING=11,						// Vertical spacing between sliders.
			BUTTON_X=OPTION_X+63,	 				// Options button x pos
			BUTTON_Y=OPTION_Y+102, 					// Options button y pos
		};

	public:

		VisualControlsClass(void) {};
		void Process(void);
};

#endif
