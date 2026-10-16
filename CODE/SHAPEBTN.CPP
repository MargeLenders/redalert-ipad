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
#include "shapebtn.h"


/***********************************************************************************************
 * ShapeButtonClass::ShapeButtonClass -- Default Constructor for a shape type button.          *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   You must call Set_Shape() before using a button constructed with this function, *
 *             and you must set X & Y, and ID.                                                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ShapeButtonClass::ShapeButtonClass(void) :
	ToggleClass(0, 0, 0, 0, 0),
	ReflectButtonState(false)
{
}


/***********************************************************************************************
 * ShapeButtonClass::ShapeButtonClass -- Constructor for a shape type button.                  *
 *                                                                                             *
 *    This is the normal constructor for a shape type button. Shape buttons are ones that      *
 *    have their imagery controlled by a shape file. The various states of the button are      *
 *    given a visual form as one of these shapes. Button dimensions are controlled by the      *
 *    first shape.                                                                             *
 *                                                                                             *
 * INPUT:   id    -- The button ID.                                                            *
 *                                                                                             *
 *          shape -- Pointer to the shape file that controls the button's display.             *
 *                                                                                             *
 *          x,y   -- The pixel coordinate of the upper left corner of the button.              *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   The width and height of the shape is controlled by the first shape in the       *
 *             shape file provided. This means that all the shapes in the shape file must be   *
 *             the same size.                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ShapeButtonClass::ShapeButtonClass(unsigned id, void const * shape, int x, int y) :
	ToggleClass(id, x, y, 0, 0),
	ReflectButtonState(false)
{
//	Width = 0;
//	Height = 0;
	Set_Shape(shape);
}


/***********************************************************************************************
 * ShapeButtonClass::Set_Shape -- Assigns a shape to this shape button.                        *
 *                                                                                             *
 *    This routine will assign the specified shape to this shape object.                       *
 *                                                                                             *
 * INPUT:   data  -- Pointer to the shape to assign.                                           *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/20/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void ShapeButtonClass::Set_Shape(void const * data)
{
	ShapeData = data;
	if (ShapeData) {
		Width = Get_Build_Frame_Width(ShapeData);
		Height = Get_Build_Frame_Height(ShapeData);
	}
}


/***********************************************************************************************
 * ShapeButtonClass::Draw_Me -- Renders the shape button's imagery.                            *
 *                                                                                             *
 *    This function is called when the button detects that it must be redrawn. The actual      *
 *    shape to use is controled by the button's state and the shape file provided when then    *
 *    button was constructed.                                                                  *
 *                                                                                             *
 * INPUT:   forced   -- Should the button be redrawn regardless of the redraw flag?            *
 *                                                                                             *
 * OUTPUT:  bool; Was the shape redrawn?                                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int ShapeButtonClass::Draw_Me(int forced)
{
	if (ControlClass::Draw_Me(forced) && ShapeData) {

		/*
		**	Hide the mouse.
		*/
		if (LogicPage == &SeenBuff) {
			Conditional_Hide_Mouse(X, Y, X+Width-1, Y+Height-1);
		}

		/*
		**	Draw the body & set text color.
		*/
		int shapenum = 0;
		if (IsDisabled) {
			shapenum = DISABLED_SHAPE;
		} else {

			if (!ReflectButtonState) {

				if (IsPressed) {
					shapenum = DOWN_SHAPE;
				} else {
					shapenum = UP_SHAPE;
				}
			} else {
				shapenum = IsOn;
			}

		}
		CC_Draw_Shape(ShapeData, shapenum, X, Y, WINDOW_MAIN, SHAPE_NORMAL);
		/*
		**	Display the mouse.
		*/
		if (LogicPage == &SeenBuff) {
			Conditional_Show_Mouse();
		}
		return(true);
	}
	return(false);
}



