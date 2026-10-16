/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SCREEN_H
#define SCREEN_H


class ScreenClass
{
		/*
		**	The mouse shape is controlled by these variables. These
		**	hold the current mouse shape (so resetting won't be needlessly performed) and
		**	the normal default mouse shape (when arrow shapes are needed).
		*/
		MouseShapeType CurrentMouseShape;
		MouseShapeType NormalMouseShape;

	public:

		ScreenClass(void) {
			CurrentMouseShape = SHP_NONE;
			NormalMouseShape = SHP_MOUSE;
		};
		

		Init(void);
		Set_Default_Mouse(MouseShapeType mouse);
		Force_Mouse_Shape(MouseShapeType mouse);

		unsigned char *GamePalette;
		unsigned char *BlackPalette;
};

#endif
