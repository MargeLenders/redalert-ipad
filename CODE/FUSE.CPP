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


/***********************************************************************************************
 * FuseClass::FuseClass -- Constructor.                                                        *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/27/1995 BRR : Created.  Gosh, what a lotta work.                                       *
 *=============================================================================================*/
FuseClass::FuseClass(void)
{
	Timer = 0;
	Arming = 0;
	HeadTo = 0;
	Proximity = 0;
}


/***********************************************************************************************
 * FuseClass::Arm_Fuse -- Sets up fuse for detonation check.                                   *
 *                                                                                             *
 *    This starts a fuse. Fuses are proximity detonation variety but                           *
 *    can be modified to have a minimum time to elapse before detonation                       *
 *    and a maximum time to exist before detonation. Typically, the                            *
 *    timing values are used for missiles that have a minimum arming                           *
 *    distance and a limited amount of fuel.                                                   *
 *                                                                                             *
 * INPUT:   location -- The coordinate where the projectile start. This                        *
 *                      is needed for proper proximity tracking.                               *
 *                                                                                             *
 *          target   -- The actual impact point. Fuses are based on real                       *
 *                      word coordinates.                                                      *
 *                                                                                             *
 *          time     -- The maximum time that the fuse may work before                         *
 *                      explosion is forced.                                                   *
 *                                                                                             *
 *          arming   -- The minimum time that must elapse before the                           *
 *                      fuse may explode.                                                      *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/24/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FuseClass::Arm_Fuse(COORDINATE location, COORDINATE target, int timeto, int arming)
{
	timeto = max(timeto, arming);
	Timer = min(timeto, 0xFF);
	Arming = min(arming, 0xFF);
	HeadTo = target;
	Proximity = Distance(location, target);
}


/***********************************************************************************************
 * FuseClass::Fuse_Checkup -- Determines if the fuse triggers.                                 *
 *                                                                                             *
 *    This will process the fuse and update the internal clocks as well                        *
 *    as check to see if the fuse should trigger (explode) or not.                             *
 *                                                                                             *
 * INPUT:   newlocation -- The new location of the fuse. This is needed                        *
 *                         to determine proximity explosions.                                  *
 *                                                                                             *
 * OUTPUT:  bool; Was the fuse triggered to explode now?                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/24/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
bool FuseClass::Fuse_Checkup(COORDINATE newlocation)
{
	int	proximity;

	/*
	**	Always decrement the fuse timer.
	*/
	if (Timer) Timer--;

	/*
	**	If the arming countdown has not expired, then do nothing.
	*/
	if (Arming) {
		Arming--;
	} else {

		/*
		**	If the timer has run out, then the warhead explodes.
		*/
		if (!Timer) return(true);

		proximity = Distance(newlocation, HeadTo);
		if (proximity < 0x0010) return(true);
		if (proximity < ICON_LEPTON_W && proximity > Proximity) {
			return(true);
		}
		Proximity = proximity;
	}
	return(false);
}


/***********************************************************************************************
 * FuseClass::Fuse_Write -- Writes the fuse data to the save game file.                        *
 *                                                                                             *
 *    Use this routine to output the fuse class data to the save game file specified.          *
 *                                                                                             *
 * INPUT:   file  -- The file to output the data to.                                           *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/17/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FuseClass::Fuse_Write(FileClass & file)
{
	file.Write(&Timer, sizeof(Timer));
	file.Write(&Arming, sizeof(Arming));
	file.Write(&HeadTo, sizeof(HeadTo));
	file.Write(&Proximity, sizeof(Proximity));
}


/***********************************************************************************************
 * FuseClass::Fuse_Read -- Reads the fuse class data from the save game file.                  *
 *                                                                                             *
 *    Use this routine to input the fuse class data from the save game file specified.         *
 *                                                                                             *
 * INPUT:   file  -- The file to input the data from.                                          *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/17/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FuseClass::Fuse_Read(FileClass & file)
{
	file.Read(&Timer, sizeof(Timer));
	file.Read(&Arming, sizeof(Arming));
	file.Read(&HeadTo, sizeof(HeadTo));
	file.Read(&Proximity, sizeof(Proximity));
}


