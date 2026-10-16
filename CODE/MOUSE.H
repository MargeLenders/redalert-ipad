/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef MOUSE_H
#define MOUSE_H

#include	"stage.h"
#include	"scroll.h"

class MouseClass: public ScrollClass
{
	public:
		MouseClass(void);
		MouseClass(NoInitClass const & x) : ScrollClass(x) {};

		/*
		** Initialization
		*/
		virtual void One_Time(void);							// One-time inits
		virtual void Init_Clear(void);						// Clears all to known state

		virtual void AI(KeyNumType &input, int x, int y);
		virtual bool Override_Mouse_Shape(MouseType mouse, bool wsmall=false);
		virtual void Revert_Mouse_Shape(void);
		virtual MouseType Get_Mouse_Shape(void) const {return NormalMouseShape;};
		virtual void Mouse_Small(bool wsmall);

		/*
		**	File I/O.
		*/
		virtual bool Load(Straw & file);
		virtual bool Save(Pipe & file) const;

		virtual void Set_Default_Mouse(MouseType mouse, bool wsmall = false);

		/*
		**	This allows the tactical map input gadget access to change the
		**	mouse shapes.
		*/
		friend class TacticalClass;

		/*
		**	This points to the loaded mouse shapes.
		*/
		static void const * MouseShapes;

	private:

		/*
		**	This type is used to control the frames and rates of the mouse
		**	pointer. Some mouse pointers are actually looping animations.
		*/
		typedef struct MouseStruct
		{
			int StartFrame;			// Starting frame number.
			int FrameCount;			// Number of animation frames.
			int FrameRate;				// Frame delay between changing frames.
			int SmallFrame;			// Start frame number for small version (if any).
			int X,Y;						// Hotspot X and Y offset.
		} MouseStruct;

		/*
		**	The control frames and rates for the various mouse pointers are stored
		**	in this static array.
		*/
		static MouseStruct MouseControl[MOUSE_COUNT];

	public:
		/*
		**	If the small representation of the mouse is active, then this flag is true.
		*/
		unsigned IsSmall:1;


	private:
		/*
		**	The mouse shape is controlled by these variables. These
		**	hold the current mouse shape (so resetting won't be needlessly performed) and
		**	the normal default mouse shape (when arrow shapes are needed).
		*/
		MouseType CurrentMouseShape;
		MouseType NormalMouseShape;

		/*
		**	For animating mouse shapes, this controls the frame and animation rate.
		*/
		static CDTimerClass<SystemTimerClass> Timer;
		int Frame;
};


#endif
