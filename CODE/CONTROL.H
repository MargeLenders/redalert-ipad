/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CONTROL_H
#define CONTROL_H

#include	"gadget.h"

/***************************************************************************
 * ControlClass -- Region tracking class									         *
 *                                                                         *
 * INPUT:      int x -- x position of gadget											*
 *					int y -- y position of gadget											*
 *					int w -- width of gadget												*
 *					int h -- height of gadget												*
 *					UWORD flags -- see enumeration choices								*
 *                                                                         *
 * OUTPUT:     0 = new scenario created, -1 = not									*
 * WARNINGS:	This class is Abstract (cannot make an instance of it)      *
 *                                                                         *
 * HISTORY:                                                                *
 *   01/03/1995 MML : Created.                                             *
 *=========================================================================*/
class ControlClass : public GadgetClass
{
	public:
		ControlClass(NoInitClass const & x) : GadgetClass(x) {};
		ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags=LEFTPRESS|RIGHTPRESS, int sticky=false);
		ControlClass(ControlClass const & control);

		virtual void Make_Peer(GadgetClass & gadget);

		/*
		**	Render support function.
		*/
		virtual int Draw_Me(int forced=false);

		/*
		**	This is the ID number for this control gadget. This number is used to generate
		**	a special pseudo-key when the gadget detects valid input.
		*/
		unsigned ID;

	protected:
		virtual unsigned Get_ID(void) const;
		virtual int Action(unsigned flags, KeyNumType & key);

		/*
		**	This points to the peer button to inform when something happens to this
		**	gadget.
		*/
		GadgetClass * Peer;
};

#endif

