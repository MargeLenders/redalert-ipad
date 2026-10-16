/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include "function.h"


/***************************************************************************
 * Dial8Class::Dial8Class -- constructor for the facing dial               *
 *                                                                         *
 * INPUT:                                                                  *
 *      id            button ID                                            *
 *      x,y,w,h      dimensions in window-relative pixels                  *
 *      dir         numerical initial facing value (0-255); this is the    *
 *                  value returned by WWLIB Desired_Facing8()              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/16/1994 BR : Created.                                              *
 *=========================================================================*/
Dial8Class::Dial8Class(int id, int x, int y, int w, int h, DirType dir) :
	ControlClass(id, x, y, w, h, LEFTPRESS | LEFTHELD | LEFTRELEASE, true)
{
	/*
	**	Center coordinates.
	*/
	FaceX = X + (Width / 2);
	FaceY = Y + (Height / 2);

	/*
	**	Init directions.
	*/
	Direction = dir;							// 0 - 255
	Facing = Dir_Facing(Direction);		// 0 - 7
	OldFacing = Facing;						// 0 - 7

	/*
	**	Compute the drawing dimensions:  a 45-degree angle intersects a unity-
	**	radius circle at (.707,.707). Make the decorations 8/10 of the radius,
	**	and the line extend to 6/10 of the radius. Use Width/2 for x-radius,
	**	Height/2 for y-radius.
	*/
	FacePoint[0][0] = FaceX;
	FacePoint[0][1] = FaceY - (h * 8 / 2) / 10;

	FacePoint[1][0] = FaceX + (w * 7 * 8 / 2) / 100;
	FacePoint[1][1] = FaceY - (h * 7 * 8 / 2) / 100;

	FacePoint[2][0] = FaceX + (w * 8 / 2) / 10;
	FacePoint[2][1] = FaceY;

	FacePoint[3][0] = FaceX + (w * 7 * 8 / 2) / 100;
	FacePoint[3][1] = FaceY + (h * 7 * 8 / 2) / 100;

	FacePoint[4][0] = FaceX;
	FacePoint[4][1] = FaceY + (h * 8 / 2) / 10;

	FacePoint[5][0] = FaceX - (w * 7 * 8 / 2) / 100;
	FacePoint[5][1] = FaceY + (h * 7 * 8 / 2) / 100;

	FacePoint[6][0] = FaceX - (w * 8 / 2) / 10;
	FacePoint[6][1] = FaceY;

	FacePoint[7][0] = FaceX - (w * 7 * 8 / 2) / 100;
	FacePoint[7][1] = FaceY - (h * 7 * 8 / 2) / 100;

	FaceLine[0][0] = FaceX;
	FaceLine[0][1] = FaceY - (h * 6 / 2) / 10;

	FaceLine[1][0] = FaceX + (w * 7 * 6 / 2) / 100;
	FaceLine[1][1] = FaceY - (h * 7 * 6 / 2) / 100;

	FaceLine[2][0] = FaceX + (w * 6 / 2) / 10;
	FaceLine[2][1] = FaceY;

	FaceLine[3][0] = FaceX + (w * 7 * 6 / 2) / 100;
	FaceLine[3][1] = FaceY + (h * 7 * 6 / 2) / 100;

	FaceLine[4][0] = FaceX;
	FaceLine[4][1] = FaceY + (h * 6 / 2) / 10;

	FaceLine[5][0] = FaceX - (w * 7 * 6 / 2) / 100;
	FaceLine[5][1] = FaceY + (h * 7 * 6 / 2) / 100;

	FaceLine[6][0] = FaceX - (w * 6 / 2) / 10;
	FaceLine[6][1] = FaceY;

	FaceLine[7][0] = FaceX - (w * 7 * 6 / 2) / 100;
	FaceLine[7][1] = FaceY - (h * 7 * 6 / 2) / 100;
}


/***************************************************************************
 * Dial8Class::Action -- activation function for Dial8Class                *
 *                                                                         *
 * INPUT:                                                                  *
 *      flags      the reason we're being called                           *
 *      key      the KN_number that was pressed                            *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      true = event was processed, false = event not processed            *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   02/06/1995 BR : Created.                                              *
 *=========================================================================*/
