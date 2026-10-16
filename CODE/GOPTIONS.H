/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef GOPTIONS_H
#define GOPTIONS_H

#include "options.h"
#include "gadget.h"


class GameOptionsClass : public OptionsClass {
		enum GameOptionsButtonEnum {
			BUTTON_LOAD=1,
			BUTTON_SAVE,
			BUTTON_DELETE,
			BUTTON_GAME,
			BUTTON_QUIT,
#ifdef FIXIT_VERSION_3		//	Stalemate games.
			BUTTON_DRAW,
#endif
			BUTTON_RESUME,
			BUTTON_RESTATE,

			BUTTON_COUNT
		};

		enum GameOptionsEnum {
			OPTION_WIDTH=(216+8),
			OPTION_HEIGHT=100,
			OPTION_X=((320 - (216+8)) / 2),
			OPTION_Y=((200 - 100) / 2),
#ifdef FRENCH
			BUTTON_WIDTH=142,
#else
			BUTTON_WIDTH=130,
#endif
			NUMBER_OF_BUTTONS=6,		//	ajw Not used.
			CAPTION_Y_POS=5,
			BUTTON_Y=21,
			BORDER1_LEN=72,
			BORDER2_LEN=16,
			BUTTON_RESUME_Y=(100-15)
		};

	public:
		GameOptionsClass(void): OptionsClass () { };
		void  Adjust_Variables_For_Resolution(void);
		void Process(void);

	private:
		int	OptionWidth;
		int 	OptionHeight;
		int 	OptionX;
		int 	OptionY;
		int 	ButtonWidth;
		int 	OButtonHeight;
		int 	CaptionYPos;
		int 	ButtonY;
		int 	Border1Len;
		int 	Border2Len;
		int 	ButtonResumeY;

};

#endif
