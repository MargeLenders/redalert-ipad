/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TOGGLE_H
#define TOGGLE_H

#include "control.h"

/*
**	This class handles gadgets that behave like the Windows buttons. That is, once the mouse
**	button is clicked over them, they capture the focus until the mouse button is released.
**	They have a different imagery for the pressed and released states. They only recognize
**	a valid selection when the mouse button is release while over the button.
*/
class ToggleClass : public ControlClass
{
	public:
		ToggleClass(unsigned id, int x, int y, int w, int h);
		void Turn_On(void);
		void Turn_Off(void);

		/*
		**	Is this button in a pressed down state? This occurs when the mouse is clicked on the
		**	button and the mouse is still being held down.
		*/
		unsigned IsPressed:1;

		/*
		**	This is the button on/off state. Sometimes a button that is "on" has a different
		**	imagery than one that is "off". If the on/off state is not necessary, then just
		**	ignore this flag.
		*/
		unsigned IsOn:1;

		/*
		**	If this button can be turned "on" or "off", then this flag should be set to
		**	true. Sometimes a button needs to display its on/off state. In the render routine,
		**	examine the IsOn flag and display accordingly. If this flag is false, then the
		**	IsOn flag will not be changed, regardless of button clicking.
		*/
		unsigned IsToggleType:1;

	protected:

		virtual int Action(unsigned flags, KeyNumType &key);
};

#endif
