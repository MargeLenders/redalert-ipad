/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef COLORLIST_H
#define COLORLIST_H

#include "list.h"


/***************************************************************************
** This class adds the ability for every list item to have a different color.
*/
class ColorListClass : public ListClass
{
	public:
		/*********************************************************************
		** These enums are the ways a selected item can be drawn
		*/
		//lint -esym(578,SELECT_NONE)
		typedef enum SelectEnum {
			SELECT_NORMAL,				// selected items aren't drawn differently
			SELECT_HIGHLIGHT,			// item is highlighted
			SELECT_BOX,					// draw a box around the item
			SELECT_BAR,					// draw a bar behind the item
			SELECT_INVERT				// draw the string inverted
		} SelectStyleType;

		ColorListClass(int id, int x, int y, int w, int h, TextPrintType flags, void const * up, void const * down);
		virtual ~ColorListClass(void);

		virtual int  Add_Item(char const * text, RemapControlType * color = NULL);
		virtual int  Add_Item(int text, RemapControlType * color = NULL);
		virtual void Remove_Item(char const * text);

		virtual void Set_Selected_Style(SelectStyleType style, RemapControlType * color = NULL);

		/*
		**	This is the list of colors for each item.
		*/
		DynamicVectorClass<RemapControlType *> Colors;

	protected:
		virtual void Draw_Entry(int index, int x, int y, int width, int selected);

		/*
		**	This tells how to draw the selected item.
		*/
		SelectStyleType Style;
		RemapControlType * SelectColor;

};

#endif
