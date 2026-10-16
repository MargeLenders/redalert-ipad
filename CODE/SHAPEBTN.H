/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SHAPEBTN_H
#define SHAPEBTN_H

#include	"toggle.h"

class ShapeButtonClass : public ToggleClass
{
	public:
		ShapeButtonClass(void);
		ShapeButtonClass(unsigned id, void const * shapes, int x, int y);
		virtual int Draw_Me(int forced=false);
		virtual void Set_Shape(void const * data);
		void const * Get_Shape_Data(void) {return(ShapeData);};

		enum ShapeButtonClassEnums {
			UP_SHAPE,				// Shape to use when button is "up".
			DOWN_SHAPE,				// Shape to use when button is "down".
			DISABLED_SHAPE			// Shape to use when button is disabled.
		};

		unsigned ReflectButtonState:1;

	protected:

		/*
		**	This points to the shape data file. This file contains the appropriate shapes
		**	for this button in the offsets specified above.
		*/
		void const * ShapeData;
};
#endif
