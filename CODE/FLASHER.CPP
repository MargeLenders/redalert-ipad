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


#ifdef CHEAT_KEYS
/***********************************************************************************************
 * FlasherClass::Debug_Dump -- Displays current status to the monochrome screen.               *
 *                                                                                             *
 *    This utility function will output the current status of the FlasherClass to the mono     *
 *    screen. It is through this display that bugs may be fixed or detected.                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/31/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FlasherClass::Debug_Dump(MonoClass * mono) const
{
	mono->Set_Cursor(50, 7);
	mono->Printf("%2d", FlashCount);
}
#endif


/***********************************************************************************************
 * FlasherClass::Process -- Performs the logic processing for the flashing ability.            *
 *                                                                                             *
 *    The ability for an object to flash is controlled by this logic processing routine. It    *
 *    should be called once per game tick per unit.                                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  bool; Should the associated object be redrawn?                                     *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/28/1994 JLB : Created.                                                                 *
 *   06/20/1994 JLB : Is now independent of object it represents.                              *
 *=============================================================================================*/
bool FlasherClass::Process(void)
{
	if (FlashCount) {
		FlashCount--;
		IsBlushing = false;

		if (FlashCount & 0x01) {
			IsBlushing = true;
		}
		return(true);
	}
	return(false);
}


