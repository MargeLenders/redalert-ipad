/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TEXTBTN_H
#define TEXTBTN_H

#include	"toggle.h"


class TextButtonClass : public ToggleClass
{
	public:
		TextButtonClass(void);
		TextButtonClass(unsigned id, char const * text, TextPrintType style, int x, int y, int w=-1, int h=-1, int blackborder=false);
		TextButtonClass(unsigned id, int text, TextPrintType style, int x, int y, int w=-1, int h=-1, int blackborder=false);
		virtual int Draw_Me(int forced=false);
		virtual void Set_Text(char const *text, bool resize = false);
		virtual void Set_Text(int text, bool resize = false);
		virtual void Set_Style (TextPrintType style) {PrintFlags = style;}

	protected:

		virtual void Draw_Background(void);
		virtual void Draw_Text(char const * text);

		unsigned IsBlackBorder:1;

		/*
		**	This points to a constant string that is used for the button's text.
		*/
		char const * String;

		/*
		**	This is the print flags to use when rendering this button's text.
		*/
		TextPrintType PrintFlags;
};

#endif

