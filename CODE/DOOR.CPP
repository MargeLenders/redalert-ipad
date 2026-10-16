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
 * DoorClass::DoorClass -- Constructor for the DoorClass object.                               *
 *                                                                                             *
 *    This constructor sets the door to an initial closed state.                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/14/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
DoorClass::DoorClass(void)
{
	State = IS_CLOSED;
	IsToRedraw = false;
	Stages = 0;
}


/***********************************************************************************************
 * DoorClass::AI -- Handles the door processing logic.                                         *
 *                                                                                             *
 *    This routine should be called every game frame. It handles the door closing and opening  *
 *    logic.                                                                                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/13/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void DoorClass::AI(void)
{
	if (Control.Graphic_Logic()) {
		if (Control.Fetch_Stage() >= Stages) {
			Control.Set_Rate(0);
			switch (State) {
				case IS_OPENING:
					State = IS_OPEN;
					break;

				case IS_CLOSING:
					State = IS_CLOSED;
					break;
			}
		}
		IsToRedraw = true;
	}
}


/***********************************************************************************************
 * DoorClass::Open_Door -- Opens the door for this unit.                                       *
 *                                                                                             *
 *    This routine will perform the door open operation for this unit. It will control vehicle *
 *    rotation if necessary.                                                                   *
 *                                                                                             *
 * INPUT:   rate     -- The animation rate (delay) to use for the door animation logic.        *
 *                                                                                             *
 *          stages   -- The number of animations stages that this door must pass through.      *
 *                                                                                             *
 * OUTPUT:  Was action initiated to open the door?                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool DoorClass::Open_Door(int rate, int stages)
{
	switch (State) {
		case IS_CLOSED:
		case IS_CLOSING:
			State = IS_OPENING;
			Stages = stages-1;
			Control.Set_Stage(0);
			Control.Set_Rate(rate);
			return(true);
	}
	return(false);
}


/***********************************************************************************************
 * DoorClass::Close_Door -- Try to close the unit's door.                                      *
 *                                                                                             *
 *    This routine will attempt to close the unit's door. If the door is already closed or     *
 *    in the process of closing, then no action is performed.                                  *
 *                                                                                             *
 * INPUT:   rate     -- The animation rate (delay) to use for the door animation logic.        *
 *                                                                                             *
 *          stages   -- The number of animations stages that this door must pass through.      *
 *                                                                                             *
 * OUTPUT:  Action was initiated to close the door?                                            *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool DoorClass::Close_Door(int rate, int stages)
{
	switch (State) {
		case IS_OPEN:
		case IS_OPENING:
			State = IS_CLOSING;
			Stages = stages-1;
			Control.Set_Stage(0);
			Control.Set_Rate(rate);
			return(true);
	}
	return(false);
}


/***********************************************************************************************
 * DoorClass::Door_Stage -- Fetches the current door animation frame.                          *
 *                                                                                             *
 *    Use this routine to fetch the current door animation frame number. Frame zero is the     *
 *    closed frame and frame 'N' is the open frame. If the door is in the process of opening   *
 *    or closing, the appropriate frame number is used. 'N' is defined as the number of        *
 *    stages in the animation minus 1 (e.g., a four frame animation will return a door stage   *
 *    number between 0 and 3, inclusive).                                                      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the door animation frame number.                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/14/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int DoorClass::Door_Stage(void) const
{
	switch (State) {
		case IS_CLOSING:
			return((Stages-1) - Control.Fetch_Stage());

		case IS_CLOSED:
			return(0);

		case IS_OPENING:
			return(Control.Fetch_Stage());

		case IS_OPEN:
			return(Stages-1);
	}
	return(0);
}
