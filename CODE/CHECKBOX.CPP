/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include	"function.h"
#include	"checkbox.h"


/***********************************************************************************************
 * CheckBoxClass::Draw_Me -- Draws the checkbox imagery.                                       *
 *                                                                                             *
 *    This routine will draw the checkbox either filled or empty as necessary.                 *
 *                                                                                             *
 * INPUT:   forced   -- Should the check box be drawn even if it doesn't think it needs to?    *
 *                                                                                             *
 * OUTPUT:  Was the check box rendered?                                                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/01/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int CheckBoxClass::Draw_Me(int forced)
{
	if (ToggleClass::Draw_Me(forced)) {

		Hide_Mouse();
		Draw_Box(X, Y, Width, Height, BOXSTYLE_DOWN, false);
		LogicPage->Fill_Rect(X+1, Y+1, X+Width-2, Y+Height-2, DKGREY);
		if (IsOn) {
			LogicPage->Fill_Rect(X+1, Y+1, X+Width-2, Y+Height-2, LTGREEN);
		}
		Show_Mouse();
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * CheckBoxClass::Action -- Handles a button action on a checkbox object.                      *
 *                                                                                             *
 *    This routine will detect if the mouse has been clicked on the checkbox object. If so,    *
 *    the check box state will be toggled.                                                     *
 *                                                                                             *
 * INPUT:   flags -- The event flags that resulted in this routine being called.               *
 *                                                                                             *
 *          key   -- The key that resulted in this routine being called.                       *
 *                                                                                             *
 * OUTPUT:  bool; Should normal processing occur?                                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CheckBoxClass::Action(unsigned flags, KeyNumType & key)
{
	if (flags & LEFTRELEASE) {
		if (IsOn) {
			Turn_Off();
		} else {
			Turn_On();
		}
	}
	return(ToggleClass::Action(flags, key));
}
