/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CREDITS_H
#define CREDITS_H

/****************************************************************************
**	The animating credit counter display is controlled by this class.
*/
class CreditClass {
	public:
		long Credits;		// Value of credits trying to update display to.

		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		CreditClass(void);
		CreditClass(NoInitClass const & ) {};

		/*---------------------------------------------------------------------
		**	Member function prototypes.
		*/
		void Update(bool forced=false, bool redraw=false);

		void Graphic_Logic(bool forced=false);
		void AI(bool forced=false);

		long	Current;		// Credit value currently displayed.

		unsigned IsToRedraw:1;
		unsigned IsUp:1;
		unsigned IsAudible:1;

	private:
		int	Countdown;	// Delay between ticks.
};

#endif

