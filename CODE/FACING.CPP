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
#include	"facing.h"


/***********************************************************************************************
 * FacingClass::FacingClass -- Default constructor for the facing class.                       *
 *                                                                                             *
 *    This default constructor merely sets the desired and current facing values to be the     *
 *    same (North).                                                                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/21/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
FacingClass::FacingClass(void)
{
	CurrentFacing = DIR_N;
	DesiredFacing = DIR_N;
}


/***********************************************************************************************
 * FacingClass::Set_Desired -- Sets the desired facing  value.                                 *
 *                                                                                             *
 *    This routine is used to set the desired facing value without altering the current        *
 *    facing setting. Typical use of this routine is when a vehicle needs to face a           *
 *    direction, but currently isn't facing the correct direction. After this routine is       *
 *    called, it is presumed that subsequent calls to Rotation_Adjust() will result in the     *
 *    eventual alignment of the current facing.                                                *
 *                                                                                             *
 * INPUT:   facing   -- The new facing to assign to the desired value.                         *
 *                                                                                             *
 * OUTPUT:  bool; Did the desired facing value actually change by this routine call?           *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/21/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int FacingClass::Set_Desired(DirType facing)
{
	facing = (DirType)(unsigned char)facing;
	if (DesiredFacing != facing) {
		DesiredFacing = facing;
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * FacingClass::Set_Current -- Sets the current rotation value.                                *
 *                                                                                             *
 *    This routine will set the current rotation value. It is used to override the facing      *
 *    value without adjusting the desired setting.                                             *
 *                                                                                             *
 * INPUT:   facing   -- The new facing to assign to the current facing value.                  *
 *                                                                                             *
 * OUTPUT:  bool; Was the current setting changed by this routine. Failure means that the      *
 *                current setting was already at the value specified.                          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/21/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int FacingClass::Set_Current(DirType facing)
{
	facing = (DirType)(unsigned char)facing;
	if (CurrentFacing != facing) {
		CurrentFacing = facing;
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * FacingClass::Rotation_Adjust -- Perform a rotation adjustment to current facing.            *
 *                                                                                             *
 *    This routine is used when the current and desired facings differ but the current         *
 *    facing should be adjusted toward the desired facing. The amount of rotation to adjust    *
 *    is provided as a rotation rate parameter. Typical use of this routine is for turrets     *
 *    and other vehicle related rotating.                                                      *
 *                                                                                             *
 * INPUT:   rate  -- The rotation rate to use when adjusting the current facing toward the     *
 *                   desired facing. A value of 127 means instantaneous rotation.              *
 *                                                                                             *
 * OUTPUT:  bool; Did the rotation result in the current facing transitioning from one         *
 *                1/32 zone to another? If true, then the owning object most likely will       *
 *                need to be redrawn to reflect the change.                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/21/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int FacingClass::Rotation_Adjust(int rate)
{
	/*
	**	Only perform the rotation adjustment if the desired facing is not the
	**	same as the current facing.
	*/
	if (Is_Rotating()) {
		rate = min(rate, 127);

		DirType oldfacing = CurrentFacing;
		int diff = Difference();

		/*
		**	If the allowed facing change is greater than the difference between
		**	the current facing and the desired facing, then just snap the
		**	facing to the new value.
		*/
		if (ABS(diff) < rate) {
			CurrentFacing = DesiredFacing;
		} else {

			/*
			**	Adjust the current facing clockwise or counterclockwise depending
			**	on the shortest distance to the desired facing from the current
			**	facing.
			*/
			if (diff < 0) {
				CurrentFacing = (DirType)(unsigned char)(CurrentFacing - (DirType)rate);
			} else {
				CurrentFacing = (DirType)(unsigned char)(CurrentFacing + (DirType)rate);
			}
		}

		/*
		**	If this facing adjustment caused the current facing to rotate into a
		**	new 1/32 rotation zone (likely to cause a redraw), then return
		**	this fact with a true value.
		*/
		return(Dir_To_32(CurrentFacing) != Dir_To_32(oldfacing));
	}
	return(false);
}
