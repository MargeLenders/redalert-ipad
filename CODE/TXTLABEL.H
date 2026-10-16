/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TXTLABEL_H
#define TXTLABEL_H

class TextLabelClass : public GadgetClass
{
	public:
		/*
		** Constructor/Destructor
		*/
		TextLabelClass(char *txt, int x, int y, RemapControlType * color,
			TextPrintType style);

		/*
		** Overloaded draw routine
		*/
		virtual int Draw_Me(int forced = false);

		/*
		** Sets the displayed text of the label
		*/
		virtual void Set_Text(char *txt) {Text = txt;};

		/*
		** General-purpose data fields
		*/
		unsigned long UserData1;
		unsigned long UserData2;
		TextPrintType Style;
		char *Text;
		RemapControlType * Color;
		int PixWidth;
};

#endif

