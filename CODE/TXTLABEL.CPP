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


/***********************************************************************************************
 * TextLableClass::TextLabelClass -- Constructor                                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      txt         pointer to text buffer to print from                                       *
 *      x            x-coord for text printing                                                 *
 *      y            y-coord for text printing                                                 *
 *      color         color to print in                                                        *
 *      style         style to print (determines the meaning of x & y)                         *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/24/1995 BRR : Created.                                                                 *
 *=============================================================================================*/
TextLabelClass::TextLabelClass(char *txt, int x, int y, RemapControlType * color,
 TextPrintType style) : GadgetClass(x, y, 1, 1, 0, 0)
{
	Text = txt;
	Color = color;
	Style = style;
	UserData1 = 0;
	UserData2 = 0;
	PixWidth = -1;
}


/***********************************************************************************************
 * TextLableClass::Draw_Me -- Graphical update routine                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      forced      true = draw regardless of the current redraw flag state                    *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      true = gadget was redrawn, false = wasn't                                              *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/24/1995 BRR : Created.                                                                 *
 *=============================================================================================*/
int TextLabelClass::Draw_Me(int forced)
{
	if (GadgetClass::Draw_Me(forced)) {
		if (PixWidth == -1) {
			Simple_Text_Print(Text, X, Y, Color, TBLACK, Style);
//			Fancy_Text_Print(Text, X, Y, Color, TBLACK, Style);
		} else {
			Conquer_Clip_Text_Print(Text, X, Y, Color, TBLACK, Style, PixWidth);
		}
		return(true);
	}
	return(false);
}
