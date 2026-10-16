/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TAB_H
#define TAB_H

#include	"sidebar.h"
#include	"credits.h"

class TabClass: public SidebarClass
{
	public:
		TabClass(void);
		TabClass(NoInitClass const & x) : SidebarClass(x), Credits(x), FlasherTimer(x), MoneyFlashTimer(x) {};

		virtual void AI(KeyNumType &input, int x, int y);
		virtual void Draw_It(bool complete=false);
		static void Draw_Credits_Tab(void);
		static void Hilite_Tab(int tab);
		void Flash_Money(void);

		virtual void One_Time(void);							// One-time inits
		void Redraw_Tab(void) {IsToRedraw = true;Flag_To_Redraw(false);};

		CreditClass Credits;

		CDTimerClass<FrameTimerClass> FlasherTimer;

	protected:

		/*
		**	If the tab graphic is to be redrawn, then this flag is true.
		*/
		unsigned IsToRedraw:1;

	private:
		void Set_Active(int select);

		CDTimerClass<FrameTimerClass> MoneyFlashTimer;

		static void const * TabShape;
};


#endif
