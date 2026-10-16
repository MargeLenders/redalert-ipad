/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SOUNDDLG_H
#define SOUNDDLG_H

#include "gadget.h"

class SoundControlsClass
{
	enum SoundControlsClassEnums {
#ifdef FRENCH
		OPTION_WIDTH=308,
#else
		OPTION_WIDTH=292,
#endif
		OPTION_HEIGHT=146,

		OPTION_X=((320 - OPTION_WIDTH) / 2),
		OPTION_Y=(200 - OPTION_HEIGHT) / 2,

		LISTBOX_X=17,
		LISTBOX_Y=54,
		LISTBOX_W=OPTION_WIDTH-(LISTBOX_X*2),
		LISTBOX_H=72,

		BUTTON_WIDTH=70,
		BUTTON_X=OPTION_WIDTH-(BUTTON_WIDTH+17),	 				// Options button x pos
		BUTTON_Y=128, 					// Options button y pos

		STOP_X=17,						// Stop button X.
		STOP_Y=128,						//	Stop button Y.

		PLAY_X=35,
		PLAY_Y=128,

		ONOFF_WIDTH=25,
#ifdef GERMAN
		SHUFFLE_X=79,//BGA:91,
#else
#ifdef FRENCH
		SHUFFLE_X=99,
#else
		SHUFFLE_X=97,
#endif
#endif
		SHUFFLE_Y=128,

#ifdef FRENCH
		REPEAT_X=169,
#else
		REPEAT_X=164,
#endif
		REPEAT_Y=128,

		MSLIDER_X=147,
		MSLIDER_Y=28,
		MSLIDER_W=108,
		MSLIDER_HEIGHT=5,

		FXSLIDER_X=147,
		FXSLIDER_Y=40,
		FXSLIDER_W=108,
		FXSLIDER_HEIGHT=5,

		BUTTON_STOP = 605,
		BUTTON_PLAY,
		BUTTON_SHUFFLE,
		BUTTON_REPEAT,
		BUTTON_OPTIONS,
		SLIDER_MUSIC,
		SLIDER_SOUND,
		BUTTON_LISTBOX,
	};

	public:
		SoundControlsClass(void) {}
		void Process(void);
};

#endif
