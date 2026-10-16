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


/***************************************************************************
 * ColorListClass::ColorListClass -- class constructor                     *
 *                                                                         *
 * INPUT:                                                                  *
 *      id               button ID                                         *
 *      x,y            upper-left corner, in pixels                        *
 *      w,h            width, height, in pixels                            *
 *      list            ptr to array of char strings to list               *
 *    flags          flags for mouse, style of listbox                     *
 *      up,down         pointers to shapes for up/down buttons             *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:          01/05/1995 MML : Created.                             *
 *=========================================================================*/
ColorListClass::ColorListClass (int id, int x, int y, int w, int h,
	TextPrintType flags, void const * up, void const * down) :
	ListClass (id, x, y, w, h, flags, up, down),
	Style(SELECT_HIGHLIGHT),
	SelectColor(NULL)
{
}


/***************************************************************************
 * ColorListClass::~ColorListClass -- Class destructor                     *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
ColorListClass::~ColorListClass(void)
{
	Colors.Clear();
	SelectColor = 0;
}


/***************************************************************************
 * ColorListClass::Add_Item -- Adds an item to the list                    *
 *                                                                         *
 * INPUT:                                                                  *
 *		text		text to add to list                                      	*
 *		color		color for item                                          		*
 *                                                                         *
 * OUTPUT:                                                                 *
 *		position of item in the list                                       	*
 *                                                                         *
 * WARNINGS:                                                               *
 *		none.                                                              	*
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
int ColorListClass::Add_Item(char const * text, RemapControlType * color)
{
	Colors.Add(color);
	return(ListClass::Add_Item(text));
}


/***************************************************************************
 * ColorListClass::Add_Item -- Adds an item to the list                    *
 *                                                                         *
 * INPUT:                                                                  *
 *		text		text to add to list                                      	*
 *		color		color for item                                          		*
 *                                                                         *
 * OUTPUT:                                                                 *
 *		position of item in the list                                       	*
 *                                                                         *
 * WARNINGS:                                                               *
 *		none.                                                              	*
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
int ColorListClass::Add_Item(int text, RemapControlType * color)
{
	Colors.Add(color);
	return(ListClass::Add_Item(text));
}


/***************************************************************************
 * ColorListClass::Remove_Item -- Removes an item from the list            *
 *                                                                         *
 * INPUT:                                                                  *
 *      text      ptr to item to remove                                    *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Remove_Item(char const * text)
{
	int index = List.ID(text);
	if (index != -1) {
		Colors.Delete(index);
		ListClass::Remove_Item(text);
	}
}


/***************************************************************************
 * ColorListClass::Set_Selected_Style -- tells how to draw selected item   *
 *                                                                         *
 * INPUT:                                                                  *
 *		style		style to draw                                           		*
 *		color		color to draw the special style in; -1 = use item's color	*
 *                                                                         *
 * OUTPUT:                                                                 *
 *		none.                                                              	*
 *                                                                         *
 * WARNINGS:                                                               *
 *		none.                                                              	*
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Set_Selected_Style(SelectStyleType style, RemapControlType * color)
{
	Style = style;
	SelectColor = color;
}


/***************************************************************************
 * ColorListClass::Draw_Entry -- Draws one text line                       *
 *                                                                         *
 * INPUT:                                                                  *
 *		index			index into List of item to draw                      		*
 *		x,y			x,y coords to draw at                                  	*
 *		width			maximum width allowed for text                       		*
 *		selected		true = this item is selected                         		*
 *                                                                         *
 * OUTPUT:                                                                 *
 *		none.                                                              	*
 *                                                                         *
 * WARNINGS:                                                               *
 *		none.                                                              	*
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
	RemapControlType * color;

	/*
	** Draw a non-selected item in its color
	*/
	if (!selected) {
		Conquer_Clip_Text_Print(List[index], x, y, Colors[index], TBLACK, TextFlags, width, Tabs);
		return;
	}

	/*
	** For selected items, choose the right color & style:
	*/
	if (SelectColor == NULL) {
		color = Colors[index];
	} else {
		color = SelectColor;
	}

	switch (Style) {
		/*
		**	NONE: Just print the string in its native color
		*/
		case SELECT_NORMAL:
			Conquer_Clip_Text_Print(List[index], x, y, Colors[index], TBLACK,
				TextFlags, width, Tabs);
			break;

		/*
		**	HIGHLIGHT: Draw the string in the highlight color (SelectColor must
		**	be set)
		*/
		case SELECT_HIGHLIGHT:
			if (TextFlags & TPF_6PT_GRAD) {
				Conquer_Clip_Text_Print(List[index], x, y, color, TBLACK, TextFlags | TPF_BRIGHT_COLOR, width, Tabs);
			} else {
				Conquer_Clip_Text_Print(List[index], x, y, color, TBLACK, TextFlags, width, Tabs);
			}
			break;

		/*
		**	BOX: Draw a box around the item in the current select color
		*/
		case SELECT_BOX:
			LogicPage->Draw_Rect (x, y, x + width - 2, y + LineHeight - 2, color->Color);
			Conquer_Clip_Text_Print(List[index], x, y, Colors[index], TBLACK, TextFlags, width, Tabs);
			break;

		/*
		**	BAR: draw a color bar under the text
		*/
		case SELECT_BAR:
			if (TextFlags & TPF_6PT_GRAD) {
				LogicPage->Fill_Rect(x, y, x + width - 1, y + LineHeight - 1, color->Color);
				Conquer_Clip_Text_Print(List[index], x, y, Colors[index], TBLACK, TextFlags | TPF_BRIGHT_COLOR, width, Tabs);
			} else {
				LogicPage->Fill_Rect(x, y, x + width - 2, y + LineHeight - 2, color->Color);
				Conquer_Clip_Text_Print(List[index], x, y, Colors[index], TBLACK, TextFlags, width, Tabs);
			}
			break;

		/*
		**	INVERT: Draw text as the background color on foreground color
		*/
		case SELECT_INVERT:
			LogicPage->Fill_Rect (x, y, x + width - 1, y + LineHeight - 1, Colors[index]->Color);
			break;
	}
}
