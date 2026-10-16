/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SCROLL_H
#define SCROLL_H

#include	"help.h"


class ScrollClass: public HelpClass
{
		/*
		**	If map scrolling is automatic, then this flag is true. Automatic scrolling will
		**	cause the map to scroll if the mouse is in the scroll region, regardless of
		**	whether or not the mouse button is held down.
		*/
		unsigned IsAutoScroll:1;

		/*
		**	Scroll speed is regulated by this count down timer. When this value reaches zero,
		**	scroll the map in the direction required and reset this timer.
		*/
		static CDTimerClass<SystemTimerClass> Counter;

		/*
		** Inertia control for scrolling
		*/
		int	Inertia;

	public:
		ScrollClass(void);
		ScrollClass(NoInitClass const & x) : HelpClass(x) {};

		bool Set_Autoscroll(int control);

		virtual void AI(KeyNumType &input, int x, int y);
		virtual void Init_IO(void) {Counter = 0;HelpClass::Init_IO();};
};

#endif
