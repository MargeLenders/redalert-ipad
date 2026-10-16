/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef HELP_H
#define HELP_H

#include	"tab.h"

#define HELP_TEXT_COLOR 80	//158		//Goldy/orange

class HelpClass: public TabClass
{
	public:
		HelpClass(void);
		HelpClass(NoInitClass const & x) : TabClass(x) {};

		/*
		** Initialization
		*/
		virtual void Init_Clear(void);						// Clears all to known state

		virtual void Draw_It(bool complete=false);
		virtual void AI(KeyNumType &input, int x, int y);
		virtual bool Scroll_Map(DirType facing, int &distance, bool really);
		virtual void Set_Tactical_Position(COORDINATE coord);

		void Help_Text(int text, int x=-1, int y=-1, int color=LTGREY, bool quick=false);
		void Set_Cost(int cost);
		short const * Overlap_List(void) const;

	private:

		static char const *HelpText;
		int HelpX;
		int HelpY;
		int HelpWidth;


		void Set_Text(int text);

		/*
		**	If the help text is right justified (as with the help text that pops up over the
		**	sidebar icons), then this flag is set to true.
		*/
		unsigned IsRight:1;

		/*
		**	If the optional second line of text that displays cost is desired, then this
		**	value will be non-zero. Typically, this is true when the help text is associated
		**	with one of the sidebar construction icons.
		*/
		int Cost;

		/*
		**	This is the recorded position of the cursor at the time the help text
		**	pops up. The help text is rendered as an offset from this pixel position.
		*/
		int X;
		int Y;

		/*
		**	This is the draw X and Y coordinate. This position is relative to the X and
		**	Y coordinates but adjusted for screen edges as necessary.
		*/
		int DrawX;
		int DrawY;

		/*
		**	The width of the help text (in pixels) is stored here. This is a convenience
		**	since calculating the width takes a bit of time.
		*/
		int Width;

		/*
		**	The text number of the help text to display is held here. If no text is to be
		**	displayed, then this value will be TXT_NONE.
		*/
		int Text;

		/*
		**	This is the background color to use for the help text. It can change according
		**	to the message displayed.
		*/
		int Color;

		/*
		**	This countdown timer controls when the help text will pop up. If the mouse
		**	remains stationary while this countdown timer expires, then the help text
		**	will pop up.
		*/
		CDTimerClass<SystemTimerClass> CountDownTimer;

		/*
		**	This is a calculated cell offset list (from the Map.TacticalCell) that indicates
		**	which cells are under the help text and thus which cells need to be redrawn if
		**	the help text is to be erased.
		*/
		static short OverlapList[60];

		enum HelpClassEnum {
			HELP_DELAY=TIMER_SECOND*1,				// The countdown timer delay before help text pops up.
			Y_OFFSET=0,					// The Y pixel offset from cursor for help text print.
			X_OFFSET=12					// The X pixel offset from cursor for help text print.
		};
};


#endif