int Dial8Class::Action(unsigned flags, KeyNumType &key)
{
	static int is_sel = 0;

	/*
	**	We might end up clearing the event bits. Make sure that the sticky
	**	process is properly updated anyway.
	*/
	Sticky_Process(flags);

	if (flags & LEFTPRESS) {
		is_sel = 1;
	}

	/*
	**	If left mouse is clicked or held, and the dial has changed its direction,
	**	invoke the parent Action routine:
	**	GadgetClass::Action handles Sticky processing, & sets IsToRepaint if any
	**	  flag bits are set.
	**	ControlClass::Action handles Peer_To_Peer notification, and substitutes
	**	  'key' with the button ID if any flags are set, or 0 if no flags are set
	*/
	if (flags & LEFTPRESS || ((flags & LEFTHELD) && is_sel)) {
		/*
		**	Get new dial position (0-255)
		*/
		Direction = (DirType)Desired_Facing8(FaceX, FaceY, Get_Mouse_X(), Get_Mouse_Y());

		/*
		**	Convert to Facing value (0-7).
		*/
		Facing = Dir_Facing(Direction);

		/*
		**	If it's moved, redraw.
		*/
		if (Facing!=OldFacing) {
			OldFacing = Facing;
			ControlClass::Action(flags, key);
			return(true);

		} else {

			/*
			**	Dial hasn't moved; kill the event & return
			*/
			key = KN_NONE;
			ControlClass::Action(0, key);
			return(true);
		}

	} else {

		/*
		**	Otherwise, no events have occurred; kill the event if it's a LEFTRELEASE,
		**	and return
		*/
		if (flags & LEFTRELEASE) {
			key = KN_NONE;
			is_sel = 0;
		}
		return(ControlClass::Action(0, key));
	}
}


/***************************************************************************
 * Dial8Class::Draw_Me -- custom render routine for Dial8Class             *
 *                                                                         *
 * INPUT:                                                                  *
 *      forced      true = draw regardless of the current redraw flag state*
 *                                                                         *
 * OUTPUT:                                                                 *
 *      true = gadget was redrawn, false = wasn't                          *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   02/06/1995 BR : Created.                                              *
 *=========================================================================*/
int Dial8Class::Draw_Me(int forced)
{
	RemapControlType * scheme = GadgetClass::Get_Color_Scheme();

	/*
	**	Redraw if parent indicates a redraw is needed
	*/
	if (ControlClass::Draw_Me(forced)) {
		/*
		**	Hide the mouse.
		*/

		if (LogicPage == &SeenBuff) {
			Hide_Mouse();
		}

		/*
		**	Draw background & decorations.
		*/
		Draw_Box(X, Y, Width, Height, BOXSTYLE_DOWN, true);
		for (int i=0; i<8; i++) {
			Draw_Box(FacePoint[i][0] - 1, FacePoint[i][1] -1, 3, 3, BOXSTYLE_RAISED, false);
		}

		/*
		**	Draw the hand & its shadow.
		*/
		LogicPage->Draw_Line(FaceX+1, FaceY+1, FaceLine[Facing][0]+1, FaceLine[Facing][1]+1, scheme->Shadow);
		LogicPage->Draw_Line(FaceX, FaceY, FaceLine[Facing][0], FaceLine[Facing][1], scheme->Highlight);

		/*
		**	Restore the mouse.
		*/
		if (LogicPage == &SeenBuff) {
			Show_Mouse();
		}

		return(true);
	}

	return(false);
}


/***************************************************************************
 * Dial8Class::Get_Direction -- retrieves direction (0-255) of dial        *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      DirType dial is pointing to                                        *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/17/1994 BR : Created.                                              *
 *=========================================================================*/
DirType Dial8Class::Get_Direction(void) const
{
	return(Direction);
}


/***************************************************************************
 * Dial8Class::Set_Direction -- sets current direction (0-255) of dial     *
 *                                                                         *
 * INPUT:                                                                  *
 *      DirType to set dial to                                             *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/17/1994 BR : Created.                                              *
 *=========================================================================*/
void Dial8Class::Set_Direction(DirType dir)
{
	Direction = dir;
	Facing = Dir_Facing(Direction);
	OldFacing = Facing;
	Flag_To_Redraw();
}
